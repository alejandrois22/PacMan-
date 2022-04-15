#pragma once

#include "BoundBlock.h"
#include "Dot.h"
class EntityManager {

public:
	~EntityManager();
	std::vector<Entity*> entities;
	std::vector<BoundBlock*> boundBlocks;
	std::vector<Entity*> ghosts;
	void tick();
	void render();
	void setKillable(bool);
	int getDots();

private:
	bool killable = false;
	int killableCounter;
};