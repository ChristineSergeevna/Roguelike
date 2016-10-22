#pragma once
#include "Character.h"

using namespace std;

class Field;

struct Position 
{
	int x, y;
	Position() : x(0), y(0) {};
	Position(int x, int y) : x(x), y(y) {};
};

static Field* field;
void setField(Field* this_field);

class Field
{
public:
	Field() : width(0), height(0), pos(), game_continues(false) { setField(this); level = -1; };
	~Field() {};

	void read();
	void render();
	void render(BaseObject*);
	void swap(BaseObject*, BaseObject*);
	BaseObject* getObject(int x, int y) { return tiles[y][x]; }
	void removeObject(int x, int y);
	void setNewFireball(Fireball*);

	int width;
	int height;
	int level;
	Position pos;
	bool game_continues;
	vector<vector<BaseObject*>> tiles;
	vector<Character*> characters;
	vector<Fireball*> fireballs;
};