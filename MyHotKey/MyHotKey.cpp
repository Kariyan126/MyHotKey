#include <Windows.h>
#include <tchar.h>
#include <WinUser.h>
#include <powrprof.h>
#pragma comment(lib, "PowrProf.lib")

#define HOTKEY_SHUTDOWN 1
#define HOTKEY_SLEEP 2
#define HOTKEY_RESTART 3

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	HANDLE hMutex = CreateMutex(NULL, TRUE, L"MyUniqueAppMutexName");
	if (GetLastError() == ERROR_ALREADY_EXISTS) return 0;

	TCHAR szAppName[] = TEXT("Win32API_test");
	WNDCLASS wc;
	HWND hwnd;
	MSG msg;

	wc.style = CS_HREDRAW || CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;

	if (!RegisterClass(&wc)) return 0;

	hwnd = CreateWindow(
		szAppName,
		TEXT("Win32API_test"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (!hwnd) return 0;

	UpdateWindow(hwnd);

	RegisterHotKey(hwnd, HOTKEY_SHUTDOWN, MOD_CONTROL, VK_F12);
	RegisterHotKey(hwnd, HOTKEY_SLEEP, MOD_CONTROL | MOD_SHIFT | MOD_ALT, 'S');
	RegisterHotKey(hwnd, HOTKEY_RESTART, MOD_CONTROL | MOD_SHIFT | MOD_ALT, 'R');


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ReleaseMutex(hMutex);
	CloseHandle(hMutex);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_HOTKEY:
		switch (wParam)
		{
		case HOTKEY_SHUTDOWN:
			ShellExecuteW(NULL, L"open", L"cmd.exe", L"/c shutdown /s /t 0", NULL, SW_HIDE);
			break;

		case HOTKEY_SLEEP:
			SetSuspendState(FALSE, FALSE, FALSE);
			break;

		case HOTKEY_RESTART:
			ShellExecuteW(NULL, L"open", L"cmd.exe",L"/c shutdown /r /t 0", NULL, SW_HIDE);
			break;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}