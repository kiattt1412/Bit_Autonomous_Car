#pragma once
#include "CarGame.h"
class Car
{
public:
	Car();
	~Car();
	int cartype;
	int carposxCur, carposyCur;
	int carposxBef, carposyBef;
	float moveDelay;
	float carfuel;
	int nextDirection;
	int lastDirection;
	void setCar(int type);
	void carMove(char mg[10][10],int direction);
	void pathFinding(char mg[10][10]);
	
};

