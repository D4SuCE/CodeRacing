#include "GameWorld.h"

GameWorld::GameWorld() {
	gameCore = new GameCore(this);
}

RaceCar* GameWorld::getNextFrame(float steerWheelInput, float throttleInput, float brakeInput) {
	raceCar.steerWheel = steerWheelInput;
	raceCar.throttle = throttleInput;
	raceCar.brake = brakeInput;

	gameCore->tick();

	return &raceCar;
}

void GameWorld::reset(float handleInput, float throttleInput, float brakeInput) {
	// Your code...
}
