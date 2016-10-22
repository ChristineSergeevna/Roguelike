#pragma once
#include "Field.h"

using namespace std;

void Field::read() 
{
	if (level != 3) level++;
	string file_name = to_string(level) + ".txt";
	ifstream fin(file_name.c_str());
	vector<string> scheme;
	string line;
	while (getline(fin, line))
		scheme.push_back(line);
	fin.close();

	height = scheme.size();
	width = scheme.front().size();

	tiles.resize(height);
	for (size_t i = 0; i < tiles.size(); ++i) 
	{
		tiles[i] = vector<BaseObject*>(width);
		for (size_t j = 0; j < tiles[i].size(); ++j)
			switch (scheme[i][j]) 
			{
			case '#':     
				tiles[i][j] = new Wall(j, i); 
				break;
			case '.':    
				tiles[i][j] = new Floor(j, i); 
				break;
			case 'P': 
				tiles[i][j] = new Princess(j, i); 
				break;
			case 'K':   
				tiles[i][j] = new Knight(j, i); 
				pos.y = i; pos.x = j; 
				break;
			case 'Z':   
				tiles[i][j] = new Zombie(j, i); 
				characters.push_back(static_cast<Character*>(tiles[i][j])); 
				break;
			case 'D':   
				tiles[i][j] = new Dragon(j, i); 
				characters.push_back(static_cast<Character*>(tiles[i][j])); 
				break;
			case '&': 
				tiles[i][j] = new MedicineChest(j, i);
			}
	}
}

void Field::swap(BaseObject* o1, BaseObject* o2) 
{
	int x = o2->x(), y = o2->y();
	tiles[o1->y()][o1->x()] = o2;
	tiles[o2->y()][o2->x()] = o1;
	o2->x(o1->x()); o2->y(o1->y());
	o1->x(x); o1->y(y);
	if (o1->symbol() == 'K') 
	{ 
		pos.x = o1->x(); 
		pos.y = o1->y(); 
	}
	if (o2->symbol() == 'K') 
	{ 
		pos.x = o2->x(); 
		pos.y = o2->y(); 
	}
	render(o1); render(o2);
	refresh();
}

void Field::render() 
{
	initscr();
	clear();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	curs_set(0);
	resize_term(height + 10 + height % 2, width + 20 + !(width % 2));
	start_color();

	for (size_t i = 0; i < tiles.size(); ++i)
		for (size_t j = 0; j < tiles[i].size(); ++j)
			render(tiles[i][j]);

	refresh();
}

void Field::render(BaseObject* t) 
{
	init_pair(t->symbol(), t->color(), 0);
	attron(COLOR_PAIR(t->symbol()));
	mvaddch(t->y() + 5, t->x() + 10, t->symbol());
	attroff(COLOR_PAIR(t->symbol()));
}

void Field::setNewFireball(Fireball* other) 
{
	if (tiles[other->y()][other->x()]->collide(*other) == EMPTY_TILE) 
	{
		delete tiles[other->y()][other->x()];
		tiles[other->y()][other->x()] = other;
		fireballs.push_back(other);
		render(other);
		refresh();
	}
}

void Field::removeObject(int x, int y)
{
	if (tiles[y][x]->symbol() == '*')
	{
		for (size_t i = 0; i < fireballs.size(); ++i)
			if (tiles[y][x] == fireballs[i])
				fireballs.erase(fireballs.begin() + i);
	}
	else if (tiles[y][x]->symbol() == 'K')
	{
		game_continues = false;
		return;
	}
	delete tiles[y][x];
	tiles[y][x] = new Floor(x, y);
	render(tiles[y][x]);
	refresh();
}