#pragma once
#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <thread>
#include <Windows.h>
#include <conio.h>
#include "People.h"
#include "Lane.h"
#include <ctime>
#include "Car.h"
#include "Truck.h"
#include "Bird.h"
#include "Dinosaur.h"
#include "Menu.h"

//test
#include <ctime>
using namespace std;


#define MAXIMUM 8		// maximum number of stacles per lane
#define MINIMUM	3		// minimum number of stacles per lane
#define MAX_LEVEL 4
#define SIDE_WALK_HEIGHT 4		//  chiều cao vỉa hè
#define DISTANCE 5
#define SLEEP_TIME 25
#define MAX_LANE 8

class Game
{
private:
	vector<Lane> lane;
	People people;
	int level;
	Menu menu;
	thread t;
public:
	Game();
	void DrawGame();
	~Game();
	People GetPeople();
	void Init();
	void Run();
	void ThreadFunct();
	void ResetGame();
	void PauseGame();
	void ExitGame(HANDLE);
	void StartGame();
	void LoadGame(istream&);
	void SaveGame();
	void PauseGame(HANDLE);
	void ResumeGame(HANDLE);
	void UpdatePosPeople(char MOVING);
	void UpdatePosObstacle();
	bool IsImpact();
	void ProcessDead();
	void PrintObstacle();
	void PrintPeople();
	void PrintSeparator();
	void ClearBoard() const;
};


#endif // !_GAME_H
