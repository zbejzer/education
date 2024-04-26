#pragma once
class Game
{
	static Game* instance;

public:
	char quit;

	Game();

	static Game* getInstance();
	static void setInstance(Game* new_instance);
	static void destroyInstance(Game* instance);
	static void destroyInstance();

	void nextTurn();
};