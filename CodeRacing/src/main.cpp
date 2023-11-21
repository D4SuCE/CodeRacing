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

class Car
{
private:
    float turnWheel;
    float gaz;
    float brakes;
    float massa;
    float ratation;
    Coords center;
    CoordsVertex borders;
    std::vector<Radar> radars;

public:
    Car()
        : turnWheel(0.0f), gaz(0.0f), brakes(0.0f),
        massa(1.0f), ratation(0.0f)
    {
        center.x = 0.0f;
        center.y = 0.0f;
        borders = setBorderCoords(center);
    }

private:
    CoordsVertex setBorderCoords(const Coords& center)
    {
        Coords TL = { center.x - 1, center.y + 2 };
        Coords TR = { center.x + 1, center.y + 2 };
        Coords BL = { center.x - 1, center.y - 2 };
        Coords BR = { center.x + 1, center.y - 2 };
        CoordsVertex corners = { TL, TR, BL, BR };
        return corners;
    }
};

struct Map
{
    CoordsVertex firstLine;
    CoordsVertex secondLine;
};

class SharedMemory
{
private:
    Car car;
    Map map;

public:
    SharedMemory() {}
    ~SharedMemory() {}

    const Map& getMap()
    {
        return map;
    }

    /*const CoordsVertex& getCarPoz()
    {
        return *car.poz;
    }

    const std::vector<Radar>& getCarRadars()
    {
        return *car.radars;
    }

    void setCarPoz(const Coords& offset)
    {
        for (auto& coord : car.poz)
        {
            coord.x += offset.x;
            coord.y += offset.y;
        }
    }*/
};

/*
Coords finish = {Map::firstLine.back(), Map::secondLine.back()};

std::vector<std::pair<float, float>> poz;
poz[0].first;
poz[0].second;

std::vector<Coords> poz;
poz[0].x;
poz[0].y;
*/

int main()
{

    return 0;
}