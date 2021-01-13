#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdio.h>
#include <io.h>
#include <Windows.h>
#include <locale>
#include <algorithm>
#include <fcntl.h>
#include <valarray>
#include <conio.h>

using namespace std;

/*
#define escape 27
#define enter 13
#define space 32
#define tab 9
#define BackSlash 92
*/
/*
#define UgolUpLeft (char)218
#define UgolUpRight (char)191
#define UgolDownLeft (char)192
#define UgolDownRight (char)217
#define HorizontalLine (char)196
#define VerticalLine (char)179
#define Kvadrat (char)219
#define space 32
*/

#define offset_top "\n\n\n\n\n\n\n\n"
#define offset_left "\t\t\t\t\t\t\t"

void Check(char field[], const int n, char player);
void PrintField(char field[], const int n, char player);
void Move(char field[], const int n, char player);
void randomError();

int main()
{
	setlocale(LC_ALL, "");
	system("Color 0A");

	const int n = 9;
	char field[n] = {};

	PrintField(field, n, 'O');

}


void PrintField(char field[], const int n, char player)
{
	system("CLS");

	cout << offset_top;

	for (int i = 6; i >= 0; i -= 3)
	{
		cout << offset_left << " ";

		for (int j = 0; j < 3; j++)
		{
			cout << field[i + j];
			if (j != 2)cout << " | ";
		}
		cout << endl;
		cout << offset_left;
		if (i != 0)cout << "-----------";
		cout << endl;
	}
	Check(field, n, player);
}

void randomError()
{
	srand(time(NULL));
	string Random[3] = { "Уже занято", "Это место уже занято", "Занято" };
	string randmass = Random[rand() % 3];

	cout << randmass << " " << endl;
	srand(time(NULL));
}

void Move(char field[], const int n, char player)
{
	char key;
	bool busy;

	do
	{
		busy = false;
		do
		{
			key = _getch();
			if (key == 27)return;
			if ((key < '1' || key > '9') && key != 27)cout << "Жмите на цифры :)\n";


		} while (key < '1' || key > '9');

		if (field[key - 49] != 0)
		{
			busy = true;
			randomError();
		}

		else
		{
			field[key - 49] = player;
		}
		

	} while (busy);

	PrintField(field, n, player);
}

void Check(char field[], const int n, char player)
{
	bool gameover = false;
	int hr;
	int vr;
	/*bool NoSpace = false;*/

	//Диоганали
	if (
		field[0] == field[4] && field[4] == field[8] && field[8] != 0 ||
		field[2] == field[4] && field[4] == field[6] && field[6] != 0
		)
		gameover = true;
	    
	    //Горизонтали
		for (hr = 0; hr < 7; hr += 3)
		{
			if (field[hr] == field[hr + 1] && field[hr] == field[hr + 2] && field[hr] != 0)gameover = true;
		//Вертикали
			for (vr = 0; vr < 3; vr++)
			{
				if (field[vr] == field[vr + 3] && field[vr] == field[vr + 6] && field[vr] != 0)gameover = true;
			}
		}

		char yesno2;

		//ничья
	if ((field[0] && field[1] && field[2] && field[3] && field[4] && field[5] && field[6] && field[7] && field[8]) != 0)
	{
		/*NoSpace = true;*/
		cout << "Ничья" << endl << endl;
		cout << "Ещё разок?" << endl;
		cout << "Y/any: "; cin >> yesno2;
		if (yesno2 == 'Y' || yesno2 == 'y')
		{
			main();
		}
		else
		{
			return;
		}
	}

	if (gameover == true)
	{
		cout << player << " Wins" << endl << endl;
	}
	else
	{
		if(player == 'X')Move(field, n, 'O');
		else Move(field, n, 'X');
	}

	char yesNo;

	if (gameover)
	{
		cout << "Ещё разок?" << endl;
		cout << "Y/any: "; cin >> yesNo;
		if (yesNo == 'Y' || yesNo == 'y')
		{
			main();
		}
	}
}