#include <thread>
#include <chrono>

#include "GameWorldManager.h"

GameWorld* GameWorldManager::createGameWorld() {
	return new GameWorld();
}

void GameWorldManager::startOfflineGame() {
	RenderCore rc;
	std::thread t(&RenderCore::createWindow, &rc);
	t.detach();
	//renderCore.createWindow();
	offlineWorld = createGameWorld();
	while (1) {
		RaceCar* raceCar = offlineWorld->getNextFrame(steer,throttle,brake);
		x = raceCar->position.x;
		y = raceCar->position.y;
		rotation = raceCar->rotation;
		InvalidateRect(rc.hwnd, NULL, TRUE);
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}
