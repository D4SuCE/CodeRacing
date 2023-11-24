#pragma once
#include <windows.h>
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        MoveToEx(hdc, 100, 100, NULL);
        LineTo(hdc, 200, 200);
        MoveToEx(hdc, 200, 200, NULL);
        LineTo(hdc, 100, 200);
        MoveToEx(hdc, 100, 200, NULL);
        LineTo(hdc, 100, 100);
        EndPaint(hwnd, &ps);
    } break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
    return 0;
}
class RenderCore
{
public:
    void createWindow() {
        void createWindow();
        const LPCWSTR CLASS_NAME = L"Sample Window Class";
        WNDCLASS wc = { };

        wc.lpfnWndProc = WindowProcedure;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = CLASS_NAME;

        RegisterClass(&wc);

        HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Sample Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);

        if (hwnd == NULL) {
            return;
        }

        ShowWindow(hwnd, SW_SHOW);
        UpdateWindow(hwnd);

        MSG msg = { };
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
};
