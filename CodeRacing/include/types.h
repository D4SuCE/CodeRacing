#pragma once

#include <vector>

struct Coords
{
    float x;
    float y;
};

struct CoordsR
{
    float* x;
    float* y;
};

using CoordsPairR = std::pair<CoordsR, Coords>;
using CoordsPair = std::pair<Coords, Coords>;
using CoordsChain = std::vector<CoordsPair>;
using CoordsVertex = std::vector<Coords>;
using PointAnglePair = std::pair<CoordsPair, float>;