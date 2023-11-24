#pragma once

#include <synchapi.h>
#include <cmath>

class GameWorld;  // Forward declaration

class GameCore
{
private:
	GameWorld* gameWorld;
	int gameTicks = 0;

public:
	GameCore(GameWorld* gameWorld);

	void tick();
	bool isGameEnded();

private:
	void calculateMovement();
	void calculateRadarsDistance();
	bool checkCarToBorderCollisions();

	friend class RaceCar;
	friend class RaceTrack;
	friend class GameWorld;
};
