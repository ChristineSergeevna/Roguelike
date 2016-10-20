#include "Character.h"

Character::Character(char symbol, int row_0, int col_0, chtype color)
{
	_symbol = symbol;
	_pos.row = row_0;
	_pos.col = col_0;
	_color = color;
}

void Character::newPos(int row_0, int col_0) 
{
	_pos.row = row_0;
	_pos.col = col_0;
}
