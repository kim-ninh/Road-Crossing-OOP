#include "Lane.h"

Lane::Lane()
{
	width = BOARD_GAME_RIGHT - BOARD_GAME_LEFT + 1;
}

Lane::Lane(COORD coord, vector<Obstacle*> v, Direction theDirec, short SleepTime, short SoundWaiting)
{
	obs = v;
	pos = coord;
	direc = theDirec;
	height = obs[0]->Height() + 1;
	width = BOARD_GAME_RIGHT - BOARD_GAME_LEFT + 1;
	sleepTime = SleepTime;
	timeCount = 0;
	soundWaiting = SoundWaiting;
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
		light.print(this->pos.X + width - 3, this->pos.Y);
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

void Lane::Tell(People &people)
{
	if (IsInside(people) == true)
	{
		if (timeCount % soundWaiting == 0)
		{
			timeCount = 0;
			obs[0]->Tell();
		}

		timeCount += sleepTime;
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

void Lane::Write(ostream& outDev)
{
	int num;
	ObstacleType type = obs[0]->GetType();

	outDev.write((char*)&type, sizeof(type));
	outDev.write((char*)&width, sizeof(width));
	outDev.write((char*)&height, sizeof(height));
	outDev.write((char*)&pos, sizeof(pos));
	num = obs.size();

	outDev.write((char*)&num, sizeof(num));
	for (int i = 0; i < num; i++) {
		obs[i]->Write(outDev);
	}

	outDev.write((char*)&light, sizeof(light));
	outDev.write((char*)&direc, sizeof(direc));
	outDev.write((char*)&sleepTime, sizeof(sleepTime));
	outDev.write((char*)&timeCount, sizeof(timeCount));
	outDev.write((char*)&soundWaiting, sizeof(soundWaiting));
}

void Lane::Read(istream& inDev)
{
	int num;
	ObstacleType type;

	inDev.read((char*)&type, sizeof(type));
	inDev.read((char*)&width, sizeof(width));
	inDev.read((char*)&height, sizeof(height));
	inDev.read((char*)&pos, sizeof(pos));
	num = obs.size();

	inDev.read((char*)&num, sizeof(num));
	obs.resize(num);

	// allocate	'num' pointer to 'num' Obstacle object
	switch (type)
	{
	case BIRD:
		for (int i = 0; i < num; i++) {
			obs[i] = new Bird();
		}
		break;
	case CAR:
		for (int i = 0; i < num; i++) {
			obs[i] = new Car();
		}
		break;
	case DINOUSAUR:
		for (int i = 0; i < num; i++) {
			obs[i] = new Dinosaur();
		}
		break;
	case TRUCK:
		for (int i = 0; i < num; i++) {
			obs[i] = new Truck();
		}
		break;
	default:
		break;
	}

	for (int i = 0; i < num; i++) {
		obs[i]->Read(inDev);
	}

	inDev.read((char*)&light, sizeof(light));
	inDev.read((char*)&direc, sizeof(direc));
	inDev.read((char*)&sleepTime, sizeof(sleepTime));
	inDev.read((char*)&timeCount, sizeof(timeCount));
	inDev.read((char*)&soundWaiting, sizeof(soundWaiting));
}

void Lane::Deallocate()
{
	if (!obs.empty()) {
		for (int i = 0; i < obs.size(); i++) {
			delete obs[i];
			obs[i] = nullptr;
		}
		obs.clear();
	}
}
bool Lane::IsInside(People & people)
{
	COORD peoplePos = people.GetPosition();
	if (pos.Y <= peoplePos.Y && peoplePos.Y < pos.Y + height)
		return true;
	return false;
}
