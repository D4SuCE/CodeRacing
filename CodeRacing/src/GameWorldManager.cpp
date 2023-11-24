#include "GameWorldManager.h"

GameWorld* GameWorldManager::createGameWorld() {
	return new GameWorld();
}

void GameWorldManager::startOfflineGame() {
	//renderCore.createWindow();
	offlineWorld = createGameWorld();
}
