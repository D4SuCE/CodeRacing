#include "GameCore.h"
#include "GameWorld.h"

GameCore::GameCore(GameWorld* gameWorld) {
	this->gameWorld = gameWorld;
}

void GameCore::tick() {
	Sleep(16);
	calculateMovement();
	calculateRadarsDistance();
}

bool GameCore::isGameEnded() {
	return checkCarToBorderCollisions();
}

void GameCore::calculateMovement() {
	gameWorld->raceCar.speed += gameWorld->raceCar.throttle - gameWorld->raceCar.brake;
	gameWorld->raceCar.rotation += gameWorld->raceCar.steerWheel / gameWorld->raceCar.speed;

	gameWorld->raceCar.position.x += gameWorld->raceCar.speed * cos(gameWorld->raceCar.rotation);
	gameWorld->raceCar.position.y += gameWorld->raceCar.speed * sin(gameWorld->raceCar.rotation);
}

void GameCore::calculateRadarsDistance() {
    // Your code...
}

bool GameCore::checkCarToBorderCollisions() {
	return 0;
}