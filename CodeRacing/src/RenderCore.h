#pragma once

#include <windows.h>
#include <stdio.h>
#include <thread>
#include <chrono>
#include <cmath>
#include <queue>

#include "RaceCar.h"

class RenderCore
{
public:
    int started = 0;
    static RaceCar* offlineCar;
    HWND hwnd;
    static std::queue<CoordsVertex*> renderQueueLines;
    static std::queue<CoordsPairR> renderQueueLinesR;
    static std::queue<RaceCar*> renderQueueSquares;

public:
    void addLineToRenderQueue(CoordsVertex* cv);
    void addLineToRenderQueue(CoordsPairR cv);
    void addSquareToRenderQueue(RaceCar* cv);
    void startRender();
    void createWindow();
    void update();

private:
    static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};
