#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <iomanip>
#include <ctime>

#include "field.h"
#include "Hero.h"
#include "Earth.h"

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

#define LEN 255
//check git

using namespace std;

int sub_m_count = 0;
int m_count = 0;
int m_play_count = 0;
int m_hero_count = 0;
int m_delete_count = 0;
const int m_itemSize = 2;
const int m_playSize = 5;
const int m_heroSize = 5;



void menuListUnit(field& FieldG);
void menuListUnitChoice(field& FieldG);
void menuPlay(field& FieldG);
void menuPlayChoice(field& FieldG);
void menu();
void menuChoice();
void menuHeroChoice(field& FieldG);
void createHeroOnField(field& FieldG);
void menuDeleteUnitChoice(field& FieldG);

void SetColor(int text, int bg) {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

class Archer : public Hero {
public:
	Archer() : Hero("Archer") {};
};

class MeleeUnit : public Hero {
public:
	MeleeUnit() : Hero("MeleeUnit") {};
	MeleeUnit(const char name[]) : Hero(name) {};
};

class Cavalry : public Hero {
public:
	Cavalry() : Hero("Calvary") {};
};

class Swordsman : public MeleeUnit {
public:
	Swordsman() : MeleeUnit("Swordsman") {};
};

class Spearman : public MeleeUnit {
public:
	Spearman() : MeleeUnit("Spearman") {};
};

int checkdigit() {
	while (true) {
		int value;
		cin >> value;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			SetColor(4, 0);
			cout << "INVALID VALUE. Please try again.\n";
			SetColor(7, 0);
		}
		else {
			cin.ignore(32767, '\n');
			return value;
		}
	}
}

void copyField(field& FieldG) {
	field temp;
	temp = FieldG;
	temp.printfield();
	cout << endl;
	SetColor(2, 0);
	cout << "Field was copied successfuly. Press any key.\n";
	SetColor(7, 0);
	_getch();
	menuPlay(FieldG);
}

void deleteHeroFromField(field& FieldG) {
	if (FieldG.getCurrentCountUnit() == 0) {
		SetColor(4, 0);
		cout << "FIELD DOESNT HAVE HEROES.\n";
		SetColor(7, 0);
		system("pause");
		menuPlay(FieldG);
	}
	FieldList* listUnit = FieldG.getList();
	system("cls");
	cout << setw(20) << right << "___DELETE HERO___\n";
	cout << "What the hero do u want delete? Press"; SetColor(2, 0); cout << " ESC "; SetColor(7, 0); cout << "to back in menu" << endl;
	for (int i = 0; i < FieldG.getSizeList(); i++) {
		if (m_delete_count == i)
			SetColor(6, 0);
		cout << i << ". " << listUnit[i].name << ": x = " << listUnit[i].x_pos << " y = " << listUnit[i].y_pos << endl;
		SetColor(7, 0);
	}
	menuDeleteUnitChoice(FieldG);
}

void createHeroOnField(field& FieldG) {
	if (FieldG.getCurrentCountUnit() == FieldG.getMaxCountUnit()) {
		SetColor(4, 0);
		cout << "MAX UNIT ON FIELD.\n";
		SetColor(7, 0);
		system("pause");
		menuPlay(FieldG);
	}
	string menuHeroItem[m_heroSize] = { "Archer" , "MeleeUnit", "Cavalry", "Spearman", "Swordsman" };
	system("cls");
	cout << setw(20) << right << "___ADD HERO___\n";
	cout << "What the class do u want create? Press"; SetColor(2, 0); cout << " ESC "; SetColor(7, 0); cout << "to back in menu" << endl;
	for (int i = 0; i < m_heroSize; i++) {
		if (m_hero_count == i)
			SetColor(6, 0);
		cout << menuHeroItem[i] << endl;
		SetColor(7, 0);
	}
	menuHeroChoice(FieldG);
}

void createField() {
	system("cls");
	int width, height;
	cout << setw(30) << right << "___CREATE FIELD___\n";
	cout << "Enter the width of field: ";
	width = checkdigit();
	while (width <= 0) {
		cout << "\nValue less than or equal to zero. Try again: ";
		width = checkdigit();
	}
	cout << "Enter the height of field: ";
	height = checkdigit();
	while (height <= 0) {
		cout << "\nValue less then or equal to zero. Try again: ";
		height = checkdigit();
	}
	field FieldG(width, height);
	cout << endl;
	FieldG.printfield();
	SetColor(2, 0);
	cout << "\nField create successfully. Press any key.\n";
	SetColor(7, 0);
	_getch();
	menuPlay(FieldG);
}

Landscape* fillLandscape(field& FieldG) {
	Earth earth;
	Landscape* tempLand = NULL;
	const int TypeLandSize = 3;
	srand(time(NULL));
	bool stop = TRUE;
	char* tempW = new char [LEN] {"Water"};
	char* tempM = new char [LEN] {"Mount"};
	char* tempE = new char [LEN] {"Earth"};
	int cur_W = 0;
	int cur_M = 0;
	char LandType[TypeLandSize][LEN] = {"Earth", "Water", "Mount"};
	for (int i = 0; i < FieldG.getHeight(); i++) {
		for (int j = 0; j < FieldG.getWidth(); j++) {
			earth.setobject(tempE);
			stop = TRUE;
			while (stop) {
				int tempI = rand() % 100;
				if (tempI >= 0 && tempI <= 40) {
					earth.setx(i);
					earth.sety(j);
					tempLand = FieldG.pushLand(tempLand, earth);
					stop = FALSE;
				}
				else if (tempI > 40 && tempI <= 80) {
					if (cur_W != FieldG.getMaxWater()) {
						earth.setx(i);
						earth.sety(j);
						earth.setobject(tempW);
						tempLand = FieldG.pushLand(tempLand, earth);
						cur_W++;
						stop = FALSE;
					}
				}
				else {
					if (cur_M != FieldG.getMaxMount()) {
						earth.setx(i);
						earth.sety(j);
						earth.setobject(tempM);
						tempLand = FieldG.pushLand(tempLand, earth);
						cur_M++;
						stop = FALSE;
					}
				}
			}
		}
	}
	return tempLand;
}

void menuDeleteUnitChoice(field& FieldG) {
	FieldList* listUnit = FieldG.getList();
	int k1 = _getch();
	if (k1 != 0x77 && k1 != 0x73 && k1 != 0xD && k1 != 0x1B) {
		menuDeleteUnitChoice(FieldG);
		return;
	}
	switch (k1) {
	case 0x1B:
		menuPlay(FieldG);
		return;
	case 0x77:
		m_delete_count--;
		if (m_delete_count < 0) m_delete_count = 0;
		deleteHeroFromField(FieldG);
		break;
	case 0x73:
		m_delete_count++;
		if (m_delete_count > FieldG.getSizeList() - 1) m_delete_count = FieldG.getSizeList() - 1;
		deleteHeroFromField(FieldG);
		break;
	case 0xD:
		FieldG.deleteHero(listUnit[m_delete_count].x_pos, listUnit[m_delete_count].y_pos);
		m_delete_count = 0;
		menuPlay(FieldG);
		break;
	default:
		menuDeleteUnitChoice(FieldG);
	}
}

void menuHeroChoice(field& FieldG) {
	Archer arch;
	MeleeUnit melee;
	Cavalry calv;
	Spearman spr;
	Swordsman swrd;
	int k1 = _getch();
	if (k1 != 0x77 && k1 != 0x73 && k1 != 0xD && k1 != 0x1B) {
		menuHeroChoice(FieldG);
		return;
	}
	switch (k1) {
	case 0x1B:
		menuPlay(FieldG);
		return;
	case 0x77:
		m_hero_count--;
		if (m_hero_count < 0) m_hero_count = 0;
		createHeroOnField(FieldG);
		break;
	case 0x73:
		m_hero_count++;
		if (m_hero_count > m_heroSize - 1) m_hero_count = m_heroSize - 1;
		createHeroOnField(FieldG);
		break;
	case 0xD:
		switch (m_hero_count)
		{
		case 0:
			FieldG.addHero(arch);
			break;
		case 1:
			FieldG.addHero(melee);
			break;
		case 2:
			FieldG.addHero(calv);
			break;
		case 3:
			FieldG.addHero(spr);
			break;
		case 4:
			FieldG.addHero(swrd);
			break;
		default:
			break;
		}
		menuPlay(FieldG);
		break;
	default:
		menuHeroChoice(FieldG);
	}
}

void menuPlayChoice(field& FieldG) {
	int k1 = _getch();
	if (k1 != 0x77 && k1 != 0x73 && k1 != 0xD && k1 != 0x1B) {
		menuPlayChoice(FieldG);
		return;
	}
	switch (k1) {
	case 0x1B:
		FieldG.~field();
		menu();
		return;
	case 0x77:
		m_play_count--;
		if (m_play_count < 0) m_play_count = 0;
		menuPlay(FieldG);
		break;
	case 0x73:
		m_play_count++;
		if (m_play_count > m_playSize - 1) m_play_count = m_playSize - 1;
		menuPlay(FieldG);
		break;
	case 0xD:
		switch (m_play_count) {
		case 0:
			createHeroOnField(FieldG);
			break;
		case 1:
			deleteHeroFromField(FieldG);
			break;
		case 2:
			menuListUnit(FieldG);
			break;
		case 3:
			copyField(FieldG);
			break;
		case 4:
			FieldG.~field();
			menu();
			break;
		default:
			break;
		}
		break;
	default:
		menuPlayChoice(FieldG);
	}
}

void menuChoice() {
	int k1 = _getch();
	if (k1 != 0x77 && k1 != 0x73 && k1 != 0xD) {
		menuChoice();
		return;
	}
	switch (k1) {
	case 0x77:
		m_count--;
		if (m_count < 0) m_count = 0;
		menu();
		break;
	case 0x73:
		m_count++;
		if (m_count > m_itemSize - 1) m_count = m_itemSize - 1;
		menu();
		break;
	case 0xD:
		switch (m_count) {
		case 0:
			createField();
			break;
		case 1:
			system("cls");
			SetColor(2, 0); cout << setw(30) << right << "GOODBYE!" << endl; SetColor(0, 0);
			exit(0);
			break;
		default:
			break;
		}
		break;
	default:
		menuChoice();
	}
}

void menuListUnitChoice(field& FieldG) {
	int k1 = _getch();
	FieldList* tempListUnit = FieldG.getList();
	if (k1 != 0x77 && k1 != 0x73 && k1 != 0xD && k1 != 0x1B) {
		menuListUnitChoice(FieldG);
		return;
	}
	switch (k1) {
	case 0x1B:
		menuPlay(FieldG);
		return;
	case 0x77:
		sub_m_count--;
		if (sub_m_count < 0) sub_m_count = 0;
		menuListUnit(FieldG);
		break;

	case 0x73:
		sub_m_count++;
		if (sub_m_count > FieldG.getSizeList() - 1) sub_m_count = FieldG.getSizeList() - 1;
		menuListUnit(FieldG);
		break;
	case 0xD:
		cout << "Move by WASD on keyboard\n";
		while (!FieldG.moveHero(FieldG, tempListUnit[sub_m_count])) {
			system("cls");
			FieldG.printfield();
			FieldG.printList();
			cout << "Move by WASD on keyboard. Press any key to stop moving.\n";
		}
		menuListUnit(FieldG);
		break;
	default:
		menuListUnitChoice(FieldG);
	}
}

void menuListUnit(field& FieldG) {
	FieldList* listUnit = FieldG.getList();
	system("cls");
	FieldG.printfield();
	if (FieldG.getSizeList() == 0) {
		SetColor(3, 0);
		cout << "No one on field. Need add hero on field. Press any key\n";
		SetColor(7, 0);
		createHeroOnField(FieldG);
		menuListUnit(FieldG);
		return;
	}
	cout << "\nWhat the hero do u want control? Press"; SetColor(2, 0); cout << " ESC "; SetColor(7, 0); cout << "to back in menu" << endl;
	cout << "Choose the control unit: " << endl;
	for (int i = 0; i < FieldG.getSizeList(); i++) {
		if (sub_m_count == i)
			SetColor(6, 0);
		cout << i << ". " << listUnit[i].name << ": x = " << listUnit[i].x_pos << " y = " << listUnit[i].y_pos << endl;
		SetColor(7, 0);
	}
	menuListUnitChoice(FieldG);
}

void menuPlay(field& FieldG) {
	system("cls");
	cout << setw(20) << right << "_____MENU_____\n";
	string menuPlayItem[m_playSize] = { "Add Hero on field", "Delete Hero from field" , "Control Heroes on field", "Copy field", "Back" };
	for (int i = 0; i < m_playSize; i++) {
		if (m_play_count == i)
			SetColor(6, 0);
		cout << menuPlayItem[i] << endl;
		SetColor(7, 0);
	}
	cout << endl << endl;
	FieldG.printfield();
	menuPlayChoice(FieldG);
}

void menu() {
	system("cls");
	cout << setw(30) << right << "_____MENU_____\n";
	string menuItem[m_itemSize] = { "PLAY", "Exit" };
	for (int i = 0; i < m_itemSize; i++) {
		if (m_count == i)
			SetColor(6, 0);
		cout << setw(24) << right << menuItem[i] << endl;
		SetColor(7, 0);
	}
	menuChoice();
}


void test_fill() {
	field FieldG(5, 5);
	Archer arch;
	while (true) {
		system("cls");
		FieldG.addHero(arch);
		FieldG.printfield();
		//FieldG.printList();
		system("pause");
	}
}

void test_Land() {
	field FieldG(7,20);
	FieldG.setLand(fillLandscape(FieldG));
	FieldG.printLand();
	system("pause");
	//system("cls");
	FieldG.printfield();
	system("pause");
}

int main() {

	
	system("mode con cols=200 lines=50");
	test_Land();
	menu();
	//test_fill();

	system("pause");
	return 0;
}