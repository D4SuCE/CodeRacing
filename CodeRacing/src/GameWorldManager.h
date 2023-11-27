#pragma once

#include <unordered_map>
#include <string>

#include "RenderCore.h"
#include "GameWorld.h"

class GameWorldManager
{
private:
	RenderCore renderCore;
	GameWorld* offlineWorld;
	std::unordered_map<std::string, GameWorld*> umap;

public:
	void renderWorld(std::string uid);
	GameWorld* createGameWorld();
	GameWorld* createGameWorld(std::string uid);
	void deleteGameWorld(std::string uid);
	void startOfflineGame();
};
