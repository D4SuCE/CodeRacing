#pragma once

#include "types/types.h"

class Car
{
private:
    float turnWheel;
    float gaz;
    float brakes;
    float massa;
    float ratation;
    float speed;
    Coords center;
    std::vector<float> radars;

public:
    Car()
        : turnWheel(0.3f), gaz(0.7f), brakes(0.0f),
        massa(1.0f), ratation(3.0f), speed(120.0f)
    {
        center.x = 1.0f;
        center.y = 0.1f;
        radars.push_back(60.0f);
        radars.push_back(45.0f);
        radars.push_back(30.0f);
        radars.push_back(15.0f);
        radars.push_back(0.0f);
    }

    std::vector<float> getServerInfo()
    {
        std::vector<float> info;
        info.push_back(ratation);
        info.push_back(speed);
        for (int i = 0; i < radars.size(); ++i)
        {
            info.push_back(radars[i]);
        }

        return info;
    }

    std::vector<float> getClientInfo()
    {
        std::vector<float> info;
        info.push_back(turnWheel);
        info.push_back(gaz);
        info.push_back(brakes);
        return info;
    }

    void setClientInfo(const std::vector<float>& data)
    {
        turnWheel = data[0];
        gaz = data[1];
        brakes = data[2];
    }

    void setServerInfo(const std::vector<float>& data)
    {
        ratation = data[0];
        speed = data[1];
        radars[0] = data[2];
        radars[1] = data[3];
        radars[2] = data[4];
        radars[3] = data[5];
        radars[4] = data[6];
    }
};