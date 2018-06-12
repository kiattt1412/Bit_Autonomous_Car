#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <crtdbg.h>
#include <memory>
#include <stdlib.h>
#include <cstdlib>
#include <windows.h>
#define _CRTDBG_MAP_ALLOC

#include "CarGame.h"

auto carcall = std::make_shared<CarGame>();

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	carcall->startCarGame();

	return 0;
}


