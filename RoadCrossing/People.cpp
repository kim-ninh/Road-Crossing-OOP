#pragma once
#include "People.h"

Figure People::fig("Figure\\People.txt");

People::People(int x, int y)
{
	mX = x;
	mY = y;
	COORD temp = { -1,-1 };
	oldPos.push_back(temp);
}

void People::Up()
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

	if (mY > BOARD_GAME_TOP + 1) {
		mY--;
	}
}

void People::Left()
{
	oldPos.clear();
	int width = this->Width();
	int height = this->Height();
	COORD pos = { mX + width - 1};

	for (int i = 0; i < height; i++) {
		pos.Y = mY + i;
		oldPos.push_back(pos);
	}

	if (mX > BOARD_GAME_LEFT + 1) {
		mX--;
	}
}

void People::Right()
{
	oldPos.clear();
	int width = this->Width();
	int height = this->Height();
	COORD pos = { mX };

	for (int i = 0; i < height; i++) {
		pos.Y = mY + i;
		oldPos.push_back(pos);
	}

	if (mX + fig.Width() - 1 < BOARD_GAME_RIGHT - 1) {
		mX++;
	}
}

void People::Down()
{
	oldPos.clear();
	int width = this->Width();
	int height = this->Height();
	COORD pos = { 0, mY };

	for (int i = 0; i < width; i++) {
		pos.X = mX + i;
		oldPos.push_back(pos);
	}

	if (mY + fig.Height() - 1 < BOARD_GAME_BOTTOM - 1) {
		mY++;
	}
}

void People::Move(char MOVING)
{
	if (MOVING == 'A') {
		this->Left();
	}
	else if (MOVING == 'D') {
		this->Right();
	}
	else if (MOVING == 'S') {
		this->Down();
	}
	else if (MOVING == 'W') {
		this->Up();
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
	if (oldPos[0].X > 0) {
		this->EraseOld();
	}
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

COORD People::GetPosition()
{
	COORD pos = { mX,mY };
	return pos;
}

Figure& People::GetFigure()
{
	return fig;
}

int People::Width()
{
	if (fig.width == 0) {
		Figure f("Figure\\people.txt");
		return f.Width();
	}
	return fig.Width();
}

int People::Height()
{
	if (fig.height == 0) {
		Figure f("Figure\\people.txt");
		return f.Height();
	}
	return fig.Height();
}
