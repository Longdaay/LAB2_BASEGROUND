#pragma once

class Landscape {
public:
	Landscape();
	Landscape(const char object[], int x, int y);
	~Landscape();

	void pushBack(Landscape* arr, Landscape temp);
	Landscape* erase(Landscape* arr, int index);
	void printLand(Landscape *landscapeList);
	void updateLand(Landscape* landscapeList, int x_hero, int y_hero, int cur_x_hero, int cur_y_hero);

	void setx(int x) { this->x = x; }
	void sety(int y) { this->y = y; }
	//int getsizeLand() { return sizeLand; }
	char* setobject(char* object);

private:
	int x = 0;
	int y = 0;
	char* object;
	

};