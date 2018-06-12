#pragma once
#include <string>
#include <vector>
#include "json.hpp"
#include "Car.h"
class CarGame
{
public:
	CarGame();
	~CarGame();
	int track;
	int carAmount;
	void setCursorPosition(int x, int y);
	void startCarGame();
	void update();
	void checkUserInput(char userInput);
	nlohmann::json jsonReader(std::string filename);
	void textReader(std::string filename);
	void disPlayTrack();
	int trackSize = 10;
	bool inGame;
	std::string trackStore;
	char trackGrid[10][10] = { "0" };
	void spawnCar(int type);
	
};

