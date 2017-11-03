#pragma once
#include "Game.h"



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

	int pos;			// biến tạm giữ vị trí
	int arr[8] = { 0 };		// mảng chứa 8 số random tượng trưng cho 8 lane
	Figure fig;
	short height = HEIGHT_OFFSET + 1 + SIDE_WALK_HEIGHT + 1;			// chiều cao tính từ đầu màn hình console

	srand(static_cast<unsigned>(time(nullptr)));

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

		n = (MINIMUM + level) + 1;		// số vật thể của lane, 1 là vật thể dự bị của lane
		x = rand() % (BOARD_GAME_RIGHT - BOARD_GAME_LEFT - 1) + (BOARD_GAME_LEFT + 1);
		direc = i % 2 == 0 ? LEFT : RIGHT;
		vector<Obstacle*> v;
	
		switch (arr[i])
		{
		case 1:
			v.push_back(new Car(0, 0, direc));
			for (int i = 1; i < n; i++) {
				obs = new Car(x, height + 1, direc);
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
			v.push_back(new Bird(0, 0, direc));

			for (int i = 1; i < n; i++) {
				obs = new Bird(x, height + 1, direc);
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
			v.push_back(new Truck(0, 0, direc));

			for (int i = 1; i < n; i++) {
				obs = new Truck(x, height + 1, direc);
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
			v.push_back(new Dinosaur(0, 0, direc));

			for (int i = 1; i < n; i++) {
				obs = new Dinosaur(x, height + 1, direc);
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
	PrintPeople();
	t = thread(&Game::ThreadFunct, this);

	while (true) {

		char ch = toupper(_getch());
		if (ch == 'A' || ch == 'D' || ch == 'S' || ch == 'W') {

			UpdatePosPeople(ch);

			lock_guard<mutex> lock(theLock);
			PrintPeople();
		}
		else if (ch=='P') {
			PauseGame();
		}
		else if (ch =='S') {
			SuspendThread(t.native_handle());
		}
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

		if (IsImpact()) {
			ProcessDead();
		}

		PrintSeparator();

		delete lock;
		Sleep(SLEEP_TIME);
	}
}

void Game::ResetGame()
{

}

void Game::PauseGame()
{
	lock_guard<mutex> lock(theLock);
	SuspendThread(t.native_handle());
	ClearBoard();
	menu.Set("pause");
	menu.Print();
	string select = menu.Select();
	if (select == "CONTINUE") {
		menu.Erase();
		PrintPeople();
		//delete lock;
		ResumeThread(t.native_handle());
	}

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

bool Game::IsImpact()
{
	const short people_top = people.GetPosition().Y;
	const short people_bot = people.GetPosition().Y + people.Height() - 1;

	if (people_bot <= lane[0].GetPos().Y) {
		return false;
	}

	if (people_top > lane[MAX_LANE - 1].GetPos().Y + lane[MAX_LANE - 1].Height()) {
		return false;
	}

	for (int i = 0; i < MAX_LANE; i++) {

		const short lane_top = lane[i].GetPos().Y;
		const short lane_bot = lane[i].GetPos().Y + lane[i].Height() - 1;

		if (lane_top >= people_bot) {
			break;
		}

		if ((people_top >= lane_top && people_top <= lane_bot)
			|| (people_bot > lane_top && people_bot <= lane_bot)) {
			
			if (lane[i].IsImpact(people)) {
				return true;
			}
		}
	}

	return false;
}

void Game::ProcessDead()
{
	const clock_t begin = clock();
	const int delay_time = 1;

	while ((clock() - begin) / CLOCKS_PER_SEC < delay_time);

	ClearBoard();
	menu.Set("lose");
	menu.Print();
	string select = menu.Select();

	if (select == "RESTART") {
		menu.Erase();
		lane.clear();
		this->Init();
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
	const short people_top = people.GetPosition().Y;
	const short people_bot = people_top + people.Height() - 1;
	const short people_left = people.GetPosition().X;
	const short people_right = people_left + people.Width() - 1;

	for (int k = 0; k < 9; k++) {
		if (k == 0 || k == 8) {
			if (people_top <= y && people_bot >= y) {
				for (int i = BOARD_GAME_LEFT + 1; i < people_left; i++) {
					s[k] += '_';
				}
				s[k] += people.GetFigure().Get()[y - people_top];
				for (int i = people_right + 1; i < BOARD_GAME_RIGHT; i++) {
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
			if (people_top <= y && people_bot >= y) {
				for (int i = BOARD_GAME_LEFT + 1; i < people_left; i++) {
					s[k] += i % 2 == 0 ? '_' : ' ';
				}
				s[k] += people.GetFigure().Get()[y - people_top];
				for (int i = people_right + 1; i < BOARD_GAME_RIGHT; i++) {
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
			y = lane[k].GetPos().Y + lane[k].Height();
		}
	}
	
	y = HEIGHT_OFFSET + 1 + SIDE_WALK_HEIGHT;
	for (int i = 0; i < 9; i++) {
		GotoXY(BOARD_GAME_LEFT + 1, y);
		printf("%s", s[i].c_str());
		if (i < 8) {
			y = lane[i].GetPos().Y + lane[i].Height();
		}
	}
}

void Game::ClearBoard() const
{
	string s;
	for (int i = BOARD_LEFT_EDGE + 1; i < BOARD_RIGHT_EDGE; i++) {
		s += ' ';
	}

	for (int i = BOARD_TOP_EDGE + 1; i < BOARD_BOTTOM_EDGE; i++) {
		GotoXY(BOARD_LEFT_EDGE + 1, i);
		printf("%s", s.c_str());
	}
}
