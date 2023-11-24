#pragma once

#include "RenderCore.h"
#include "GameWorld.h"

class GameWorldManager
{
private:
	RenderCore renderCore;
	GameWorld* offlineWorld;

public:
	GameWorld* createGameWorld();
	void startOfflineGame();
};
