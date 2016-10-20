#include "curses.h"
#include "Character.h"

#ifndef FIELD_H
#define FIELD_H

class Screen 
{
	int _height, _width;
public:
 	Screen();
	~Screen() { endwin(); }
	void add(const char *message) { printw(message); }
	int height() { return _height; }
	int width() { return _width; }
};

class Field 
{
	int _height, _width;
	int _row, _col;
	WINDOW *_w; 
public:
	Field(int nr_rows, int nr_cols, int row_0, int col_0);
	~Field() { delwin(_w); }

	int height() { return _height; } 
	int width() { return _width; } 
	int row() { return _row; } 
	int col() { return _col; }

	void fill();

	bool emptyCell(int row_0, int col_0);
	void refresh() { wrefresh(_w); }
	void addCharacter(Character &x) { mvwaddch(_w, x.row(), x.col(), x.symbol() | x.color() | A_BOLD); }
	void erase(Character &x) { mvwaddch(_w, x.row(), x.col(), ' '); } 
	void addAtPos(Character &x, int row_0, int col_0);
};
#endif