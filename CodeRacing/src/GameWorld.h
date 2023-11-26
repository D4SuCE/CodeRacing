#pragma once

#include "GameCore.h"
#include "RaceCar.h"
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

	friend class RaceCar;
	friend class RaceTrack;
	friend class GameCore;
};
