#pragma once
#include "Obstacle.h"
#pragma comment(lib, "Winmm.lib" )


Obstacle::Obstacle()
{
	oldX = -1;
}

Obstacle::Obstacle(Direction theDirec)
{
	direc = theDirec;
	oldX = -1;
}

Obstacle::Obstacle(int x, int y, Direction theDirec)
{
	mX = x;
	mY = y;
	direc = theDirec;
	oldX = -1;
}

void Obstacle::Move()
{
	Figure fig = GetFigure();
	int width = fig.Width();
	COORD pos;

	if (direc == LEFT) {
		if (mX + width - 1 < BOARD_RIGHT_EDGE) {
			oldX = mX + width - 1;
		}

		if (mX + width - 1 > BOARD_GAME_LEFT + 1) {			// chưa qua hết cạnh khung bên trái
			mX--;
		}
		else {
			mX = BOARD_GAME_RIGHT - width + 1;
		}
	}
	else {
		if (mX > BOARD_LEFT_EDGE) {
			oldX = mX;
		}

		if (mX < BOARD_GAME_RIGHT) {			// chưa qua hết cạnh khung bên phải
			mX++;
		}
		else {
			mX = BOARD_GAME_LEFT + 1;
		}
	}
}

void Obstacle::Tell()
{
	const char *sound_file_name = GetSoundFileName();
	PlaySound(sound_file_name, NULL, SND_ASYNC); //SND_FILENAME or SND_LOOP SND_ASYNC
}

int Obstacle::Width()
{
	Figure fig = GetFigure();
	return fig.Width();
}

int Obstacle::Height()
{
	Figure fig = GetFigure();
	return fig.Height();
}

void Obstacle::EraseOldPos()
{
	Figure fig = GetFigure();
	int height = fig.Height();

	for (int i = 0; i < height; i++) {
		GotoXY(oldX, mY + i);
		/*cout << " ";*/
		lock_guard<mutex> lock(theLock);
		printf(" ");
	}
}

void Obstacle::Print()
{
	Figure fig = GetFigure();
	int width = fig.Width();

	if (oldX > 0 && oldX != BOARD_GAME_RIGHT && oldX != BOARD_GAME_LEFT) {
		EraseOldPos();
	}

	if (direc == LEFT) {
		
		if (mX >= BOARD_GAME_RIGHT) {
			return;
		}
		//else if (mX < BOARD_GAME_LEFT && mX + width - 1 > BOARD_GAME_LEFT) {
		//	short a = BOARD_GAME_RIGHT - (BOARD_GAME_LEFT - mX + 1);
		//	Obstacle *newObs = this->Clone(a, mY);
		//	newObs->Print();
		//	delete newObs;
		//}
	}
	else if (direc == RIGHT) {

		if (mX + width - 1 < BOARD_GAME_LEFT) {
			return;
		}
		else if (mX < BOARD_GAME_RIGHT && mX + width - 1 > BOARD_GAME_RIGHT) {
			Obstacle * newObs = this->Clone(BOARD_GAME_LEFT - (BOARD_GAME_RIGHT - mX) + 1, mY);
			newObs->Print();
			delete newObs;
		}
	}


	fig.Print(mX, mY);
}

COORD Obstacle::GetPosition()
{
	COORD pos = { mX,mY };

	return pos;
}

void Obstacle::SetPosition(short x, short y)
{
	mX = x;
	mY = y;
}

//bool Obstacle::IsImpact(People& people)
//{
//	vector<string> obs_fig = *(const_cast<vector<string>*>(this->GetFigure()).Get());
//	)
//	Figure people_fig = people.GetFigure();
//}
