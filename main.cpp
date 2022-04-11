#include <iostream> 
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
void playGame(); //  joc ul in sine
void mainMenu(); // functie main menu
void cc(); // clear console
void gotoXY(short linie, short coloana); // functie deplasare wrt

//definire  CULORI
#define NORMAL "\033[0;37m";
#define RED "\033[0;31m"
#define GOLD "\033[0;33m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define CYAN "\033[1;36m"

// definire COMENZI SAGETI
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define SPACE 32

// dim harta
int posX = 10;
int posY = 25;
// punctaje si pozitii initiale
int score = 0;
int bullets = 2;
int senzor = 0;
int comoara1 = 1;
int comoara2 = 1;
int monstru1 = 1;
int monstru2 = 1;
int monstru3 = 1;
int monst1X = 9;
int monst1Y = 6;
int monst2X = 1;
int monst2Y = 19;
int monst3X = 3;
int monst3Y = 2;

void aboutGame() { // despre joc, un mic tutorial
	cc();
	gotoXY(2, 2);
	cout << "Created by ";
	cout << GOLD "Nicolaescu Ovidiu-Constantin\n" NORMAL;
	cout << "You can control the player with ARROWS!\nYou have to collect all the GOLD without being eaten by the monsters\nEventualy, if you meet the monsters you can kill them with your gun!\nBut be careful! You have only 2 bullets!";
	cout << CYAN "\n\nPress any key to go to main menu!" NORMAL;
	_getch();
	mainMenu();
}

typedef struct { short X; short Y; }coord;
void gotoXY(short linie, short coloana) {
	COORD coord; //structura care defineste coordonatele unui punct de pe consola
	coord.X = coloana;
	coord.Y = linie;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, coord);
}

void drawMap(int linii, int coloane) { // desenam harta alaturi de mobi si obstacole si alte elemente de grafica
	for (int i = 0; i <= linii; i++) {
		for (int j = 0; j <= coloane; j++)
			if (i == linii || j == coloane || i == 0 || j == 0) {
				gotoXY(i, j);
				cout << CYAN "#" NORMAL;
			}
	}

	////////   GOLD   ///////////
	gotoXY(5, 23);
	cout << GREEN "$" NORMAL;
	gotoXY(7, 12);
	cout << GREEN "$" NORMAL;

	// MONSTRI
	gotoXY(monst1X, monst1Y);
	cout << BLUE "Ï" NORMAL;
	gotoXY(monst2X, monst2Y);
	cout << BLUE "Ï" NORMAL;
	gotoXY(monst3X, monst3Y);
	cout << BLUE "Ï" NORMAL;
	/////

	gotoXY(3, 30);
	cout << "To end simulation, press SPACE!";

	gotoXY(4, 30);
	cout << "Bullets: ";
	gotoXY(4, 39);
	cout << GOLD;
	cout << bullets;
	cout << NORMAL;
	cout << "/2";
	gotoXY(5, 30);


	cout << "Score: ";
	gotoXY(5, 37);
	cout << GOLD;
	cout << score;
	cout << NORMAL;


	gotoXY(6, 30);
	cout << "Direction:";

	for (int i = 4; i < 8; i++) {  //3,8 | 8,13 | 15,20 | 4,9 |2,6 |6,9
		gotoXY(i, 3);
		cout << RED "X" NORMAL;
	}
	for (int i = 8; i < 13; i++) {
		gotoXY(3, i);
		cout << RED "X" NORMAL;
	}
	for (int i = 15; i < 20; i++) {
		gotoXY(8, i);
		cout << RED "X" NORMAL;
	}
	for (int i = 4; i < 9; i++) {
		gotoXY(6, i);
		cout << RED "X" NORMAL;
	}
	for (int i = 2; i < 6; i++) {
		gotoXY(i, 18);
		cout << RED "X" NORMAL;
	}
	for (int i = 6; i < 9; i++) {
		gotoXY(i, 9);
		cout << RED "X" NORMAL;
	}
	gotoXY(1, 1);
	cout << GOLD "O" NORMAL;
}

void cc() {
	system("cls");
}

void mainMenu() {
	//system("COLOR 0A"); // CULOARE CONSOLA

	////// RESETAM VALORILE PENTRU urmatorul run;
	score = 0;
	bullets = 2;
	senzor = 0;
	comoara1 = 1;
	comoara2 = 1;
	monstru1 = 1;
	monstru2 = 1;
	monstru3 = 1;
	//////
	monst1X = 9;
	monst1Y = 6;
	monst2X = 1;
	monst2Y = 19;
	monst3X = 3;
	monst3Y = 2;
	//
	cc();
	cout << "  Welcome, ";
	cout << GOLD "explorer" NORMAL;
	cout << "!";
	cout << "\nPress a key to select:";
	cout << GOLD "\n\n1 - Start Game\n2 - How to play!\n" NORMAL;
	cout << RED "0 - EXIT" NORMAL;


	char userInput; // select item meniu
	userInput = _getch();
	while (userInput != '1' && userInput != '2' && userInput != '0') {
		cout << "\nError! ";
		cout << "Insert a valid number!\n";
		userInput = _getch();
	}
	switch (userInput) {
	case '1':
		cc();
		playGame();
		break;
	case '2':
		cc();
		aboutGame();
		break;
	case '0':
		exit(0);
	}
}

void player() { // functie desenare player apelata la fiecare miscare
	cout << GOLD "O" NORMAL;
}

void bulletsUpdate() { // update la gloante (functie pentru a nu scrie de fiecare data)
	gotoXY(4, 39);
	cout << "    ";
	gotoXY(4, 39);
	cout << GOLD;
	cout << bullets;
	cout << NORMAL;
	cout << "/2";
}

void scoreUpdate() { // update la scor (functie pentru a nu scrie de fiecare data)
	gotoXY(5, 37);
	cout << "    ";
	gotoXY(5, 37);
	cout << GOLD;
	cout << score;
	cout << NORMAL;
}

void playGame() { // jocul in sine

	int linie = 1, coloana = 1; // coordonate
	int pointDirect = 1; // directia in care pointeaza playerul
	drawMap(posX, posY); // desenam mapa cu pozitile dorite (nu este total dinamica, pozitile obstacolelor / mobilor sunt fixe)
	int direction = 0;
	while (1) {
		//////////  Verificam pozitile pickup la GOLD 
		if (linie == 5 && coloana == 23) {
			if (comoara1 == 1) {
				score += 100;
				scoreUpdate();
			}
			comoara1 = 0;
		}
		if (linie == 7 && coloana == 12) {
			if (comoara2 == 1) {
				score += 100;
				scoreUpdate();
			}
			comoara2 = 0;
		}
		// n-au mai ramas comori = win

		if (comoara1 == 0 && comoara2 == 0) {
			scoreUpdate();
			gotoXY(7, 30);
			cout << GOLD "CONGRATS! You colected the money without being eaten!" NORMAL;
			gotoXY(8, 30);
			cout << "Press any key to go to main menu!";
			_getch();
			mainMenu();
		}

		/// kill MONSTRI 9,6 1,19
		if (linie == monst1X && coloana == monst1Y) { // verificam daca suntem in casuta cu monstrul
			if (monstru1 == 1) { // daca monstrul este viu
				if (bullets >= 1) { // daca avem gloante
					bullets -= 1; // trage un glont
					score -= 25; // atribuie scoruriile
					score += 50;
					monstru1 = 0; // seteaza monstul ca mort
					scoreUpdate(); // update afisare scor
					bulletsUpdate(); // update afisare gloante
				}
				else if (bullets < 1) { // daca nu mai avem gloante, monstrul ne omoara
					score -= 200; // atribuie scorul
					scoreUpdate(); // updatam scorul
					gotoXY(7, 30); // mergem la pozitia respectiva pentru a printa mesajul
					cout << RED "HAWL! YOU ARE MONSTER FOOD..." NORMAL;
					gotoXY(8, 30);
					cout << "Press any key to go to main menu!";
					_getch(); // asteptam apasarea unei taste inainte de a merge in main menu
					mainMenu(); // ne intoarcem la main menu
				}
			}
			monstru1 = 0;
		}
		if (linie == monst2X && coloana == monst2Y) {
			if (monstru2 == 1) {
				if (bullets >= 1) {
					bullets -= 1;
					score -= 25;
					score += 50;
					monstru2 = 0;
					scoreUpdate();
					bulletsUpdate();
				}
				else if (bullets < 1) {
					score -= 200;
					scoreUpdate();
					scoreUpdate();
					gotoXY(7, 30);
					cout << RED "HAWL! YOU ARE MONSTER FOOD..." NORMAL;
					gotoXY(8, 30);
					cout << "Press any key to go to main menu!";
					_getch();
					mainMenu();
				}
			}
			monstru2 = 0;
		}
		if (linie == monst3X && coloana == monst3Y) {
			if (monstru3 == 1) {
				if (bullets >= 1) {
					bullets -= 1;
					score -= 25;
					score += 50;
					monstru3 = 0;
					scoreUpdate();
					bulletsUpdate();
				}
				else if (bullets < 1) {
					score -= 200;
					scoreUpdate();
					scoreUpdate();
					gotoXY(7, 30);
					cout << RED "HAWL! YOU ARE MONSTER FOOD..." NORMAL;
					gotoXY(8, 30);
					cout << "Press any key to go to main menu!";
					_getch();
					mainMenu();
				}
			}
			monstru3 = 0;
		}
		/*if (monstru1 == 0 || monstru2 == 0) {
			scoreUpdate();
			gotoXY(7, 30);
			cout << RED "HAWL! YOU ARE MONSTER FOOD..." NORMAL;
			gotoXY(8, 30);
			cout << "Press any key to go to main menu!";
			_getch();
			mainMenu();
		}*/

		///////////////

		switch ((direction = _getch())) { // movement player
		case UP:
			score += -1; // -1 la fiecare miscare
			scoreUpdate(); // updatam scorul
			gotoXY(6, 41); // mergem la pozitia respectiva si printam directia in se uita jucatorul
			cout << GOLD "^" NORMAL;
			if (pointDirect == 1) { // verificam daca se uita in directia respectiva pentru a avansa
				if (!(coloana == 3 && linie == 8) // obstacole "X"
					&& !((coloana > 2 && coloana < 10) && linie == 7)
					&& !(linie == 9 && coloana == 9)
					&& !(linie == 4 && (coloana > 7 && coloana < 13))
					&& !(linie == 6 && coloana == 18)
					&& !(linie == 9 && (coloana > 14 && coloana < 20)))
					if (linie > 1) {  //3,8 | 8,13 | 15,20 | 4,9 |2,6 |6,9 // verificam limitele harti
						gotoXY(linie, coloana); // printeaza pe pozitia actuala un space pentru a sterge caracterul inainte sa il mute
						cout << " "; 
						gotoXY(linie -= 1, coloana); // printeaza caracterul pe noua pozitie
						player();
					}
			}
			else {
				pointDirect = 1; // daca nu se uita in directia respectiva va pointa acum in acea directie
			}
			break;
		case DOWN:
			score += -1;
			scoreUpdate();
			gotoXY(6, 41);
			cout << GOLD "V" NORMAL;
			if (pointDirect == 2) {
				if (!(coloana == 3 && linie == 3)
					&& !((coloana > 2 && coloana < 10) && linie == 5)
					&& !(linie == 2 && (coloana > 7 && coloana < 13))
					&& !(linie == 1 && coloana == 18)
					&& !(linie == 7 && (coloana > 14 && coloana < 20)))
					if (linie < posX - 1) {
						gotoXY(linie, coloana);
						cout << " ";
						gotoXY(linie += 1, coloana);
						player();
					}
			}
			else {
				pointDirect = 2;
			}
			break;
		case LEFT:
			score += -1;
			scoreUpdate();
			gotoXY(6, 41);
			cout << GOLD "<" NORMAL;
			if (pointDirect == 3) {
				if (!(coloana == 4 && (linie >= 4 && linie <= 7))
					&& !(linie == 6 && coloana == 10)
					&& !(coloana == 10 && (linie > 6 && linie < 9))
					&& !(linie == 3 && coloana == 13)
					&& !(coloana == 19 && (linie > 1 && linie < 6))
					&& !(linie == 8 && coloana == 20))
					if (coloana > 1) {
						gotoXY(linie, coloana);
						cout << " ";
						gotoXY(linie, coloana -= 1);
						player();
					}
			}
			else {
				pointDirect = 3;
			}
			break;
		case RIGHT:
			score += -1;
			scoreUpdate();
			gotoXY(6, 41);
			cout << GOLD ">" NORMAL;
			if (pointDirect == 4) {
				if (!(coloana == 2 && (linie >= 4 && linie <= 7))
					&& !(coloana == 8 && (linie > 5 && linie < 9))
					&& !(linie == 3 && coloana == 7)
					&& !(coloana == 17 && (linie > 1 && linie < 6))
					&& !(linie == 8 && coloana == 14))
					if (coloana < posY - 1) {
						gotoXY(linie, coloana);
						cout << " ";
						gotoXY(linie, coloana += 1);
						player();
					}
			}
			else {
				pointDirect = 4;
			}
			break;
		case SPACE:
			mainMenu();
		}
	}
}



int main() { // main
	mainMenu();
}