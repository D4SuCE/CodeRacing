#pragma once

#include "types.h"

class RaceCar
{
public:
    struct Radar {
        CoordsR coords;
        Coords rayHitPoint;
        float rayHitDistance;
        float rayLength;
        float angleOffset;
        RaceCar* car;  // Pointer to the enclosing RaceCar object

        // Constructor
        Radar(RaceCar* c, float length, float offset) : car(c), rayLength(length), angleOffset(offset) {
            coords.x = &car->position.x;
            coords.y = &car->position.y;
        }

        // Member function to compute the angle
        float angle() {
            return car->rotation + angleOffset;
        }
    };

    int finishStatus;
    float distanceDriven;
    float tickCount;
    float steerWheel;
    float throttle;
    float brake;
    float mass;
    float speed;
    float rotation;
    float renderWidth;
    float renderHeight;
    Coords position;
    std::vector<Radar> radars;

public:
    RaceCar()
        : finishStatus(0), distanceDriven(0.0f), tickCount(0.0f), steerWheel(0.0f), throttle(0.0f), brake(0.0f),
        mass(1.0f), speed(0.0f), rotation(0.0f), renderWidth(50.0f), renderHeight(25.0f)
    {
        position.x = 425;
        position.y = 227;
        
        Radar radar1(this, 100, -90);
        radars.push_back(radar1);

        Radar radar2(this, 100, -45);
        radars.push_back(radar2);
        
        Radar radar3(this, 100, 0);
        radars.push_back(radar3);
        
        Radar radar4(this, 100, 45);
        radars.push_back(radar4);
        
        Radar radar5(this, 100, 90);
        radars.push_back(radar5);
    }
};
