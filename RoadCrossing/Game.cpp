#pragma once
#include "Game.h"

Game::Game()
{
	// Tạo các lane vật thể

	int i = 0, pos, arr[8] = { 0 };
	Figure fig;
	short height = HEIGHT_OFFSET + 1 + 4;
	
	srand((unsigned)time(NULL));

	// tạo 8 số ngẫu nhiên từ 1 tới 4, mỗi số lặp lại đúng 2 lần
	for (int i = 1; i <= 4; i++) {

		for (int j = 0; j < 2; j++) {
			do {
				pos = rand() % 8;
			} while (arr[pos]);
			arr[pos] = i;
		}
	}


	int n = 0;
	int x;
	int distance = 4;
	Obstacle *obs;
	Direction direc;
	COORD lanePos;
	for (int i = 0; i < 8; i++) {

		n = rand() % (MAXIMUM - MINIMUM + 1) + MINIMUM;		// random số vật thể của lane
		x = rand() % (BOARD_GAME_RIGHT - BOARD_GAME_LEFT - 1) + (BOARD_GAME_LEFT + 1);
		direc = i % 2 == 0 ? LEFT : RIGHT;
		vector<Obstacle*> v;

		switch (arr[i])
		{
		case 1:
			for (int i = 0; i < n; i++) {
				obs = new Car(x, height, direc);
				v.push_back(obs);
				
				if (direc == LEFT) {
					x += obs->Width() + distance;
				}
				else {
					x -= obs->Width() + distance;
				}
			}

			lanePos = { BOARD_GAME_LEFT + 1,height };
			lane.push_back(Lane(lanePos, v, direc));
			break;

		case 2:
			for (int i = 0; i < n; i++) {
				obs = new Bird(x, height, direc);
				v.push_back(obs);

				if (direc == LEFT) {
					x += obs->Width() + distance;
				}
				else {
					x -= obs->Width() + distance;
				}
			}

			lanePos = { BOARD_GAME_LEFT + 1,height };
			lane.push_back(Lane(lanePos, v, direc));
			break;

		case 3:
			for (int i = 0; i < n; i++) {
				obs = new Truck(x, height, direc);
				v.push_back(obs);

				if (direc == LEFT) {
					x += obs->Width() + distance;
				}
				else {
					x -= obs->Width() + distance;
				}
			}

			lanePos = { BOARD_GAME_LEFT + 1,height };
			lane.push_back(Lane(lanePos, v, direc));
			break;

		case 4:
			for (int i = 0; i < n; i++) {
				obs = new Dinosaur(x, height, direc);
				v.push_back(obs);

				if (direc == LEFT) {
					x += obs->Width() + distance;
				}
				else {
					x -= obs->Width() + distance;
				}
			}

			lanePos = { BOARD_GAME_LEFT + 1,height };
			lane.push_back(Lane(lanePos, v, direc));
			break;

		}

		height += lane[i].Height();
		v.clear();
	}

	people = People(30, BOARD_GAME_BOTTOM - people.Height());
}

void Game::DrawGame()
{
	int n = lane.size();

	for (int i = 0; i < n; i++) {
		lane[i].Print();
	}

	people.Print();
}

Game::~Game()
{
}

People Game::GetPeople()
{
	return People();
}

void Game::ResetGame()
{
}

void Game::ExitGame(HANDLE)
{
}

void Game::StartGame()
{
}

void Game::LoadGame(istream &)
{
}

void Game::SaveGame()
{
}

void Game::PauseGame(HANDLE)
{
}

void Game::ResumeGame(HANDLE)
{
}

void Game::UpdatePosPeople(char MOVING)
{
	people.Move(MOVING);
}

void Game::UpdatePosObstacle()
{
	int n = lane.size();

	for (int i = 0; i < n; i++) {
		lane[i].UpdatePos();
	}
}

void Game::PrintObstacle()
{
	int n = lane.size();

	for (int i = 0; i < n; i++) {
		lane[i].Print();
	}
}

void Game::PrintPeople()
{
	people.Print();
}
