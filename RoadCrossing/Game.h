#pragma once
#ifndef _GAME_H
#define _GAME_H

#include <iostream>
#include <thread>
#include <Windows.h>
#include "People.h"
#include "Lane.h"
using namespace std;

class Game
{
private:
	vector<Lane> lane;
	People *pPeople;
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
	void UpdatePosPeople(char);
	void UpdatePosVehicle();
	void UpdatePosAnimal();
};


#endif // !_GAME_H
