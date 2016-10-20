#include "curses.h"
#include "Character.h"
#include "Field.h"
#include <cmath>
#include <vector>
#define ESC 27

using namespace std;

void monsterMove(Screen &scr, Field &game_map, Character &main_char, Character &monster, bool &slow)
{
	if (monster.symbol() == 'Z')
	{
		slow = !slow;
		if (slow) return;
	}

	int max = pow(game_map.height(), 2) + pow(game_map.width(), 2),
		pos = -1, dist = -1;

	if (game_map.emptyCell(monster.row(), monster.col() - 1))
	{
		dist = pow(main_char.row() - monster.row(), 2) + pow(main_char.col() - (monster.col() - 1), 2);
		if (dist < max)
		{
			max = dist;
			pos = 0;
		}
	}
	
	if (game_map.emptyCell(monster.row(), monster.col() + 1))
	{
		dist = pow(main_char.row() - monster.row(), 2) + pow(main_char.col() - (monster.col() + 1), 2);
		if (dist < max)
		{
			max = dist;
			pos = 1;
		}
	}

	if (game_map.emptyCell(monster.row() - 1, monster.col()))
	{
		dist = pow(main_char.row() - (monster.row() - 1), 2) + pow(main_char.col() - monster.col(), 2);
		if (dist < max)
		{
			max = dist;
			pos = 2;
		}
	}
	
	if (game_map.emptyCell(monster.row() + 1, monster.col()))
	{
		dist = pow(main_char.row() - (monster.row() + 1), 2) + pow(main_char.col() - monster.col(), 2);
		if (dist < max)
		{
			max = dist;
			pos = 3;
		}
	}
	
	switch(pos)
	{
	case 0:
		game_map.addAtPos(monster, monster.row(), monster.col() - 1);
		break;
	case 1:
		game_map.addAtPos(monster, monster.row(), monster.col() + 1);
		break;
	case 2:
		game_map.addAtPos(monster, monster.row() - 1, monster.col());
		break;
	case 3:
		game_map.addAtPos(monster, monster.row() + 1, monster.col());
		break;
	}
	game_map.refresh();
}

void gameStart(Screen &scr, Field &game_map, Character &main_char, int ch, Character &dragon, Character &zombie, Character &princess)
{
	if (ch == ESC) return;

	game_map.addCharacter(dragon);
	game_map.addCharacter(zombie);
	game_map.addCharacter(princess);
	game_map.addCharacter(main_char);
	game_map.refresh(); 

	bool slow = false;

	while (ch = getch())
	{
		if (ch == KEY_LEFT) 
		{
			game_map.addAtPos(main_char, main_char.row(), main_char.col() - 1);
			game_map.refresh();
		}
		else if (ch == KEY_RIGHT) 
		{
			game_map.addAtPos(main_char, main_char.row(), main_char.col() + 1);
			game_map.refresh();
		}
		else if (ch == KEY_UP) 
		{
			game_map.addAtPos(main_char, main_char.row() - 1, main_char.col());
			game_map.refresh();
		}
		else if (ch == KEY_DOWN) 
		{
			game_map.addAtPos(main_char, main_char.row() + 1, main_char.col());
			game_map.refresh();
		}
		else if (ch == ESC) 
			break;

		monsterMove(scr, game_map, main_char, dragon, slow);
		monsterMove(scr, game_map, main_char, zombie, slow);

		if (main_char.pos() == zombie.pos() || main_char.pos() == dragon.pos())
		{
			clear();
			scr.add("Game over.\nPress any key to quit.");
			if (getch()) return;
		}
		if (main_char.pos() == princess.pos())
		{
			clear();
			scr.add("You win!\nPress any key to quit.");
			if (getch()) return;
		}
	}
}

void newGame()
{
	Screen scr;
	scr.add("Press any key to start.\nIf you want to quit press ESC.");
	int ch = getch();
	Field game_map(scr.height(), scr.width(), 0, 0);
	Knight knight(game_map.height() / 2, game_map.width() / 2, COLOR_PAIR(1));
	Monster dragon('D', knight.row() + 7, knight.col() + 22, COLOR_PAIR(2));
	Monster zombie('Z', knight.row() - 7, knight.col() - 22, COLOR_PAIR(2));
	Princess princess(2, 2, COLOR_PAIR(3));
	game_map.fill();
	gameStart(scr, game_map, knight, ch, dragon, zombie, princess);
}

int main() 
{
	newGame();
	return 0;
}