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
	light.updateTimeNum();					//Cập nhật thời gian đếm ngược của đèn trước

	if (light.isRedActivated() == false)		//đèn xanh thì phwong tiện đứng yên, người di chuyển!!!
		return;

	for (int i = 0; i < n; i++) {
		obs[i]->Move();
	}
}

void Lane::Print()
{
	int n = obs.size();

	//for (int i = 1; i < n; i++) {
	//	obs[i]->Print();
	//}


	if (direc == RIGHT) {
		light.print(this->pos.X, this->pos.Y);
		for (int i = 1; i < n; i++) {

			const short obs_left = obs[i]->GetPosition().X;
			const short obs_right = obs[i]->GetPosition().X + obs[i]->Width() - 1;

			if (BOARD_GAME_RIGHT > obs_left && BOARD_GAME_RIGHT < obs_right) {

				obs[0]->SetPosition(BOARD_GAME_LEFT - (BOARD_GAME_RIGHT - obs_left), obs[1]->GetPosition().Y);

				for (int i = 0; i < n; i++) {
					obs[i]->Print();
				}

				return;
			}
		}

		obs[0]->SetPosition(0, 0);

		for (int i = 1; i < n; i++) {
			obs[i]->Print();
		}
	}
	else {
		light.print(this->pos.X + width - 4, this->pos.Y);
		for (int i = 1; i < n; i++) {

			const short obs_left = obs[i]->GetPosition().X;
			const short obs_right = obs[i]->GetPosition().X + obs[i]->Width() - 1;

			if (BOARD_GAME_LEFT > obs_left && BOARD_GAME_LEFT < obs_right) {

				obs[0]->SetPosition(BOARD_GAME_RIGHT - (BOARD_GAME_LEFT - obs_left), obs[1]->GetPosition().Y);

				for (int i = 0; i < n; i++) {
					obs[i]->Print();
				}

				return;
			}
		}

		obs[0]->SetPosition(0, 0);

		for (int i = 1; i < n; i++) {
			obs[i]->Print();
		}
	}
}

COORD Lane::GetPos()
{
	return pos;
}

TrafficLight& Lane::GetLight()
{
	return light;
}

bool Lane::IsImpact(People& people)
{
	int n = obs.size();			// số vật cản có trong lane
	const short people_left = people.GetPosition().X;
	const short people_right = people.GetPosition().X + people.Width() - 1;

	for (int i = 0; i < n; i++) {

		const int min_x = obs[i]->GetPosition().X;
		const int max_x = obs[i]->GetPosition().X + obs[i]->Width() - 1;

		if (people_left >= min_x && people_left <= max_x) {
			return true;
		}

		if (people_right >= min_x && people_right <= max_x) {
			return true;
		}
	}

	return false;
}
