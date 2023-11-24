#pragma once

#include <synchapi.h>
#include <cmath>

#include "GameWorld.h"

class GameCore
{
private:
	GameWorld* gameWorld;
	int gameTicks = 0;

public:
	GameCore (GameWorld* gameWorld){
		this->gameWorld = gameWorld;
	}

	void tick() {
		Sleep(16);
		calculateMovement();
		calculateRadarsDistance();
	}

	bool isGameEnded() {
		return checkCarToBorderCollisions();
	}

private:
	void calculateMovement() {
		gameWorld->raceCar.speed += gameWorld->raceCar.throttle - gameWorld->raceCar.brake;
		gameWorld->raceCar.rotation += gameWorld->raceCar.steerWheel / gameWorld->raceCar.speed;

		gameWorld->raceCar.position.x += gameWorld->raceCar.speed * cos(gameWorld->raceCar.rotation);
		gameWorld->raceCar.position.y += gameWorld->raceCar.speed * sin(gameWorld->raceCar.rotation);
	}

	void calculateRadarsDistance() {

	}

	bool checkCarToBorderCollisions() {
		return 0;
	}

private:
	friend class RaceCar;
	friend class RaceTrack;
	friend class GameWorld;
};
