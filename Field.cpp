#include "Field.h"
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

Screen::Screen()
{
	initscr();
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	getmaxyx(stdscr, _height, _width);
}

Field::Field(int nr_rows, int nr_cols, int row_0, int col_0) 
{
	_w = newwin(nr_rows, nr_cols, row_0, col_0);
	_height = nr_rows;
	_width = nr_cols;
	_row = row_0;
	_col = col_0;
}

void Field::addAtPos(Character &x, int row_0, int col_0)
{
	if ((row_0 >= 0 && row_0 < _height) && (col_0 >= 0 && col_0 < _width))
	{
		char ch = mvwinch(_w, row_0, col_0);
		if (ch == '#')
			return;
		erase(x);
		mvwaddch(_w, row_0, col_0, x.symbol() | A_BOLD | x.color());
		x.newPos(row_0, col_0);
	}
}

bool Field::emptyCell(int row_0, int col_0)
{
	char ch = mvwinch(_w, row_0, col_0); 
	if (ch == '#')
		return FALSE;
	return TRUE;
}

void Field::fill()
{
	ifstream level("level1.txt");

	for (int i = 0; i < 23; i++)
	{
		char str[75];
		level.getline(str, 75);
		mvwaddstr(_w, i, 0, str);
	}

}