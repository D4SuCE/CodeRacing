//#include <thread>
#include <chrono>

#include "GameWorldManager.h"

GameWorld* GameWorldManager::createGameWorld() {
	return new GameWorld();
}

void GameWorldManager::startOfflineGame() {
	//RenderCore rc;
	//std::thread t(&RenderCore::createWindow, &rc);
	//t.detach();
	renderCore.startRender();
	offlineWorld = createGameWorld();
	renderCore.offlineCar = &offlineWorld->raceCar;
	while (1) {
		offlineWorld->getNextFrame();
		//renderCore.offlineCar = raceCar;
		//x = raceCar->position.x;
		//y = raceCar->position.y;
		//rotation = raceCar->rotation;
		renderCore.addSquareToRenderQueue(&offlineWorld->raceCar);
		renderCore.addLineToRenderQueue(&offlineWorld->raceTrack.firstLine);
		renderCore.addLineToRenderQueue(&offlineWorld->raceTrack.secondLine);
		

		CoordsPairR radarLines;
		for (auto& radar : offlineWorld->raceCar.radars) {
			//Coords coords1, coords2;
			// ... (initialize coords1 and coords2) ...
			//CoordsPairR pair = { radar.coords, radar.rayHitPoint };
			//radarLines.push_back();
			if (radar.rayHitDistance != 0) {
				//printf("%f ", radar.rayHitDistance);
				renderCore.addLineToRenderQueue({ radar.coords, radar.rayHitPoint });
			}
		}
		renderCore.update();
		//InvalidateRect(rc.hwnd, NULL, TRUE);
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}
