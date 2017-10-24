#pragma once
#include "Game.h"


int Game::level = 0;

Game::Game()
{
	
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

void Game::Init()
{
	// Tạo các lane vật thể

	int i = 0, pos, arr[8] = { 0 };
	Figure fig;
	short height = HEIGHT_OFFSET + 1 + SIDE_WALK_HEIGHT + 1;

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
	Obstacle *obs;
	Direction direc;
	COORD lanePos;
	for (int i = 0; i < 8; i++) {

		n = MINIMUM + level;		// random số vật thể của lane
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
					x += obs->Width() + DISTANCE;
				}
				else {
					x -= obs->Width() + DISTANCE;
				}
			}

			lanePos = { BOARD_GAME_LEFT + 1,height };
			lane.push_back(Lane(lanePos, v, direc));
			break;

		case 2:
			n *= 2;
			for (int i = 0; i < n; i++) {
				obs = new Bird(x, height, direc);
				v.push_back(obs);

				if (direc == LEFT) {
					x += obs->Width() + DISTANCE;
				}
				else {
					x -= obs->Width() + DISTANCE;
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
					x += obs->Width() + DISTANCE;
				}
				else {
					x -= obs->Width() + DISTANCE;
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
					x += obs->Width() + DISTANCE;
				}
				else {
					x -= obs->Width() + DISTANCE;
				}
			}

			lanePos = { BOARD_GAME_LEFT + 1,height };
			lane.push_back(Lane(lanePos, v, direc));
			break;

		}

		height += lane[i].Height() + 1;				// cộng 1 là cộng thêm độ cao của dải phân cách
		v.clear();
	}

	people = People((BOARD_GAME_LEFT + BOARD_GAME_RIGHT) / 2, BOARD_GAME_BOTTOM - people.Height());
}

void Game::Run()
{
	thread t(&Game::ThreadFunct, this);

	PrintPeople();
	while (true) {

		char ch = toupper(_getch());
		if (ch == 'A' || ch == 'D' || ch == 'S' || ch == 'W') {
			UpdatePosPeople(ch);
		}
		lock_guard<mutex> lock(theLock);
		PrintPeople();
	}
}

void Game::ThreadFunct()
{
	COORD pos;
	while (true) {
		//pos = GetCursorPosition();

		UpdatePosObstacle();
		lock_guard<mutex> *lock = new lock_guard<mutex>(theLock);
		PrintObstacle();
		PrintSeparator();
		delete lock;
		Sleep(25);
	}
}

void Game::ResetGame()
{
}

void Game::ExitGame(HANDLE)
{
}

void Game::StartGame()
{
	PlaySound("Sound\\TheFatRat_Unity.wav", NULL, SND_ASYNC);
	string select = menu.Select();
	menu.Erase();
	if (select == "NEW GAME") {
		Init();
		Run();
	}
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

void Game::PrintSeparator()
{
	int y = HEIGHT_OFFSET + 1 + SIDE_WALK_HEIGHT;
	string s[9];
	COORD peoplePos = people.GetPosition();

	for (int k = 0; k < 9; k++) {
		if (k == 0 || k == 8) {
			if (peoplePos.Y <= y && peoplePos.Y + people.Height() - 1 >= y) {
				for (int i = BOARD_GAME_LEFT + 1; i < peoplePos.X; i++) {
					s[k] += '_';
				}
				s[k] += people.GetFigure().Get()[y - peoplePos.Y];
				for (int i = peoplePos.X + people.Width(); i < BOARD_GAME_RIGHT; i++) {
					s[k] += '_';
				}
			}
			else {
				for (int i = BOARD_GAME_LEFT + 1; i < BOARD_GAME_RIGHT; i++) {
					s[k] += '_';
				}
			}
		}
		else {
			if (peoplePos.Y <= y && peoplePos.Y + people.Height() - 1 >= y) {
				for (int i = BOARD_GAME_LEFT + 1; i < peoplePos.X; i++) {
					s[k] += i % 2 == 0 ? '_' : ' ';
				}
				s[k] += people.GetFigure().Get()[y - peoplePos.Y];
				for (int i = peoplePos.X + people.Width(); i < BOARD_GAME_RIGHT; i++) {
					s[k] += i % 2 == 0 ? '_' : ' ';
				}
			}
			else {
				for (int i = BOARD_GAME_LEFT + 1; i < BOARD_GAME_RIGHT; i++) {
					s[k] += i % 2 == 0 ? '_' : ' ';
				}
			}
		}

		if (k < 8) {
			y = lane[k].GetPos().Y + lane[k].Height() - 1;
		}
	}
	
	y = HEIGHT_OFFSET + 1 + SIDE_WALK_HEIGHT;
	for (int i = 0; i < 9; i++) {
		GotoXY(BOARD_GAME_LEFT + 1, y);
		printf("%s", s[i].c_str());
		if (i < 8) {
			y = lane[i].GetPos().Y + lane[i].Height() - 1;
		}
	}
}
