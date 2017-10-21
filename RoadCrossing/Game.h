#pragma once
#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <thread>
#include <Windows.h>
#include "People.h"
#include "Lane.h"
#include <ctime>
#include "Car.h"
#include "Truck.h"
#include "Bird.h"
#include "Dinosaur.h"
using namespace std;


#define MAXIMUM 8		// maximum number of stacles per lane
#define MINIMUM	6		// minimum number of stacles per lane

class Game
{
private:
	vector<Lane> lane;
	People people;
public:
	Game();
	void DrawGame();
	~Game();
	People GetPeople();
	void ResetGame();
	void ExitGame(HANDLE);
	void StartGame();
	void LoadGame(istream&);
	void SaveGame();
	void PauseGame(HANDLE);
	void ResumeGame(HANDLE);
	void UpdatePosPeople(char MOVING);
	void UpdatePosObstacle();
	void PrintObstacle();
	void PrintPeople();
};


#endif // !_GAME_H
