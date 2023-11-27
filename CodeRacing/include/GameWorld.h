#pragma once

#include "RaceCar.h"
#include "GameCore.h"
#include "RaceTrack.h"

class GameWorld
{
public:
	GameCore* gameCore;
	RaceCar raceCar;
	RaceTrack raceTrack;

public:
	GameWorld();
	RaceCar* getNextFrame(float steerWheelInput, float throttleInput, float brakeInput);
	RaceCar* getNextFrame();
	void reset();
};
