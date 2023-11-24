#pragma once

#include <windows.h>
#include <stdio.h>

static int up = 0;
static int down = 0;
static int right = 0;
static int left = 0;
int x = 100, y = 100;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
    case WM_PAINT: {
        //PAINTSTRUCT ps;
        //HDC hdc = BeginPaint(hwnd, &ps);
        //MoveToEx(hdc, 100, 100, NULL);
        //LineTo(hdc, 200, 200);
        //MoveToEx(hdc, 200, 200, NULL);
        //LineTo(hdc, 100, 200);
        //MoveToEx(hdc, 100, 200, NULL);
        //LineTo(hdc, 100, 100);
        //EndPaint(hwnd, &ps);

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rect;
        GetClientRect(hwnd, &rect);
        HBRUSH brush = (HBRUSH)GetStockObject(WHITE_BRUSH);
        FillRect(hdc, &rect, brush);
        MoveToEx(hdc, x, y, NULL);
        LineTo(hdc, x + 100, y + 100);
        LineTo(hdc, x + 200, y);
        LineTo(hdc, x, y);
        EndPaint(hwnd, &ps);
    } break;
    case WM_KEYDOWN: {
        //87 up
        //83 down
        //68 right
        //65 left
        if (wparam == VK_RIGHT) x += 5;
        else if (wparam == VK_LEFT) x -= 5;
        else if (wparam == VK_UP) y -= 5;
        else if (wparam == VK_DOWN) y += 5;
        switch (wparam) {
        case 87: up = 1; break;
        case 83: down = 1; break;
        case 68: right = 1; break;
        case 65: left = 1; break;
        }
        InvalidateRect(hwnd, NULL, TRUE);
    } break;
    case WM_KEYUP: {
        //87 up
        //83 down
        //68 right
        //65 left
        switch (wparam) {
        case 87: up = 0; break;
        case 83: down = 0; break;
        case 68: right = 0; break;
        case 65: left = 0; break;
        }
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
    HWND hwnd;
public:
    void createWindow() {
        const LPCWSTR CLASS_NAME = L"Sample Window Class";
        WNDCLASS wc = { };

        wc.lpfnWndProc = WindowProcedure;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = CLASS_NAME;

        RegisterClass(&wc);

        hwnd = CreateWindowEx(0, CLASS_NAME, L"Sample Window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);

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
