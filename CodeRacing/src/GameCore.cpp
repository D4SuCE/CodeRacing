#include "GameCore.h"
#include "GameWorld.h"

GameCore::GameCore(GameWorld* gameWorld) {
	this->gameWorld = gameWorld;
}

void GameCore::tick() {
	calculateMovement();
	calculateRadarsDistance();
}

bool GameCore::isGameEnded() {
	return checkCarToBorderCollisions();
}

void GameCore::calculateMovement() {
	float speed = gameWorld->raceCar.speed + gameWorld->raceCar.throttle - gameWorld->raceCar.brake;
	gameWorld->raceCar.speed = speed < 0 ? 0 : speed;

	if (gameWorld->raceCar.speed != 0) {
		gameWorld->raceCar.rotation += gameWorld->raceCar.steerWheel / gameWorld->raceCar.speed;

		gameWorld->raceCar.position.x += gameWorld->raceCar.speed * cos(gameWorld->raceCar.rotation);
		gameWorld->raceCar.position.y += gameWorld->raceCar.speed * sin(gameWorld->raceCar.rotation);
	}
}

void GameCore::calculateRadarsDistance() {
	for (auto& radar : gameWorld->raceCar.radars) {
		radar.rayHitDistance = radar.rayLength;
		radar.rayHitPoint.x = gameWorld->raceCar.position.x + radar.rayLength * cos(gameWorld->raceCar.rotation + radar.angleOffset * M_PI / 180.0);
		radar.rayHitPoint.y = gameWorld->raceCar.position.y + radar.rayLength * sin(gameWorld->raceCar.rotation + radar.angleOffset * M_PI / 180.0);
	}

	for (const auto& coord : gameWorld->raceTrack.firstLineChain) {
		for (auto& radar : gameWorld->raceCar.radars) {
			lineIntersection(&radar, gameWorld->raceCar.position.x, gameWorld->raceCar.position.y, gameWorld->raceCar.position.x + radar.rayLength * cos(gameWorld->raceCar.rotation + radar.angleOffset * M_PI / 180.0), gameWorld->raceCar.position.y + radar.rayLength * sin(gameWorld->raceCar.rotation + radar.angleOffset * M_PI / 180.0), coord.first.x, coord.first.y, coord.second.x, coord.second.y);
		}
	}

	for (const auto& coord : gameWorld->raceTrack.secondLineChain) {
		for (auto& radar : gameWorld->raceCar.radars) {
			lineIntersection(&radar, gameWorld->raceCar.position.x, gameWorld->raceCar.position.y, gameWorld->raceCar.position.x + radar.rayLength * cos(gameWorld->raceCar.rotation + radar.angleOffset * M_PI / 180.0), gameWorld->raceCar.position.y + radar.rayLength * sin(gameWorld->raceCar.rotation + radar.angleOffset * M_PI / 180.0), coord.first.x, coord.first.y, coord.second.x, coord.second.y);
		}
	}
}

bool GameCore::checkCarToBorderCollisions() {
	std::pair<float, float> topLeft = std::make_pair(gameWorld->raceCar.position.x - gameWorld->raceCar.renderWidth / 2.0f, gameWorld->raceCar.position.y - gameWorld->raceCar.renderHeight / 2.0f);
	
	for (const auto& coord : gameWorld->raceTrack.firstLineChain) {
		if (lineRectangleCollide(coord.first.x, coord.first.y, coord.second.x, coord.second.y, topLeft.first, topLeft.second, gameWorld->raceCar.renderWidth, gameWorld->raceCar.renderHeight, gameWorld->raceCar.rotation * M_PI / 180))
			return 1;
	}

	for (const auto& coord : gameWorld->raceTrack.secondLineChain) {
		if (lineRectangleCollide(coord.first.x, coord.first.y, coord.second.x, coord.second.y, topLeft.first, topLeft.second, gameWorld->raceCar.renderWidth, gameWorld->raceCar.renderHeight, gameWorld->raceCar.rotation * M_PI / 180))
			return 1;
	}

	return 0;
}


bool GameCore::ccw(Coords A, Coords B, Coords C) {
	return (C.y - A.y) * (B.x - A.x) > (B.y - A.y) * (C.x - A.x);
}

bool GameCore::intersect(Coords A, Coords B, Coords C, Coords D) {
	return ccw(A, C, D) != ccw(B, C, D) && ccw(A, B, C) != ccw(A, B, D);
}

Coords GameCore::rotatePoint(float x, float y, float angle) {
	float px = x - gameWorld->raceCar.position.x;
	float py = y - gameWorld->raceCar.position.y;

	float qx = px * cos(-angle) - py * sin(-angle);
	float qy = px * sin(-angle) + py * cos(-angle);

	Coords coords;
	coords.x = qx + gameWorld->raceCar.position.x;
	coords.y = qy + gameWorld->raceCar.position.y;

	return coords;
}

bool GameCore::lineRectangleCollide(float x1, float y1, float x2, float y2, float rx, float ry, float rw, float rh, float angle) {
	Coords rectangle_points[] = { rotatePoint(rx, ry, angle), rotatePoint(rx + rw, ry, angle), rotatePoint(rx + rw, ry + rh, angle), rotatePoint(rx, ry + rh, angle) };

	Coords lineSegment1;
	lineSegment1.x = x1;
	lineSegment1.y = y1;

	Coords lineSegment2;
	lineSegment2.x = x2;
	lineSegment2.y = y2;

	for (size_t i = 0; i < 4; i++) {
		if (intersect(lineSegment1, lineSegment2, rectangle_points[i], rectangle_points[(i + 1) % 4]))
			return 1;
	}

	return 0;
}

void GameCore::lineIntersection(RaceCar::Radar* radar, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	float denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (denom == 0)
		return;

	float px = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denom;
	float py = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denom;

	if ((std::min(x1, x2) <= px && px <= std::max(x1, x2)) && (std::min(y1, y2) <= py && py <= std::max(y1, y2)) && (std::min(x3, x4) <= px && px <= std::max(x3, x4)) && (std::min(y3, y4) <= py && py <= std::max(y3, y4))) {
		float distance = sqrt(pow((px - x1), 2) + pow((py - y1), 2));
		if (distance < radar->rayHitDistance) {
			radar->rayHitDistance = distance;
			radar->rayHitPoint.x = px;
			radar->rayHitPoint.y = py;
		}
	}
}