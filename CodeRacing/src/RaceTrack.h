#pragma once

#include "DataStructure.h"

class RaceTrack
{
private:
    CoordsVertex firstLine;
    CoordsVertex secondLine;

public:
    RaceTrack() {

    }


private:
    friend class GameWorld;
    friend class GameCore;
};
