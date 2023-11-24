#pragma once

#include "GameCore.h"
#include "RaceCar.h"
#include "RaceTrack.h"

class GameWorld
{
private:
	GameCore* gameCore;
	RaceCar raceCar;
	RaceTrack raceTrack;

public:
	GameWorld();
	RaceCar* getNextFrame(float steerWheelInput, float throttleInput, float brakeInput);
	void reset(float handleInput, float throttleInput, float brakeInput);

	friend class RaceCar;
	friend class RaceTrack;
	friend class GameCore;
};
