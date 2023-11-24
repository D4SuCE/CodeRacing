#pragma once

#include "GameCore.h"
#include "RaceCar.h""
#include "RaceTrack.h"

class GameWorld
{
private:
	GameCore* gameCore;
	RaceCar raceCar;
	RaceTrack raceTrack;

private:
	GameWorld() {
		gameCore = new GameCore(this);
	}

	RaceCar* getNextFrame(float steerWheelInput, float throttleInput, float brakeInput) {
		raceCar.steerWheel = steerWheelInput;
		raceCar.throttle = throttleInput;
		raceCar.brake = brakeInput;
		
		gameCore->tick();
		
		return &raceCar;
	}

	void reset(float handleInput, float throttleInput, float brakeInput) {

	}

private:
	friend class RaceCar;
	friend class RaceTrack;
	friend class GameCore;
};
