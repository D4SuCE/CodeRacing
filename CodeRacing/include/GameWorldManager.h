#pragma once


#include <string>
#include "RenderCore.h"
#include "GameWorld.h"
#include <unordered_map>

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
