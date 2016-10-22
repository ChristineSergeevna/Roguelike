#pragma once
#include "Game.h"

void Game::init() 
{
	field.read();
	field.render();
	state = 0;
	knight = static_cast<Character*>(field.tiles[field.pos.y][field.pos.x]);
	field.game_continues = true;
	srand(time(0));
}

void Game::start() 
{
	int key;
	while (field.game_continues) 
	{
		key = getch();
		if (key == KEY_LEFT) knight->moveL();
		if (key == KEY_RIGHT) knight->moveR();
		if (key == KEY_UP) knight->moveU();
		if (key == KEY_DOWN) knight->moveD();
		if (key == ESC) return;
		moveMonsters();
		moveFireball();
	}
	switch (state) 
	{
	case 1: 
		clear();
		mvprintw(field.height / 2, field.width / 2, "Level complete!");
		break;
	case 2: 
		clear();
		mvprintw(field.height / 2, field.width / 2 + 5, "You lose");
		break;
	default: 
		break;
	}
	mvprintw(4 + field.height / 2, field.width / 2, "Press R to restart");
	mvprintw(6 + field.height / 2, field.width / 2, "Press N for next level");
	mvprintw(8 + field.height / 2, field.width / 2, "Press ESC to quit");
	while (key = getch())
	{
		if (key == 'r')
		{
			end();
			init();
			start();
		}
		else if (key == 'n')
		{
			end();
			init();
			start();
		}
		else if (key == ESC)
			return;
	}
}

void Game::end() 
{
	while (field.characters.size()) 
		field.characters.pop_back();
	while (field.fireballs.size()) 
		field.fireballs.pop_back();
	for (size_t i = field.tiles.size() - 1; i > 0; --i) 
	{
		for (size_t j = 0; j < field.tiles[i].size(); ++j)
			delete field.tiles[i][j];
		field.tiles.pop_back();
	}
}

void Game::moveMonsters() 
{
	for (int i = field.characters.size() - 1; i >= 0; --i) 
	{
		if (!field.game_continues) 
			return;
		
		if (abs(field.characters[i]->x() - knight->x()) > 30 || abs(field.characters[i]->y() - knight->y()) > 30 || rand() % 10 == 0)
			continue;
		if ((field.characters[i]->symbol() == 'Z' && rand() % 2) || (field.characters[i]->symbol() == 'D'))
		{
			if (abs(field.characters[i]->x() - knight->x()) > abs(field.characters[i]->y() - knight->y()))
			{
				if (field.characters[i]->x() < knight->x())
				{
					if (rand() % 2)
						field.characters[i]->shootR();
					field.characters[i]->moveR();
				}
				else if (field.characters[i]->x() > knight->x())
				{
					if (rand() % 2)
						field.characters[i]->shootL();
					field.characters[i]->moveL();
				}
			}
			else
			{
				if (field.characters[i]->y() < knight->y())
				{
					if (rand() % 2)
						field.characters[i]->shootD();
					field.characters[i]->moveD();
				}
				else if (field.characters[i]->y() > knight->y())
				{
					if (rand() % 2)
						field.characters[i]->shootU();
					field.characters[i]->moveU();
				}
			}
		}
	}
}

void Game::moveFireball() 
{
	int i = 0, size = field.fireballs.size();
	while (i < size) 
	{
		if (!field.game_continues) 
			return;
		Fireball* p = field.fireballs[i];
		p->move(p->x() + p->dx, p->y() + p->dy);
		if (size > field.fireballs.size())
			size = field.fireballs.size();
		else 
			++i;
	}
}

void Game::showHealth(Character* actor, string name, int x, int y) 
{
	string health = name + " health: " + to_string(actor->health());
	mvprintw(y, x, ""); 
	clrtoeol();
	mvprintw(y, x, health.c_str());
}

void main()
{
	Game game;
	game.init();
	game.start();
	game.end();
}