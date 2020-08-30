#pragma warning(disable : 4996)

#include <iostream>
#include <conio.h>
#include <iomanip>

#include "Landscape.h"

#define LEN 255

using namespace std;

Landscape::Landscape() {
	char* temp = new char[LEN] { "-" };
	this->object = setobject(temp);
	this->x = x;
	this->y = y;
}

Landscape::Landscape(const char object[], int x, int y) {
	char* temp = new char[LEN] {};
	strcpy(temp, object);
	this->object = setobject(temp);
	this->x = x;
	this->y = y;
}

Landscape::~Landscape() {
	delete[] this->object;
}

char* Landscape::setobject(char* object) {
	this->object = object;
	return this->object;
}

/*

Landscape* Landscape::erase(Landscape* arr, int index) {
	Landscape* newArray = new Landscape[this->sizeLand - 1];
	if (this->sizeLand == 1) {
		arr = newArray;
		this->sizeLand--;
		return arr;
	}
	if (index == 0) {
		for (int i = 0; i < this->sizeLand - 1; i++)
			newArray[i] = arr[i + 1];
		arr = newArray;
		this->sizeLand--;
		return arr;
	}
	if (index == this->sizeLand - 1) {
		for (int i = 0; i < index; i++)
			newArray[i] = arr[i];
		arr = newArray;
		this->sizeLand--;
		return arr;
	}
	for (int i = 0; i < index; i++)
		newArray[i] = arr[i];
	for (int i = index; i < this->sizeLand - 1; i++)
		newArray[i] = arr[i + 1];
	arr = newArray;
	this->sizeLand--;
	return arr;
}

void Landscape::printLand(Landscape* landscapeList) {
	int i = 1;
	cout << endl;
	cout << setw(10) << right << "FIELD LIST" << endl;
	for (int j = 0; j < getsizeLand(); j++) {
		cout << i++ <<
			". " << landscapeList[j].object <<
			": x = " << landscapeList[j].x <<
			" y = " << landscapeList[j].y << endl;
	}
}

void Landscape::updateLand(Landscape* landscapeList, int x_hero, int y_hero, int cur_x_hero, int cur_y_hero) {
	for (int i = 0; i < getsizeLand(); i++) {
		if (landscapeList[i].x == x_hero) {
			if (landscapeList[i].y == y_hero) {
				landscapeList[i].x = cur_x_hero;
				landscapeList[i].y = cur_y_hero;
				return;
			}
		}
	}
	cout << "No hero in position\n";
	system("pause");
}*/
