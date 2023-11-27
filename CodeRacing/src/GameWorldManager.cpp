#include <chrono>
#include <string>
#include <unordered_map>
#include "GameWorldManager.h"

GameWorld* GameWorldManager::createGameWorld(std::string uid) {
	GameWorld* gameworld = new GameWorld();

	umap[uid] = gameworld;

	return gameworld;
}

GameWorld* GameWorldManager::createGameWorld() {
	return new GameWorld();
}

void GameWorldManager::deleteGameWorld(std::string uid) {
	delete(umap[uid]);

	umap.erase(uid);
}

void GameWorldManager::renderWorld(std::string uid) {
	renderCore.startRender();
	renderCore.offlineCar = &umap[uid]->raceCar;

	renderCore.addSquareToRenderQueue(&umap[uid]->raceCar);
	renderCore.addLineToRenderQueue(&umap[uid]->raceTrack.firstLine);
	renderCore.addLineToRenderQueue(&umap[uid]->raceTrack.secondLine);

	CoordsPairR radarLines;
	for (auto& radar : umap[uid]->raceCar.radars) {
		if (radar.rayHitDistance != 0) {
			renderCore.addLineToRenderQueue({ radar.coords, radar.rayHitPoint });
		}
	}
	renderCore.update();
}

void GameWorldManager::startOfflineGame() {
	renderCore.startRender();
	offlineWorld = createGameWorld();
	renderCore.offlineCar = &offlineWorld->raceCar;

	while (1) {
		offlineWorld->getNextFrame();
		renderCore.addSquareToRenderQueue(&offlineWorld->raceCar);
		renderCore.addLineToRenderQueue(&offlineWorld->raceTrack.firstLine);
		renderCore.addLineToRenderQueue(&offlineWorld->raceTrack.secondLine);
		

		CoordsPairR radarLines;

		for (auto& radar : offlineWorld->raceCar.radars) {
			if (radar.rayHitDistance != 0) {
				renderCore.addLineToRenderQueue({ radar.coords, radar.rayHitPoint });
			}
		}

		renderCore.update();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}
