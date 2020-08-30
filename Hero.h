#pragma once
#include "field.h"
#include <cassert>

class field;

using namespace std;

class Hero {
public:
	Hero(const char name[]);
	Hero();
	~Hero();
	void moving(field& FieldG);
	int getx() { return x; }
	int gety() { return y; }
	char* setname(char* name);
	void setx(int x) { this->x = x; }
	void sety(int y) { this->y = y; }
	char* getname() { return name; };
	Hero& operator= (Hero  const& hero);
private:
	int x;
	int y;
	int health;
	char* name;
};

