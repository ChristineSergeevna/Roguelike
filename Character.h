#ifndef CHARACTER_H
#define CHARACTER_H

#include "curses.h"
using namespace std;

class _cell
{
public:
	int row;
	int col;

	bool operator==(const _cell p)
	{
		return (row == p.row) && (col == p.col);
	}
};

class Character 
{
	_cell _pos;
	int _row, _col;
	char _symbol;
	chtype _color;
public:
 	Character(char symbol, int row_0, int col_0, chtype color);
	~Character() { _symbol = ' '; }
	
 	void newPos(int row_0, int col_0);  
	_cell pos() { return _pos; }
	int row() { return _pos.row; } 
	int col() { return _pos.col; } 
	char symbol() { return _symbol; } 
	chtype color() { return _color; }
	bool collide(Character &character) { return (_pos == character.pos()); }
};

class Knight : public Character
{
	_cell _pos;
	int _row, _col;
	char _symbol;
	chtype _color;
public:
	Knight(int row_0, int col_0, chtype color) : Character('K', row_0, col_0, color) {}
};

class Monster : public Character
{
	_cell _pos;
	int _row, _col;
	char _symbol;
	chtype _color;
public:
	Monster(char symbol, int row_0, int col_0, chtype color) : Character(symbol, row_0, col_0, color) {}
};

class Princess : public Character
{
	_cell _pos;
	int _row, _col;
	char _symbol;
	chtype _color;public:
	Princess(int row_0, int col_0, chtype color) : Character('P', row_0, col_0, color) {}
};
#endif