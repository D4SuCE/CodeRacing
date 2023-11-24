#pragma once

#include "DataStructure.h"

class RaceCar
{
public:
    float steerWheel;
    float throttle;
    float brake;
    float mass;
    float speed;
    float rotation;
    Coords position;
    CoordsVertex borders;
    std::vector<Radar> radars;

public:
    RaceCar()
        : steerWheel(0.0f), throttle(0.0f), brake(0.0f),
        mass(1.0f), speed(0.0f), rotation(0.0f)
    {
        position.x = 0.0f;
        position.y = 0.0f;
        borders = setBorderCoords(position);
    }

private:
    inline CoordsVertex setBorderCoords(const Coords& position)
    {
        Coords TL = { position.x - 1, position.y + 2 };
        Coords TR = { position.x + 1, position.y + 2 };
        Coords BL = { position.x - 1, position.y - 2 };
        Coords BR = { position.x + 1, position.y - 2 };
        CoordsVertex corners = { TL, TR, BL, BR };
        return corners;
    }

    friend class GameWorld;
    friend class GameCore;
};
