#pragma once

class Landscape {
public:
	Landscape();
	Landscape(const char object[], int x, int y);
	//~Landscape();

	void pushBack(Landscape* arr, Landscape temp);
	Landscape* erase(Landscape* arr, int index);
	void updateLand(Landscape* landscapeList, int x_hero, int y_hero, int cur_x_hero, int cur_y_hero);

	void setx(int x) { this->x = x; }
	void sety(int y) { this->y = y; }
	void setobject(char* object);

	char* getObj() { return object; }
	int getx() { return x; }
	int gety() { return y; }

private:
	int x = 0;
	int y = 0;
	char* object;
	

};