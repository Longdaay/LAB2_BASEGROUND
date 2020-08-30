#pragma warning(disable : 4996)
#include "field.h"
#include "Hero.h"
#include "Landscape.h"
#include <iostream>
#include <conio.h>
#include <iomanip>
#include <Windows.h>

using namespace std;

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

char space[255] = "-";

void ColorField(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

field::field() {
	this->fieldWidth = 10;
	this->fieldHeight = 10;
	this->max_countUnits = this->fieldHeight * this->fieldWidth;
	Field = new Hero * [this->fieldWidth];
	for (int i = 0; i < this->fieldWidth; i++) {
		Field[i] = new Hero[this->fieldHeight];
	}
}

field::field(int width, int height) {
	this->fieldWidth = width;
	this->fieldHeight = height;
	this->max_countUnits = this->fieldHeight * this->fieldWidth;
	this->maxMount = this->max_countUnits * 0.1;
	this->maxWater = this->max_countUnits * 0.1;
	Field = new Hero * [height];
	for (int i = 0; i < height; i++) {
		Field[i] = new Hero[width];
	}
}

field::field(int sideSize) {
	this->fieldWidth = sideSize;
	this->fieldHeight = sideSize;
	this->max_countUnits = this->fieldHeight * this->fieldWidth;
	Field = new Hero * [sideSize];
	for (int i = 0; i < sideSize; i++) {
		Field[i] = new Hero[sideSize];
	}
}

field::~field() {
	delete[] fieldList;
	delete[] Field;
}

void field::addHero(Hero& hero) {
	if (current_countUnits == max_countUnits) {
		cout << "MAX UNIT ON FIELD.\n";
		system("pause");
		return;
	}
	
	int iterator = 0;
	bool moral_stop = false;
	if (this->fieldHeight > this->fieldWidth) { // height > width

		for (iterator; iterator < fieldHeight; iterator++) {
			if (!moral_stop) {
				for (int i = 0; i <= iterator; i++) {
					if (strcmp(Field[iterator - i][i].getname(), space) == 0) {
						Field[iterator - i][i] = hero;
						fieldList = pushBack(fieldList, { iterator - i, i, hero.getname() });
						current_countUnits++;
						return;
					}
					i + 1 == fieldWidth ? moral_stop = true : moral_stop = false;
				}
			}
			else {
				for (int i = 0; i < fieldWidth; i++) {
					if (strcmp(Field[iterator - i][i].getname(), space) == 0) {
						Field[iterator - i][i] = hero;
						fieldList = pushBack(fieldList, { iterator - i, i, hero.getname() });
						current_countUnits++;
						return;
					}
				}
			}
		}
		for (int i = 0; i < fieldHeight; i++) {
			for (int iterator = 0; iterator + i < fieldWidth; iterator++) {
				if (strcmp(Field[fieldHeight - iterator - 1][iterator + i].getname(), space) == 0) {
					Field[fieldHeight - iterator - 1][iterator + i] = hero;
					fieldList = pushBack(fieldList, { fieldHeight - iterator - 1, iterator + 1 + i, hero.getname() });
					current_countUnits++;
					return;
				}
			}
		}
	}
	else if (this->fieldWidth > this->fieldHeight) { // height < width
		for (iterator; iterator < fieldHeight; iterator++) {
			for (int i = 0; i <= iterator; i++) {
				if (strcmp(Field[iterator - i][i].getname(), space) == 0) {
					Field[iterator - i][i] = hero;
					fieldList = pushBack(fieldList, { iterator - i, i, hero.getname() });
					current_countUnits++;
					return;
				}
			}
		}

		for (int i = 0; i < fieldWidth; i++) {
			if (!moral_stop) {
				for (int iterator = 0; iterator < fieldHeight; iterator++) {
					if (strcmp(Field[fieldHeight - iterator - 1][iterator + i].getname(), space) == 0) {
						Field[fieldHeight - iterator - 1][iterator + i] = hero;
						fieldList = pushBack(fieldList, { fieldHeight - iterator - 1, iterator + 1 + i, hero.getname() });
						current_countUnits++;
						return;
					}
					i + iterator + 1 == fieldWidth ? moral_stop = true : moral_stop = false;
				}
			}
			else {
				for (int iterator = 0; iterator < fieldHeight - 1; iterator++) {
					if (strcmp(Field[fieldHeight - iterator - 1][iterator + i].getname(), space) == 0) {
						Field[fieldHeight - iterator - 1][iterator + i] = hero;
						fieldList = pushBack(fieldList, { fieldHeight - iterator - 1, iterator + i, hero.getname() });
						current_countUnits++;
						return;
					}
				}
			}
		}

	}
	else { // width = height
		for (iterator; iterator < fieldWidth; iterator++) {
			for (int i = 0; i <= iterator; i++) {
				if (strcmp(Field[iterator - i][i].getname(), space) == 0) {
					Field[iterator - i][i] = hero;
					fieldList = pushBack(fieldList, { iterator - i, i, hero.getname() });
					current_countUnits++;
					return;
				}
			}
		}
		for (int i = 0; i < fieldWidth; i++) {
			for (iterator = 0; iterator + i < fieldWidth; iterator++) {
				if (strcmp(Field[fieldWidth - iterator - 1][iterator + i].getname(), space) == 0) {
					Field[fieldWidth - iterator - 1][iterator + i] = hero;
					fieldList = pushBack(fieldList, { fieldWidth - iterator - 1, iterator + i, hero.getname() });
					current_countUnits++;
					return;
				}
			}
		}
	}
}

void field::deleteHero(int x_hero, int y_hero) {
	int token_index = 0;
	for (int i = 0; i < getSizeList(); i++) {
		if (fieldList[i].x_pos == x_hero) {
			token_index++;
			if (fieldList[i].y_pos == y_hero) {
				Hero tempUnit;
				Field[fieldList[i].x_pos][fieldList[i].y_pos] = tempUnit;
				fieldList = erase(fieldList, token_index - 1);
				this->current_countUnits--;
			}
		}
	}
}

FieldList* field::pushBack(FieldList* arr, FieldList temp) {
	FieldList* newArray = new FieldList[this->sizeList + 1];
	for (int i = 0; i < this->sizeList; i++)
		newArray[i] = arr[i];
	newArray[this->sizeList] = temp;
	arr = newArray;
	this->sizeList++;
	return arr;
}

FieldList* field::erase(FieldList* arr, int index) {
	FieldList* newArray = new FieldList[this->sizeList - 1];
	if (this->sizeList == 1) {
		arr = newArray;
		this->sizeList--;
		return arr;
	}
	if (index == 0) {
		for (int i = 0; i < this->sizeList - 1; i++)
			newArray[i] = arr[i + 1];
		arr = newArray;
		this->sizeList--;
		return arr;
	}
	if (index == this->sizeList - 1) {
		for (int i = 0; i < index; i++)
			newArray[i] = arr[i];
		arr = newArray;
		this->sizeList--;
		return arr;
	}
	for (int i = 0; i < index; i++)
		newArray[i] = arr[i];
	for (int i = index; i < this->sizeList - 1; i++)
		newArray[i] = arr[i + 1];
	arr = newArray;
	this->sizeList--;
	return arr;
}

Landscape* field::pushLand(Landscape* arr, Landscape temp) {
	Landscape* newArray = new Landscape[this->sizeLand + 1];
	for (int i = 0; i < this->sizeLand; i++)
		newArray[i] = arr[i];
	newArray[this->sizeLand] = temp;
	arr = newArray;
	this->sizeLand++;
	return arr;
}

void field::printLand() {
	int i = 1;
	cout << endl;
	cout << setw(10) << right << "FIELD LIST" << endl;
	for (int j = 0; j < getSizeLand(); j++) {
		cout << i++ <<
			". " << landscapeList[j].getObj() <<
			": x = " << landscapeList[j].getx() <<
			" y = " << landscapeList[j].gety() << endl;
		_getch();
	}
}

void field::printList() {
	int i = 1;
	cout << endl;
	ColorField(3, 0);
	cout << setw(10) << right << "FIELD LIST" << endl;
	ColorField(7, 0);
	for (int j = 0; j < getSizeList(); j++) {
		cout << i++ <<
			". " << fieldList[j].name <<
			": x = " << fieldList[j].x_pos <<
			" y = " << fieldList[j].y_pos << endl;
	}
}

void field::updateList(int x_hero, int y_hero, int cur_x_hero, int cur_y_hero) {
	for (int i = 0; i < getSizeList(); i++) {
		if (fieldList[i].x_pos == x_hero) {
			if (fieldList[i].y_pos == y_hero) {
				fieldList[i].x_pos = cur_x_hero;
				fieldList[i].y_pos = cur_y_hero;
				return;
			}
		}
	}
	cout << "No hero in position\n";
	system("pause");
}
/*
void field::printfield() {
	ColorField(2, 0);
	cout << "HERO MAP\n";
	ColorField(7, 0);
	for (int i = 0; i < fieldHeight; i++) {
		for (int j = 0; j < fieldWidth; j++) {
			cout << setw(10) << left << Field[i][j].getname() << "\t";
		}
		cout << "\n";
	}
}*/

char* field::findObjName(int x_pos, int y_pos) {
	assert(sizeLand >= 0);
	for (int i = 0; i < sizeLand; i++) {
		if (landscapeList[i].getx() == x_pos) {
			if (landscapeList[i].gety() == y_pos)
				return landscapeList[i].getObj();
		}
	}
}

void field::printfield() {
	ColorField(2, 0);
	cout << "HERO MAP\n";
	ColorField(7, 0);
	for (int i = 0; i < fieldHeight; i++) {
		for (int j = 0; j < fieldWidth; j++) {
			if (checkList(i, j)) {
				char names[255];
				strcpy(names, findObjName(i, j));
				if (names == "Water")
					ColorField(WHITE, BLUE);
				else if (names == "Earth")
					ColorField(BLACK, BROWN);
				else
					ColorField(BLACK, LIGHTGRAY);
				cout << setw(15) << left << findObjName(i,j) << "\t";
				ColorField(7, 0);
			} 
			else {
				cout << setw(10) << left << Field[i][j].getname() << "\t";
			}
		}
		cout << "\n";
	}
}

field& field::operator= (field const& FieldG) {
	assert(fieldHeight > 0 && fieldWidth > 0 && sizeList >= 0);
	assert(current_countUnits >= 0 && max_countUnits >= 0 && current_countUnits <= max_countUnits);

	if (this == &FieldG)
		return *this;

	Field = FieldG.Field;
	fieldHeight = FieldG.fieldHeight;
	fieldWidth = FieldG.fieldWidth;
	fieldList = FieldG.fieldList;
	sizeList = FieldG.sizeList;
	current_countUnits = FieldG.current_countUnits;
	max_countUnits = FieldG.max_countUnits;

	return *this;
}


bool field::checkList(int x_hero, int y_hero) {
	assert(sizeList >= 0);
	for (int i = 0; i < getSizeList(); i++) {
		if (fieldList[i].x_pos == x_hero) {
			if (fieldList[i].y_pos == y_hero)
				return false;						//position is busy
		}
	}
	return true;								    //position is free
}

bool field::moveHero(field& FieldG, FieldList token) {
	assert(fieldHeight > 0 && fieldWidth > 0 && sizeList >= 0);
	assert(current_countUnits >= 0 && max_countUnits >= 0 && current_countUnits <= max_countUnits);
	int k1;
	k1 = _getch();
	if (k1 != 97 && k1 != 100 && k1 != 119 && k1 != 115)
		return 1;
	int prev_x = token.x_pos;
	int prev_y = token.y_pos;
	switch (k1)
	{
	case 0x61: //97 влево
		if (token.y_pos - 1 < 0) {
			token.y_pos = 0;
			return 0;
		}
		else {
			if (FieldG.checkList(token.x_pos, token.y_pos - 1)) {
				token.y_pos--;
				FieldG.updateList(prev_x, prev_y, token.x_pos, token.y_pos);
				FieldG.updatefield(FieldG, prev_x, prev_y, token.x_pos, token.y_pos);
			}
		}
		break;
	case 0x64: //100 вправо
		if (token.y_pos + 1 == FieldG.getWidth()) {
			token.y_pos = FieldG.getWidth() - 1;
			return 0;
		}
		else {
			if (FieldG.checkList(token.x_pos, token.y_pos + 1)) {
				token.y_pos++;
				FieldG.updateList(prev_x, prev_y, token.x_pos, token.y_pos);
				FieldG.updatefield(FieldG, prev_x, prev_y, token.x_pos, token.y_pos);
			}
		}

		break;
	case 0x77: //119 вверх
		if (token.x_pos - 1 < 0) {
			token.x_pos = 0;
			return 0;
		}
		else {
			if (FieldG.checkList(token.x_pos - 1, token.y_pos)) {
				token.x_pos--;
				FieldG.updateList(prev_x, prev_y, token.x_pos, token.y_pos);
				FieldG.updatefield(FieldG, prev_x, prev_y, token.x_pos, token.y_pos);
			}
		}
		break;
	case 0x73: //115 вниз
		if (token.x_pos + 1 == FieldG.getHeight()) {
			token.x_pos = FieldG.getHeight() - 1;
			return 0;
		}
		else {
			if (FieldG.checkList(token.x_pos + 1, token.y_pos)) {
				token.x_pos++;
				FieldG.updateList(prev_x, prev_y, token.x_pos, token.y_pos);
				FieldG.updatefield(FieldG, prev_x, prev_y, token.x_pos, token.y_pos);
			}
		}
		break;
	default:
		break;
	}
	return 0;
}

void field::swapHero(Hero* first_p, Hero* second_p) {
	Hero temp;
	temp = *first_p;
	*first_p = *second_p;
	*second_p = temp;
}

void field::updatefield(field& Fieldp, int prev_x, int prev_y, int cur_x, int cur_y) {
	if (strcmp(Fieldp.Field[cur_x][cur_y].getname(), space) == 0)
		swapHero(&Fieldp.Field[prev_x][prev_y], &Fieldp.Field[cur_x][cur_y]);
}