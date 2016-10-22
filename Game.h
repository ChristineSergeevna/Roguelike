#pragma once
#include "Field.h"

#define ESC 27 

class Game;

static Game* game;
void setGame(Game* this_game);

class Game
{
public:
	Game() : state(0) { setGame(this); };
	~Game() {};

	void init();
	void start();
	void end();
	void moveMonsters();
	void moveFireball();
	void showHealth(Character*, std::string name, int x, int y);

	void setWin() { state = 1; };
	void setLose() { state = 2; };

	Field field;
	Character* knight;
	int state;
};