#include "CarGame.h"
#include "Car.h"
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>
#include <memory>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <string>
#include <windows.h>
#include <iomanip>
#include "json.hpp"
#include <typeinfo>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

using namespace std;
std::vector<std::shared_ptr<Car>> carStore;


int test = 0;
CarGame::CarGame()
{

}


CarGame::~CarGame()
{
}


void CarGame::startCarGame()
{	
	int choices = 0;
	while (true)
	{
		if (_kbhit())
		{
			char select = _getch();
			if (select == 'W' || select == 'w')
			{
				if (choices == 1) choices--;
			}
			else if (select == 'S' || select == 's')
			{
				if (choices < 1) choices++;
			}
			else if (select == 'Q' || select == 'q')
			{
				break;
			}
		}
		if (choices == 0)
		{
			setCursorPosition(20, 20);
			cout << "> Track 1";
			setCursorPosition(20, 22);
			cout << "  Track 2";
			setCursorPosition(20, 24);
			cout << " W/S to Select | Q to Enter";
		}
		else if (choices == 1)
		{
			setCursorPosition(20, 20);
			cout << "  Track 1";
			setCursorPosition(20, 22);
			cout << "> Track 2";
			setCursorPosition(20, 24);
			cout << " W/S to Select | Q to Enter";
		}
		Sleep(30);
	}

	if (choices == 0)
	{
		textReader("TrackMap.txt");
	}
	else if (choices == 1)
	{
		textReader("TrackMap2.txt");
	}
	std::system("cls");
	carAmount = 0;
	inGame = true;
	update();

}

void CarGame::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void CarGame::update()
{
	while (true && inGame)
	{
		if (_kbhit())
		{
			checkUserInput(static_cast<char>(_getch()));
		}
		for (int i = 0; i < carAmount; i++)
		{
			if (carStore[i] != NULL)
			{
				carStore[i]->carMove(trackGrid, carStore[i]->nextDirection);
				if (carStore[i]->carfuel < 0)
				{				
					trackGrid[carStore[i]->carposyCur][carStore[i]->carposxCur] = '1';
					carStore[i] = NULL;
				}
			}
		}
		disPlayTrack();	
		Sleep(300);
	}
}

nlohmann::json CarGame::jsonReader(std::string filename)
{
	std::ifstream ifs(filename);
	nlohmann::json j2 = nlohmann::json::parse(ifs);
	return j2;
}

void CarGame::textReader(std::string filename)
{
	string line;
	ifstream myfile(filename);
	
	if (myfile.is_open())
	{
		int j = 0;
		while (getline(myfile, line))
		{
			for (int i = 0; i < trackSize; ++i) {
				trackGrid[j][i] = line[i];
			}		
			j++;
		}
		myfile.close();
	}
	else cout << "Error No File Founded";
}

void CarGame::checkUserInput(char userInput)
{
	if (userInput == 'D' || userInput == 'd')
	{
		spawnCar(1);
	}
	else if (userInput == 'A' || userInput == 'a')
	{
		spawnCar(2);
	}
	else if (userInput == 'X' || userInput == 'x')
	{
		inGame = false;
	}
	else if (userInput == 'H' || userInput == 'h')
	{
		if (carStore[0] != NULL)
		{
			carStore[0]->carMove(trackGrid, 2);
		}
		
	}
	else if (userInput == 'T' || userInput == 't')
	{
		if (carStore[0] != NULL)
		{
			carStore[0]->carMove(trackGrid, 1);
		}
	}
	else if (userInput == 'G' || userInput == 'g')
	{
		if (carStore[0] != NULL)
		{
			carStore[0]->carMove(trackGrid, 3);
		}
	}
	else if (userInput == 'F' || userInput == 'f')
	{
		if (carStore[0] != NULL)
		{
			carStore[0]->carMove(trackGrid, 4);
		}
	}
	else if (userInput == 'L' || userInput == 'l')
	{
		if (carStore[0] != NULL)
		{
			carStore[0]->pathFinding(trackGrid);
		}
	}
}

void CarGame::spawnCar(int type)
{
	srand((unsigned int)time(NULL));
	if (type == 1)
	{
		if (trackGrid[1][1] == '1')
		{
			auto car = std::make_shared<Car>();
			carStore.push_back(car);
			carStore[carAmount]->setCar(1);
			carStore[carAmount]->pathFinding(trackGrid);
			trackGrid[1][1] = '3';
			carAmount++;
		}

	}
	else if (type == 2)
	{
		if (trackGrid[1][1] == '1')
		{
			auto car = std::make_shared<Car>();
			carStore.push_back(car);
			carStore[carAmount]->setCar(2);
			carStore[carAmount]->pathFinding(trackGrid);
			trackGrid[1][1] = '4';
			carAmount++;
		}
	}
}

void CarGame::disPlayTrack()
{	
	for (int i = 0; i < trackSize; i++)
	{
		setCursorPosition(5, 5+2*i);
		for (int j = 0; j < trackSize; j++)
		{	
			if (trackGrid[i][j] == '0')
			{
				cout << " o ";
				
			}
			else if (trackGrid[i][j] == '1')
			{				
				cout << " . ";
				
			}
			else if (trackGrid[i][j] == '2')
			{				
				cout << "   ";
				
			}
			else if (trackGrid[i][j] == '3')
			{
				cout << " B ";
				
			}
			else if (trackGrid[i][j] == '4')
			{
				cout << " F ";
				
			}
		}
	}
	setCursorPosition(50, 15);
	cout <<  "A : Spawn Ferrari , D : Spawn Benz";
	for (int i = 0; i < carAmount; i++)
	{
		if (carStore[i] != NULL) {																	                             
			setCursorPosition(50, 17+i);
			cout << "                                                                    ";
			setCursorPosition(50, 17 + i);
			cout << "  " << " Car : " << i + 1 << " Fuel : " << carStore[i]->carfuel;
		}
	}
}
