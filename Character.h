#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include "curses.h"

enum Collision { EMPTY_TILE, WALL, DAMAGE, KNIGHT, ENDGAME, TAKE };

class Character;
class Knight;
class StaticObject;
class Fireball;

class BaseObject
{
public:
	BaseObject(char s, int c, int x, int y) : _symbol(s), _color(c), _x(x), _y(y) {};
	virtual ~BaseObject() {};

	virtual int x() = 0;
	virtual int y() = 0;
	virtual void x(int x) = 0;
	virtual void y(int y) = 0;
	virtual char symbol() = 0;
	virtual int color() = 0;

	virtual Collision collide(BaseObject&) = 0;
	virtual Collision collide(Character&) = 0;
	virtual Collision collide(StaticObject&) = 0;

protected:
	int _x, _y;
	char _symbol;
	int _color;
};

class StaticObject : public BaseObject
{
public:
	StaticObject(char s, int c, int x, int y) : BaseObject(s, c, x, y) {};
	~StaticObject() {};

	virtual int x() { return _x; }
	virtual int y() { return _y; }
	virtual void x(int x) { _x = x; }
	virtual void y(int y) { _y = y; }
	virtual char symbol() { return _symbol; }
	virtual int color() { return _color; }

	virtual Collision collide(BaseObject&) { return WALL; }
	virtual Collision collide(Character&) { return WALL; }
	virtual Collision collide(StaticObject&) { return WALL; }
};

class Floor : public StaticObject
{
public:
	Floor(int x, int y) : StaticObject('.', 0, x, y) {};
	~Floor() {};

	Collision collide(BaseObject&) { return EMPTY_TILE; }
	Collision collide(Character&) { return EMPTY_TILE; }
	Collision collide(StaticObject&) { return EMPTY_TILE; }
};

class Wall : public StaticObject
{
public:
	Wall(int x, int y) : StaticObject('#', 7, x, y) {};
	~Wall() {};
};

class MedicineChest : public StaticObject
{
public:
	MedicineChest(int x, int y) : StaticObject('&', 10, x, y) {};
	~MedicineChest() {};

	void heal(Character*);

	Collision collide(Character&);
};

class Character : public BaseObject
{
public:
	Character(char s, int c, int h, int d, int x, int y) : BaseObject(s, c, x, y), _health(h), _damage(d) {};
	~Character() {};

	virtual int health() { return _health; }
	virtual int damage() { return _damage; }
	virtual void health(int h) { _health = h; }
	virtual void damage(int d) { _damage = d; }

	virtual int x() { return _x; }
	virtual int y() { return _y; }
	virtual void x(int x) { _x = x; }
	virtual void y(int y) { _y = y; }
	virtual char symbol() { return _symbol; }
	virtual int color() { return _color; }

	virtual void attack(Knight&);
	virtual void kill(Character&);
	virtual void Healing(MedicineChest*);

	virtual void move(int x, int y);
	virtual void moveL();
	virtual void moveR();
	virtual void moveU();
	virtual void moveD();

	virtual void shootL();
	virtual void shootR();
	virtual void shootU();
	virtual void shootD();

	virtual Collision collide(BaseObject&);
	virtual Collision collide(Character&);
	virtual Collision collide(StaticObject&);

protected:
	int _health;
	int _damage;
};

class Knight : public Character
{
public:
	Knight(int x, int y) : Character('K', 11, 100, 10, x, y), _armor(5) {};
	~Knight() {};

	int armor() { return _armor; }
	void armor(int a) { _armor = a; }
	void receiveDamage(int damage);
	void attack(Character&);

	void shootL() {};
	void shootR() {};
	void shootU() {};
	void shootD() {};

private:
	int _armor;
};

class Princess : public Character
{
public:
	Princess(int x, int y) : Character('P', 13, 0, 0, x, y) {};
	~Princess() {};
};

class Zombie : public Character
{
public:
	Zombie(int x, int y) : Character('Z', 6, 0, 5, x, y) {};
	~Zombie() {};

	void shootL() {};
	void shootR() {};
	void shootU() {};
	void shootD() {};
};

class Dragon : public Character
{
public:
	Dragon(int x, int y) : Character('D', 12, 0, 15, x, y) {};
	~Dragon() {};
};

class Fireball : public Character
{
public:
	Fireball(int x, int y, int dir_x, int dir_y) : Character('*', 12, 3, 30, x, y), dx(dir_x), dy(dir_y) {};
	~Fireball() {};

	int dx, dy;
};