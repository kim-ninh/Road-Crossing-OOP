#pragma once
#include "People.h"

Figure People::fig("Figure\\People.txt");

People::People(int x, int y)
{
	mX = x;
	mY = y;
}

void People::Up(int)
{
	oldPos.clear();
	int width = this->Width();
	int height = this->Height();
	COORD pos = { 0, mY + height - 1 };

	for (int i = 0; i < width; i++) {
		pos.X = mX + i;
		pos.Y = mY + height - 1;
		oldPos.push_back(pos);
	}

	if (mY > BOARD_TOP_EDGE + 1) {
		mY--;
	}
}

void People::Left(int)
{
	oldPos.clear();
	int width = this->Width();
	int height = this->Height();
	COORD pos = { mX + width - 1};

	for (int i = 0; i < height; i++) {
		pos.Y = mY + i;
		oldPos.push_back(pos);
	}

	if (mX > BOARD_LEFT_EDGE + 1) {
		mX--;
	}
}

void People::Right(int)
{
	oldPos.clear();
	int width = this->Width();
	int height = this->Height();
	COORD pos = { mX };

	for (int i = 0; i < height; i++) {
		pos.Y = mY + i;
		oldPos.push_back(pos);
	}

	if (mX + fig.Width() - 1 < BOARD_RIGHT_EDGE - 1) {
		mX++;
	}
}

void People::Down(int)
{
	oldPos.clear();
	int width = this->Width();
	int height = this->Height();
	COORD pos = { 0, mY };

	for (int i = 0; i < width; i++) {
		pos.X = mX + i;
		oldPos.push_back(pos);
	}

	if (mY + fig.Height() - 1 < BOARD_BOTTOM_EDGE - 1) {
		mY++;
	}
}

bool People::IsImpact(const Obstacle *&)
{
	return false;
}

bool People::IsFinish()
{
	return false;
}

bool People::IsDead()
{
	return false;
}

void People::Print()
{
	this->EraseOld();
	fig.Print(mX, mY);
}

void People::EraseOld()
{
	int len = oldPos.size();

	for (int i = 0; i < len; i++) {
		GotoXY(oldPos[i]);
		lock_guard<mutex> lock(theLock);
		printf(" ");
	}
}

int People::Width()
{
	return fig.Width();
}

int People::Height()
{
	return fig.Height();
}
