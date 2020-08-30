#pragma warning(disable : 4996)
#include "Hero.h"
#include <conio.h>
#include <iostream>

#define LEN 255

Hero::Hero() {
	char* temp = new char[LEN]{ "-" };
	this->name = setname(temp);
	this->x = 0;
	this->y = 0;
	this->health = 100;
}
Hero::Hero(const char name[])
{
	char* temp = new char[LEN] {};
	strcpy(temp, name);
	this->name = setname(temp);
	this->x = 0;
	this->y = 0;
	this->health = 100;
}

Hero::~Hero() {
	delete[] name;
}

char* Hero::setname(char* name) {
	this->name = name;
	return this->name;
}

void Hero::moving(field& FieldG) {
	assert(health >= 0 && health <= 100);
	assert(name);
	assert(x >= 0 && x < FieldG.getHeight() && y >= 0 && y < FieldG.getWidth());
	int k1;
	k1 = _getch();
	if (k1 == 0xE0) k1 = _getch();
	int prev_x = this->x;
	int prev_y = this->y;
	switch (k1)
	{
	case 0x4B: //75 влево
		if (this->y - 1 < 0) {
			this->y = 0;
			return;
		}
		else {
			if (FieldG.checkList(this->x, this->y - 1)) {
				this->y--;
				FieldG.updateList(prev_x, prev_y, this->x, this->y);
				FieldG.updatefield(FieldG, prev_x, prev_y, this->x, this->y);
			}
		}
		break;
	case 0x4D: //77 вправо
		if (this->y + 1 == FieldG.getWidth()) {
			this->y = FieldG.getWidth() - 1;
			return;
		}
		else {
			if (FieldG.checkList(this->x, this->y + 1)) {
				this->y++;
				FieldG.updateList(prev_x, prev_y, this->x, this->y);
				FieldG.updatefield(FieldG, prev_x, prev_y, this->x, this->y);
			}
		}

		break;
	case 0x48: //72 вверх
		if (this->x - 1 < 0) {
			this->x = 0;
			return;
		}
		else {
			if (FieldG.checkList(this->x - 1, this->y)) {
				this->x--;
				FieldG.updateList(prev_x, prev_y, this->x, this->y);
				FieldG.updatefield(FieldG, prev_x, prev_y, this->x, this->y);
			}
		}
		break;
	case 0x50: //80 вниз
		if (this->x + 1 == FieldG.getHeight()) {
			this->x = FieldG.getHeight() - 1;
			return;
		}
		else {
			if (FieldG.checkList(this->x + 1, this->y)) {
				this->x++;
				FieldG.updateList(prev_x, prev_y, this->x, this->y);
				FieldG.updatefield(FieldG, prev_x, prev_y, this->x, this->y);
			}
		}
		break;
	default:
		break;
	}
}
Hero& Hero::operator= (Hero const &hero) {
	assert(health >= 0 && health <= 100);
	assert(name);
	assert(x >= 0 && y >= 0);
	if (this == &hero)
		return *this;

	x = hero.x;
	y = hero.y;
	health = hero.health;
	strcpy(name, hero.name);
	
	return *this;
}

