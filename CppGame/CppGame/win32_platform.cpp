#include "utils.cpp"
#include <Windows.h>

global_variable bool gameRunning = true;

struct Render_State
{
	int width, height;
	void* memory;
	BITMAPINFO bitmap_Info;
};


global_variable Render_State render_state;

#include "renderer.cpp"

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

	while (gameRunning)
	{
		//Input
		MSG message;
		while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}

		//Simulate
		clear_screen(0x9ce79c);
		//draw_rect_in_pixels(50, 50, 500, 500, 0x000000);
		draw_rect(0, 0, 2, 2, 0x000000);
		draw_rect(3, 2, 4, 25, 0x000000);
		draw_rect(-3, -2, 4, 25, 0x000000);

		//Rendering
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_Info, DIB_RGB_COLORS,SRCCOPY);
	}

};