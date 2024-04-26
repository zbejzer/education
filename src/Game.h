#pragma once

#include <list>

#include "Entity.h"

using namespace std;

class Game
{
	static Game* instance;
	list<Entity*> entities;
	double board_scale;

public:
	char quit;

	Game();

	static Game* getInstance();
	static void setInstance(Game* new_instance);
	static void destroyInstance(Game* instance);
	static void destroyInstance();

	void nextTurn();
	void registerEntity(Entity *entity);
	const list<Entity*>& getEntities();
	void setBoardScale(const double& scale);
	const double& getBoardScale() const;
};