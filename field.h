#pragma once
#include "FieldList.h"
#include "Hero.h"

class Hero;
class Landscape;

class field {
public:

	field();
	field(int widht, int height);
	field(int sideSize);
	~field();
	void addHero(Hero& hero);
	void deleteHero(int x_hero, int y_hero);
	bool moveHero(field& FieldG, FieldList token);
	bool checkList(int x_hero, int y_hero);
	FieldList* pushBack(FieldList* arr, FieldList temp);
	FieldList* erase(FieldList* arr, int index);
	Landscape* pushLand(Landscape* arr, Landscape temp);
	void printList();
	void updateList(int x_hero, int y_hero, int cur_x_hero, int cur_y_hero);
	void updatefield(field& Fieldp, int prev_x, int prev_y, int cur_x, int cur_y);
	void swapHero(Hero* first_p, Hero* second_p);
	void printfield();

	int getWidth() { return fieldWidth; }
	int getHeight() { return fieldHeight; }
	FieldList* getList() { return fieldList; }
	Landscape* getLand() { return landscapeList; }
	int getSizeList() { return sizeList; }
	int getCurrentCountUnit() { return current_countUnits; }
	int getMaxCountUnit() { return max_countUnits; }

	field& operator= (field const& FieldG);
private:
	Hero** Field;
	int fieldWidth = 0;
	int fieldHeight = 0;
	FieldList* fieldList;
	Landscape* landscapeList;
	int sizeList = 0;
	int sizeLand = 0;
	int current_countUnits = 0;
	int max_countUnits = 0;
};