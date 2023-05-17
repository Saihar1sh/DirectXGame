#include <Windows.h>

bool gameRunning = true;

void* buffer_memory;
int buffer_width;
int buffer_height;
BITMAPINFO buffer_bitmapInfo;

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
		buffer_width = rect.right - rect.left;
		buffer_height = rect.bottom - rect.top;

		int buffer_size = buffer_width * buffer_height * sizeof(unsigned int);

		if (buffer_memory) VirtualFree(buffer_memory, 0, MEM_RELEASE);
		buffer_memory = VirtualAlloc(0, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		buffer_bitmapInfo.bmiHeader.biSize = sizeof(buffer_bitmapInfo.bmiHeader);
		buffer_bitmapInfo.bmiHeader.biWidth = buffer_width;
		buffer_bitmapInfo.bmiHeader.biHeight = buffer_height;
		buffer_bitmapInfo.bmiHeader.biPlanes = 1;
		buffer_bitmapInfo.bmiHeader.biBitCount = 32;
		buffer_bitmapInfo.bmiHeader.biCompression = BI_RGB;

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

		//Rendering
		StretchDIBits(hdc, 0, 0, buffer_width, buffer_height, 0, 0, buffer_width, buffer_height, buffer_memory, &buffer_bitmapInfo, DIB_RGB_COLORS,SRCCOPY);
	}

};