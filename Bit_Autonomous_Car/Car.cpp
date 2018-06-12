#include "Car.h"
#include "CarGame.h"
#include "iostream"


Car::Car()
{
	
}


Car::~Car()
{
}

void Car::setCar(int type)
{
	auto cc = std::make_shared<CarGame>();
	carposxCur = 1;
	carposyCur = 1;
	carposxBef = 0;
	carposyBef = 0;
	lastDirection = 2;
	cartype = type;
	if (cartype == 1)
	{
		carfuel = cc->jsonReader("carinformation.json")["Benz"]["Fuel"];	
		moveDelay = 1;
	}
	else if (cartype == 2)
	{
		carfuel = cc->jsonReader("carinformation.json")["Ferrari"]["Fuel"];
		moveDelay = 0.5;
	}
}

void Car::carMove(char mg[10][10],int direction)
{
	//1top 2right 3down 4left
	if (direction == 1)
	{
		if (mg[carposyCur-1][carposxCur] == '1')
		{
			mg[carposyCur][carposxCur] = '1';
			if (cartype == 1)
			{
				mg[carposyCur-1][carposxCur ] = '3';
			}
			else if (cartype == 2)
			{
				mg[carposyCur-1][carposxCur] = '4';
			}
			carposyBef = carposyCur;
			carposxBef = carposxCur;
			carposyCur -= 1;
			carfuel -= 10;
			
		}
		pathFinding(mg);
	}
	else if (direction == 2)
	{
		if (mg[carposyCur][carposxCur + 1] == '1')
		{
			mg[carposyCur][carposxCur] = '1';
			if (cartype == 1)
			{
				mg[carposyCur][carposxCur+1] = '3';
			}
			else if (cartype == 2)
			{
				mg[carposyCur][carposxCur + 1] = '4';
			}
			carposyBef = carposyCur;
			carposxBef = carposxCur;
			carposxCur += 1;
			carfuel -= 10;
			
		}
		pathFinding(mg);
	}
	else if (direction == 3)
	{
		if (mg[carposyCur+1][carposxCur] == '1')
		{
			mg[carposyCur][carposxCur] = '1';
			if (cartype == 1)
			{
				mg[carposyCur+1][carposxCur] = '3';
			}
			else if (cartype == 2)
			{
				mg[carposyCur+1][carposxCur] = '4';
			}
			carposyBef = carposyCur;
			carposxBef = carposxCur;
			carposyCur += 1;
			carfuel -= 10;
			
		}
		pathFinding(mg);
	}
	else if (direction == 4)
	{
		if (mg[carposyCur][carposxCur - 1] == '1')
		{
			mg[carposyCur][carposxCur] = '1';
			if (cartype == 1)
			{
				mg[carposyCur][carposxCur - 1] = '3';
			}
			else if (cartype == 2)
			{
				mg[carposyCur][carposxCur - 1] = '4';
			}
			carposyBef = carposyCur;
			carposxBef = carposxCur;
			carposxCur -= 1;
			carfuel -= 10;
			
		}
		pathFinding(mg);
	}
	
}

void Car::pathFinding(char mg[10][10])
{
	if (lastDirection == 1)
	{
		if (mg[carposyCur - 1][carposxCur] == '1')
		{			
				nextDirection = 1;	
				lastDirection = nextDirection;
		}
		else if (mg[carposyCur][carposxCur + 1] == '1')
		{			
				nextDirection = 2;
				lastDirection = nextDirection;
		}
		else if (mg[carposyCur][carposxCur - 1] == '1')
		{		
				nextDirection = 4;	
				lastDirection = nextDirection;
		}
	}
	else if (lastDirection == 2)
	{
		if (mg[carposyCur - 1][carposxCur] == '1')
		{

				nextDirection = 1;
				lastDirection = nextDirection;
		}
		else if (mg[carposyCur][carposxCur + 1] == '1')
		{
				nextDirection = 2;
				lastDirection = nextDirection;

		}
		else if (mg[carposyCur + 1][carposxCur] == '1')
		{
				nextDirection = 3;
				lastDirection = nextDirection;
		}
	}
	else if (lastDirection == 3)
	{
		if (mg[carposyCur][carposxCur + 1] == '1')
		{
			
				nextDirection = 2;
				lastDirection = nextDirection;
	
		}
		else if (mg[carposyCur + 1][carposxCur] == '1')
		{
			
				nextDirection = 3;
				lastDirection = nextDirection;
			
		}
		else if (mg[carposyCur][carposxCur - 1] == '1')
		{
			
				nextDirection = 4;
				lastDirection = nextDirection;
			
		}
	}
	else if (lastDirection == 4)
	{
		if (mg[carposyCur - 1][carposxCur] == '1')
		{
			
				nextDirection = 1;
				lastDirection = nextDirection;
			
		}

		else if (mg[carposyCur + 1][carposxCur] == '1')
		{
			
				nextDirection = 3;
				lastDirection = nextDirection;
			
		}
		else if (mg[carposyCur][carposxCur - 1] == '1')
		{
			
				nextDirection = 4;
				lastDirection = nextDirection;
			
		}
	}
}