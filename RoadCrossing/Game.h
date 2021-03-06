﻿#pragma once
#define _CRT_SECURE_NO_WARNINGS
#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <thread>
#include <Windows.h>
#include <conio.h>
#include "People.h"
#include "Lane.h"
#include "Car.h"
#include "Truck.h"
#include "Bird.h"
#include "Dinosaur.h"
#include "Menu.h"
#include <stdlib.h>
#include <filesystem>

//test
#include <ctime>
using namespace std;
using namespace std::experimental::filesystem;

#define MAXIMUM 8		// maximum number of stacles per lane
#define MINIMUM	2		// minimum number of stacles per lane
#define MAX_LEVEL 4
#define SIDE_WALK_HEIGHT 4		//  chiều cao vỉa hè
#define DISTANCE 5
#define SLEEP_TIME 25
#define MAX_LANE 8
#define CAR_SOUND_FREQ 4500			//4500
#define TRUCK_SOUND_FREQ 2500		//4000
#define BIRD_SOUND_FREQ	1000		//1500
#define DINOSAUR_SOUND_FREQ 4000	//5000


class Game
{
private:
	vector<Lane> lane;
	People people;
	int level;
	Menu menu;
	thread t;
	
	bool busy;
	bool IsExistFile(const char *fileName);
	void PrintLevel();
	void PrintMessage(string);
	vector<string> GetFileName(const char *path);
public:
	Game();
	void DrawGame();
	~Game();
	void Init();
	void Run();
	void ThreadFunct();
	void ResetGame();
	void PauseGame();
	void ExitGame();
	void StartGame();
	void LoadGame();
	void SaveGame();
	bool IsLevelUp();
	void LevelUp();
	void ResumeGame();
	void UpdatePosPeople(const char MOVING);
	void UpdatePosObstacle();
	bool IsImpact();
	void ProcessDead();
	void PrintObstacle();
	void PrintPeople();
	void PrintSeparator();
	void ClearBoard() const;
	void Deallocate();
	void TellObstacle();
};

#endif // !_GAME_H
