#pragma once

#include <cmath>
#include <algorithm>
#include "DataStructure.h"
#include "RaceCar.h"

#define M_PI 3.14159265358979323846

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
	
	bool ccw(Coords A, Coords B, Coords C);
	bool intersect(Coords A, Coords B, Coords C, Coords D);
	Coords rotatePoint(float x, float y, float angle);
	bool lineRectangleCollide(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh, float angle);
	void lineIntersection(RaceCar::Radar* car, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

	friend class RaceCar;
	friend class RaceTrack;
	friend class GameWorld;
};
