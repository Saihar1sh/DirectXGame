#include "utils.cpp"
#include <windows.h>

global_variable bool gameRunning = true;

struct Render_State
{
	int width, height;
	void* memory;
	BITMAPINFO bitmap_Info;
};


global_variable Render_State render_state;

#include "renderer.cpp"
#include "platform_common.cpp"
#include "game.cpp"

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	switch (uMsg)
	{
		case WM_CLOSE:
		case WM_DESTROY:
		{
			gameRunning = false;
		}
			break;

		case WM_SIZE:
		{
			RECT rect;
			GetClientRect(hwnd, &rect);
			render_state.width = rect.right - rect.left;
			render_state.height = rect.bottom - rect.top;

			int buffer_size = render_state.width * render_state.height * sizeof(unsigned int);

			if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
			render_state.memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

			render_state.bitmap_Info.bmiHeader.biSize = sizeof(render_state.bitmap_Info.bmiHeader);
			render_state.bitmap_Info.bmiHeader.biWidth = render_state.width;
			render_state.bitmap_Info.bmiHeader.biHeight = render_state.height;
			render_state.bitmap_Info.bmiHeader.biPlanes = 1;
			render_state.bitmap_Info.bmiHeader.biBitCount = 32;
			render_state.bitmap_Info.bmiHeader.biCompression = BI_RGB;

		}
		break;

		default:
			result = DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	}

	return result;
}

int WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd) 
{
	//creating windows class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = window_callback;

	//registering class
	RegisterClass(&window_class);

	//creating a window
	HWND window = CreateWindow(window_class.lpszClassName, L"First Game", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT,
		1280, 720, 0, 0, hInstance, 0);

	HDC hdc = GetDC(window);

	Input input = {};

	while (gameRunning)
	{
		//Input
		MSG message;

		for (int i = 0; i < Button_Count; i++)
		{
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			switch (message.message)
			{
				case WM_KEYUP:
				case WM_KEYDOWN: 
				{
					u32 vk_code = (u32)message.wParam;
					bool is_down = ((message.lParam & (1 << 31)) == 0);

					switch (vk_code)
					{
						case VK_UP:
						{
							input.buttons[Button_Up].is_down = is_down;
							input.buttons[Button_Up].changed = true;
						}
						break;
						case VK_DOWN:
						{
							input.buttons[Button_Down].is_down = is_down;
							input.buttons[Button_Down].changed = true;
						}
						break;
						case VK_RIGHT:
						{
							input.buttons[Button_Right].is_down = is_down;
							input.buttons[Button_Right].changed = true;
						}
						break;
						case VK_LEFT:
						{
							input.buttons[Button_Left].is_down = is_down;
							input.buttons[Button_Left].changed = true;
						}
						break;
						default:
							break;
					}
				}
				break;
				default:
				{
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
				break;
			}

		}

		//Simulate
		simulate_game(&input);

		//Rendering
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_Info, DIB_RGB_COLORS,SRCCOPY);
	}

};