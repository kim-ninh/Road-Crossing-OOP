
#define _CRT_SECURE_NO_WARNINGS
#include "Console.h"
#include "Game.h"
#include <conio.h>
#include <mutex>


using namespace std;


int main() {

	SetConsoleOutputCP(437);
	Game game;
	game.StartGame();
	
	//while (true) {
	//	PlaySound("Sound\\Only My Railgun", NULL, SND_ASYNC);
	//	Sleep(1000);
	//}


	_getch();
	return 0;
}
