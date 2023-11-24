#pragma once
#include <vector>

struct Coords
{
    float x;
    float y;
};

struct Radar
{
    Coords coords;
    float angle;
};

using CoordsVertex = std::vector<Coords>;
