#pragma once
#include "Character.h"
#include "Field.h"
#include "Game.h"

void setField(Field* this_field) { field = this_field; }
void setGame(Game* this_game) { game = this_game; }

void Character::move(int x, int y)
{
	BaseObject* other = field->getObject(x, y);

	switch (this->collide(*other))
	{
	case EMPTY_TILE: 
		field->swap(this, other); 
		break;
	case DAMAGE:
		this->attack(static_cast<Knight&>(*other));
		if (this->symbol() == '*')
			field->removeObject(this->x(), this->y());
		break;
	case KNIGHT:
		static_cast<Knight&>(*this).attack(static_cast<Character&>(*other));
		break;
	case TAKE:
		this->Healing(static_cast<MedicineChest*>(other));
		field->swap(this, field->getObject(x, y));
		break;
	case ENDGAME:
		field->removeObject(this->x(), this->y());
		game->setWin();
	default:
		if (this->symbol() == '*')
			field->removeObject(this->x(), this->y());
		break;
	}
	refresh();
}

void Character::moveL() { move(x() - 1, y()); }
void Character::moveR() { move(x() + 1, y()); }
void Character::moveU() { move(x(), y() - 1); }
void Character::moveD() { move(x(), y() + 1); }

void Character::shootL() { field->setNewFireball(new Fireball(this->x() - 1, this->y(), -1, 0)); }
void Character::shootR() { field->setNewFireball(new Fireball(this->x() + 1, this->y(), 1, 0)); }
void Character::shootU() { field->setNewFireball(new Fireball(this->x(), this->y() - 1, 0, -1)); }
void Character::shootD() { field->setNewFireball(new Fireball(this->x(), this->y() + 1, 0, 1)); }

Collision MedicineChest::collide(Character& other) 
{
	if (other.symbol() == 'K') 
		return TAKE;
	return WALL;
};

Collision Character::collide(BaseObject& other) 
{
	return other.collide(*this);
}

Collision Character::collide(Character& other) 
{
	if ((this->symbol() == 'K' && other.symbol() == 'P') || (this->symbol() == 'P' && other.symbol() == 'K')) return ENDGAME;
	if ((this->symbol() == 'K' && (other.symbol() == 'Z' || other.symbol() == 'D')) ||
	(other.symbol() == '*' && (this->symbol() == 'K' || this->symbol() == 'Z' || this->symbol() == 'D'))) return DAMAGE;
	if ((this->symbol() == 'Z' || this->symbol() == 'D') && other.symbol() == 'K') return KNIGHT;
	return WALL;
}

Collision Character::collide(StaticObject& other) 
{
	return other.collide(*this);
}

void Character::attack(Knight& other)
{
	other.receiveDamage(_damage);
	if (other.health() <= 0)
		kill(other);
}

void Knight::attack(Character& other)
{
	this->receiveDamage(_damage);
	if (this->health() <= 0)
		kill(*this);
}

void Knight::receiveDamage(int damage) 
{
	if (_armor - damage < 0) 
		_health -= damage - _armor;
	game->showHealth(this, "Knight", 0, 0);
}

void Character::kill(Character& other) 
{
	field->removeObject(other.x(), other.y());
	if (other.symbol() == 'K')
		game->setLose();
}

void Character::Healing(MedicineChest* other)
{
	MedicineChest* hp = other;
	hp->heal(this);
	game->showHealth(this, "Knight", 0, 0);
	field->removeObject(other->x(), other->y());
}

void MedicineChest::heal(Character* other) { other->health(100); }