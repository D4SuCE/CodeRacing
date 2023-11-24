#pragma once

#include <windows.h>
#include <stdio.h>
#include <cmath>

static int throttle = 0;
static int brake = 0;
static int steer = 0;
static int x = 0, y = 0;
static float rotation;


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
private:
    static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
        switch (msg) {
        case WM_PAINT: {
            int halfWidth = 50;
            int halfHeight = 25;

            int x1 = ((-halfWidth) * cos(rotation) - (-halfHeight) * sin(rotation)) + x;
            int y1 = ((-halfWidth) * sin(rotation) + (-halfHeight) * cos(rotation)) + y;
            int x2 = ((halfWidth)*cos(rotation) - (-halfHeight) * sin(rotation)) + x;
            int y2 = ((halfWidth)*sin(rotation) + (-halfHeight) * cos(rotation)) + y;
            int x3 = ((halfWidth)*cos(rotation) - (halfHeight)*sin(rotation)) + x;
            int y3 = ((halfWidth)*sin(rotation) + (halfHeight)*cos(rotation)) + y;
            int x4 = ((-halfWidth) * cos(rotation) - (halfHeight)*sin(rotation)) + x;
            int y4 = ((-halfWidth) * sin(rotation) + (halfHeight)*cos(rotation)) + y;
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rect;
            GetClientRect(hwnd, &rect);
            HBRUSH brush = (HBRUSH)GetStockObject(WHITE_BRUSH);
            FillRect(hdc, &rect, brush);
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, x2, y2);
            LineTo(hdc, x3, y3);
            LineTo(hdc, x4, y4);
            LineTo(hdc, x1, y1);
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
            case 87: throttle = 1; break;
            case 83: brake = 1; break;
            case 68: steer = 1; break;
            case 65: steer = -1; break;
            }
            InvalidateRect(hwnd, NULL, TRUE);
        } break;
        case WM_KEYUP: {
            //87 up
            //83 down
            //68 right
            //65 left
            switch (wparam) {
            case 87: throttle = 0; break;
            case 83: brake = 0; break;
            case 68: steer = 0; break;
            case 65: steer = 0; break;
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
};
