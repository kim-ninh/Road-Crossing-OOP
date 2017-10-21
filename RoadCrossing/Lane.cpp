#include "Lane.h"

Lane::Lane()
{
	width = BOARD_GAME_RIGHT - BOARD_GAME_LEFT + 1;
	height = obs[0]->Height() + 1;
}

Lane::Lane(COORD coord, vector<Obstacle*> v, Direction theDirec)
{
	obs = v;
	pos = coord;
	direc = theDirec;
	height = obs[0]->Height() + 1;
	width = BOARD_GAME_RIGHT - BOARD_GAME_LEFT + 1;
}

Lane::~Lane()
{
	//int n = obs.size();

	//for (int i = 0; i < n; i++) {
	//	delete obs[i];
	//}
}

int Lane::Height()
{
	return height;
}

void Lane::UpdatePos()
{
	int n = obs.size();

	for (int i = 0; i < n; i++) {
		obs[i]->Move();
	}
}

void Lane::Print()
{
	int n = obs.size();

	for (int i = 0; i < n; i++) {
		obs[i]->Print();
	}

}
