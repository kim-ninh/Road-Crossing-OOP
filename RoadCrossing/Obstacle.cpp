#pragma once
#include "Obstacle.h"
#pragma comment(lib, "Winmm.lib" )


Obstacle::Obstacle()
{
}

Obstacle::Obstacle(Direction theDirec)
{
	direc = theDirec;
}

Obstacle::Obstacle(int x, int y, Direction theDirec)
{
	mX = x;
	mY = y;
	direc = theDirec;
}

void Obstacle::Move()
{
	Figure fig = GetFigure();
	int width = fig.Width();
	COORD pos;

	if (direc == LEFT) {
		
		oldX = mX + width - 1;

		if (mX + width - 1 > BOARD_LEFT_EDGE + 1) {			// chưa qua hết cạnh khung bên trái
			mX--;
		}
		else {
			mX = BOARD_RIGHT_EDGE - 1;
		}
	}
	else {
		
		oldX = mX;

		if (mX < BOARD_RIGHT_EDGE) {			// chưa qua hết cạnh khung bên phải
			mX++;
		}
		else {
			mX = BOARD_LEFT_EDGE + 1;
		}
	}
}

void Obstacle::Tell()
{
	const char *sound_file_name = GetSoundFileName();
	PlaySound(sound_file_name, NULL, SND_ASYNC); //SND_FILENAME or SND_LOOP SND_ASYNC
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

	if (oldX != BOARD_RIGHT_EDGE && oldX != BOARD_LEFT_EDGE) {
		EraseOldPos();
	}

	fig.Print(mX, mY);
}
