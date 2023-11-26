#include "RenderCore.h"

RaceCar* RenderCore::offlineCar = nullptr;
std::queue<CoordsVertex*> RenderCore::renderQueueLines;
std::queue<CoordsPairR> RenderCore::renderQueueLinesR;
std::queue<RaceCar*> RenderCore::renderQueueSquares;

void RenderCore::addLineToRenderQueue(CoordsVertex* cv) {
    renderQueueLines.push(cv);
}

void RenderCore::addLineToRenderQueue(CoordsPairR cv) {
    renderQueueLinesR.push(cv);
}

void RenderCore::addSquareToRenderQueue(RaceCar* cv) {
    renderQueueSquares.push(cv);
}

void RenderCore::startRender() {
    std::thread t(&RenderCore::createWindow, this);
    t.detach();
}

void RenderCore::createWindow() {
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

void RenderCore::update() {
    InvalidateRect(hwnd, NULL, TRUE);
}
LRESULT CALLBACK RenderCore::WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    switch (msg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rect;
        GetClientRect(hwnd, &rect);
        HBRUSH brush = (HBRUSH)GetStockObject(WHITE_BRUSH);
        FillRect(hdc, &rect, brush);
        while (!RenderCore::renderQueueSquares.empty()) {
            RaceCar* temp = RenderCore::renderQueueSquares.front();
            float x1 = ((-temp->renderWidth/2) * cos(temp->rotation) - (-temp->renderHeight / 2) * sin(temp->rotation)) + temp->position.x;
            float y1 = ((-temp->renderWidth / 2) * sin(temp->rotation) + (-temp->renderHeight / 2) * cos(temp->rotation)) + temp->position.y;
            float x2 = ((temp->renderWidth / 2) * cos(temp->rotation) - (-temp->renderHeight / 2) * sin(temp->rotation)) + temp->position.x;
            float y2 = ((temp->renderWidth / 2) * sin(temp->rotation) + (-temp->renderHeight / 2) * cos(temp->rotation)) + temp->position.y;
            float x3 = ((temp->renderWidth / 2) * cos(temp->rotation) - (temp->renderHeight / 2) * sin(temp->rotation)) + temp->position.x;
            float y3 = ((temp->renderWidth / 2) * sin(temp->rotation) + (temp->renderHeight / 2) * cos(temp->rotation)) + temp->position.y;
            float x4 = ((-temp->renderWidth / 2) * cos(temp->rotation) - (temp->renderHeight / 2) * sin(temp->rotation)) + temp->position.x;
            float y4 = ((-temp->renderWidth / 2) * sin(temp->rotation) + (temp->renderHeight / 2) * cos(temp->rotation)) + temp->position.y;
            //printf("g x: %.1f, y: %.1f\n", x1, y1);
            MoveToEx(hdc, x1, y1, NULL);
            LineTo(hdc, x2, y2);
            LineTo(hdc, x3, y3);
            LineTo(hdc, x4, y4);
            LineTo(hdc, x1, y1);
            RenderCore::renderQueueSquares.pop();
        }
        while (!RenderCore::renderQueueLines.empty()) {
            CoordsVertex* temp = RenderCore::renderQueueLines.front();
            MoveToEx(hdc, temp->front().x, temp->front().y, NULL);
            for (const auto& value : *temp) {
                LineTo(hdc, value.x, value.y);
            }
            RenderCore::renderQueueLines.pop();
        }
        while (!RenderCore::renderQueueLinesR.empty()) {
            CoordsPairR temp = RenderCore::renderQueueLinesR.front();
            MoveToEx(hdc, *temp.first.x, *temp.first.y, NULL);
            LineTo(hdc, temp.second.x, temp.second.y);
            RenderCore::renderQueueLinesR.pop();
        }
        EndPaint(hwnd, &ps);
    } break;
    case WM_KEYDOWN: {
        if (RenderCore::offlineCar) {
            switch (wparam) {
            case 87: RenderCore::offlineCar->throttle = 1; break;
            case 83: RenderCore::offlineCar->brake = 1; break;
            case 68: RenderCore::offlineCar->steerWheel = 1; break;
            case 65: RenderCore::offlineCar->steerWheel = -1; break;
            }
        }
    } break;
    case WM_KEYUP: {
        if (RenderCore::offlineCar) {
            switch (wparam) {
            case 87: RenderCore::offlineCar->throttle = 0; break;
            case 83: RenderCore::offlineCar->brake = 0; break;
            case 68: RenderCore::offlineCar->steerWheel = 0; break;
            case 65: RenderCore::offlineCar->steerWheel = 0; break;
            }
        }
    } break;
    case WM_DESTROY:
        PostQuitMessage(0);
        exit(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wparam, lparam);
    }
    return 0;
}