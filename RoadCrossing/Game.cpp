#pragma once
#include "Game.h"


bool Game::IsExistFile(const char* fileName)
{
	fstream inFile(fileName);

	if (inFile)
	{
		inFile.close();
		return true;
	}

	return false;
}

void Game::PrintLevel()
{
	string s = to_string(level);
	Figure fig("Figure\\Level");

	for (int i = 0; i < s.size(); i++) {
		fig = fig + Figure((string("Figure\\") + s[i]).c_str());
	}

	SMALL_RECT rect = GetWindowSize();
	int x = (rect.Right + 1 - fig.Width()) / 2;
	int y = (rect.Bottom + 1 - fig.Height()) / 2;


	TextColor(BACKGROUND_BLACK | FOREGROUND_LIGHTCYAN);		// set màu nền + màu text

	ClearConsole();
	fig.Print(x, y, false);
	Sleep(2000);
	ClearConsole();

	// trả lại màu ban đầu
	TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
}

Game::Game()
{
	level = 1;
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
			lane.push_back(Lane(lanePos, v, direc, SLEEP_TIME, CAR_SOUND_FREQ));
			lane[lane.size() - 1].GetLight().Set(SLEEP_TIME);
			break;

		case 2:
			n = 1 + (n - 1) * 2;
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
			lane.push_back(Lane(lanePos, v, direc, SLEEP_TIME, BIRD_SOUND_FREQ));
			lane[lane.size() - 1].GetLight().Set(0);
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
			lane.push_back(Lane(lanePos, v, direc, SLEEP_TIME, TRUCK_SOUND_FREQ));
			lane[lane.size() - 1].GetLight().Set(SLEEP_TIME);
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
			lane.push_back(Lane(lanePos, v, direc, SLEEP_TIME, DINOSAUR_SOUND_FREQ));
			lane[lane.size() - 1].GetLight().Set(0);

			break;

		}

		height += lane[i].Height() + 1;				// cộng 1 là cộng thêm độ cao của dải phân cách
		v.clear();
	}

	people = People((BOARD_GAME_LEFT + BOARD_GAME_RIGHT) / 2, BOARD_GAME_BOTTOM - people.Height());
	people.SetStage(true);
}

void Game::Run()
{
	PrintPeople();
	t = thread(&Game::ThreadFunct, this);
	char ch;

	while (true) {

		if (!people.IsDead()) {
			ch = toupper(_getch());
		}
		else {
			TerminateThread(t.native_handle(), 0);
			t.join();
			return StartGame();
		}

		if (ch == 'A' || ch == 'D' || ch == 'S' || ch == 'W') {

			lock_guard<mutex> lock(theLock);
			UpdatePosPeople(ch);
			PrintPeople();

			if (IsLevelUp()) {
				LevelUp();
			}
		}
		else if (ch == 'P') {
			try
			{
				PauseGame();
			}
			catch (string s)
			{
				if (s == "MAIN MENU") {
					return StartGame();
				}
			}
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
		PrintSeparator();
		PrintObstacle();
		TellObstacle();

		if (IsImpact()) {
			people.SetStage(false);

			try
			{
				ProcessDead();
			}
			catch(string s)
			{
				if (s == "MAIN MENU");
				delete lock;
				return;
			}
		}

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
	ClearConsole();

	SetConsoleFontSize({ bigFontSizeW, bigFontSizeH }, L"Consolas");
	FixConsoleWindow(CONSOLE_MENU_WIDTH, CONSOLE_MENU_HEIGHT);
	string select;
	char ch;

	menu.Set("pause");

	while (true)
	{
		select = menu.Select();
		menu.EraseMenu();

		if (select == "CONTINUE") {
			SetConsoleFontSize({ smallFontSizeW, smallFontSizeH }, L"Lucida Console");
			FixConsoleWindow(CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT);
			DrawBoard();
			PrintPeople();
			ResumeThread(t.native_handle());
			break;
		}
		else if (select == "SAVE GAME") {
			menu.Erase();
			SaveGame();
		}
		else if (select == "LOAD GAME") {
			this->LoadGame();
			SetConsoleFontSize({ smallFontSizeW,smallFontSizeH }, L"Lucida Console");
			FixConsoleWindow(CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT);
			DrawBoard();
			PrintPeople();
			ResumeThread(t.native_handle());
			break;
		}
		else if (select == "INSTRUCTION") {
			menu.PrintHelp();

			do
			{
				ch = _getch();
			} while (ch != 13);

			ClearConsole();
		}
		else if (select == "MAIN MENU") {
			ClearConsole();
			Menu m;
			m.Set("yes_no");

			SMALL_RECT rect = GetWindowSize();
			int width = rect.Right - rect.Left + 1;
			int x = (width - strlen("Are you sure?")) / 2;
			int y = (rect.Bottom) / 3 - 5;
			GotoXY(x, y);
			printf("Are you sure?");

			string select = m.Select();

			if (select == "NO") {
				string s(strlen("Are you sure?"), ' ');
				GotoXY(x, y);
				printf("%s", s.c_str());
			}
			else {		// YES
				TerminateThread(t.native_handle(), 0);
				t.join();
				Deallocate();				// deallocate before exit

				throw string("MAIN MENU");
			}
		}
	}
}

void Game::ExitGame()
{
	ClearConsole();
	Menu m;
	m.Set("yes_no");

	SMALL_RECT rect = GetWindowSize();
	int width = rect.Right - rect.Left + 1;
	int x = (width - strlen("Are you sure?")) / 2;
	int y = (rect.Bottom) / 3 - 5;
	GotoXY(x, y);
	printf("Are you sure?");

	string select = m.Select();

	if (select == "NO") {
		string s(strlen("Are you sure?"), ' ');
		GotoXY(x, y);
		printf("%s", s.c_str());
		return;
	}

	Deallocate();				// deallocate before exit
	quick_exit(EXIT_SUCCESS);
}

void Game::StartGame()
{
	PlaySound("Sound\\TheFatRat_Unity.wav", NULL, SND_ASYNC);
	char ch;
	string select;
	menu = Menu();
	SetConsoleFontSize({ bigFontSizeW, bigFontSizeH }, L"Consolas");
	FixConsoleWindow(CONSOLE_MENU_WIDTH, CONSOLE_MENU_HEIGHT);


	while (true)
	{
		select = menu.Select();
		menu.EraseMenu();

		if (select == "NEW GAME") {
			SetConsoleFontSize({ smallFontSizeW,smallFontSizeH }, L"Lucida Console");
			FixConsoleWindow(CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT);
			PrintLevel();
			DrawBoard();
			Init();
			return Run();
		}
		else if (select == "INSTRUCTION") {
			menu.PrintHelp();

			do
			{
				ch = _getch();
			} while (ch != 13);
			ClearBoard();
		}
		else if (select == "ABOUT") {
			menu.AboutAnimation();

			do
			{
				ch = _getch();
			} while (ch != 27);
			ClearBoard();
		}
		else if (select == "LOAD GAME") {
			this->LoadGame();
			SetConsoleFontSize({ smallFontSizeW,smallFontSizeH }, L"Lucida Console");
			FixConsoleWindow(CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT);
			DrawBoard();
			return Run();
		}
		else if (select == "QUIT") {
			ExitGame();
		}
	}
}

void Game::LoadGame()
{
	char fileName[50];
	int num;
	string path = "Saved\\";		// chứa đường dẫn tới file

	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_CURSOR_INFO info;

	GetConsoleScreenBufferInfo(ConsoleHandle, &csbi);		// lấy thông tin kích thước cửa sở và buffer của console
															// ở đây chỉ quan tâm kích thước cửa sổ
	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int x = (width - strlen("Enter data's name: ")) / 2;
	int y = (csbi.srWindow.Bottom) / 3 - 5;

	while (true)
	{
		GotoXY(x, y);
		printf("Enter data's name: ");

		GotoXY(x + strlen("Enter data's name: ") / 3, y + 1);
		// hiện con trỏ trước khi nhập
		info.dwSize = 100;
		info.bVisible = TRUE;
		SetConsoleCursorInfo(ConsoleHandle, &info);

		TextColor(FOREGROUND_GREEN);
		cin.getline(fileName, 50);
		TextColor(FOREGROUND_WHITE);

		// ẩn con trỏ sau khi nhập
		info.bVisible = FALSE;
		SetConsoleCursorInfo(ConsoleHandle, &info);

		path += fileName;
		if (!IsExistFile(path.c_str())) {
			GotoXY((width - strlen("Data not found!")) / 2, y + 2);
			printf("Data not found!");
			Sleep(1000);
			string s(strlen("Data not found!"), ' ');
			GotoXY((width - strlen("Data not found!")) / 2, y + 2);
			printf("%s", s.c_str());
			s = string(strlen(fileName), ' ');
			GotoXY(x + strlen("Enter data's name: ") / 3, y + 1);
			printf("%s", s.c_str());
			path = "Saved\\";
		}
		else {
			break;
		}
	}

	ifstream inFile(path, ios::binary);

	inFile.read((char*)&num, sizeof(num));
	lane.resize(num);

	for (int i = 0; i < num; i++) {
		lane[i].Read(inFile);
	}

	people.Read(inFile);
	inFile.read((char*)&level, sizeof(level));
	menu.Read(inFile);

	inFile.close();
	ClearConsole();
}

void Game::SaveGame()
{
	char fileName[51];
	int num, width;
	Menu m;
	string path = "Saved\\";

	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_CURSOR_INFO info;

	COORD pos;
	GetConsoleScreenBufferInfo(ConsoleHandle, &csbi);		// lấy thông tin kích thước cửa sở và buffer của console
															// ở đây chỉ quan tâm kích thước cửa sổ
	width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	pos.Y = (csbi.srWindow.Bottom) / 3 - 5;
	pos.X = (width - strlen("File is already exist! Overwrite?")) / 2;

	// kiểm tra trùng file.
	while (true)
	{
		GotoXY(pos.X + strlen("File is already exist! Overwrite?") / 4, pos.Y);
		printf("Input name to save: ");
		GotoXY(pos.X + strlen("File is already exist! Overwrite?") / 3, pos.Y + 1);

		// hiện con trỏ trước khi nhập
		info.dwSize = 100;
		info.bVisible = TRUE;
		SetConsoleCursorInfo(ConsoleHandle, &info);

		TextColor(FOREGROUND_GREEN);
		cin.getline(fileName, 50);
		TextColor(FOREGROUND_WHITE);

		// ẩn con trỏ sau khi nhập
		info.bVisible = FALSE;
		SetConsoleCursorInfo(ConsoleHandle, &info);

		path += fileName;
		if (IsExistFile(path.c_str()))		// file đã tồn tại
		{
			int x = (width - strlen("File is already exist! Overwrite?")) / 2;
			GotoXY(x, pos.Y + 2);
			printf("File is already exist! Overwrite?");
			m.Set("yes_no");
			string select = m.Select();

			if (select == "YES") {
				break;
			}
			else {
				ClearConsole();
				path = "Saved\\";
			}
		}
		else
			break;
	}


	m.Erase();		// xóa menu

					// mở file và bắt đầu ghi
	ofstream outFile(path, ios::binary);
	num = lane.size();

	outFile.write((char*)&num, sizeof(num));
	for (int i = 0; i < num; i++) {
		lane[i].Write(outFile);
	}

	people.Write(outFile);
	outFile.write((char*)&level, sizeof(level));
	menu.Write(outFile);

	outFile.close();

	// thông báo đã lưu thành công
	GotoXY((width - strlen("Saved!")) / 2, pos.Y + 5);
	printf("Saved!");
	GotoXY((width - strlen("Press 'Enter' key to go back to the Main Menu"))/2, pos.Y + 6);
	printf("Press 'Enter' key to go back to the Main Menu");

	while (_getch() != 13);		// chờ nhấn Enter
	ClearConsole();
}

bool Game::IsLevelUp()
{
	short people_bot = people.GetPosition().Y + people.Height() - 1;

	return people_bot < HEIGHT_OFFSET + 1 + SIDE_WALK_HEIGHT;
}

void Game::LevelUp()
{
	ClearBoard();
	SuspendThread(t.native_handle());
	Deallocate();

	level = (level == MAX_LEVEL) ? 1 : ++level;
	Init();
	PrintLevel();
	DrawBoard();
	PrintPeople();
	ResumeThread(t.native_handle());
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

	Sleep(2000);

	ClearBoard();
	SetConsoleFontSize({ bigFontSizeW, bigFontSizeH }, L"Consolas");
	FixConsoleWindow(CONSOLE_MENU_WIDTH, CONSOLE_MENU_HEIGHT);

	menu.Set("lose");
	char ch;
	string select;

	while (true)
	{
		select = menu.Select();
		menu.EraseMenu();

		if (select == "RESTART") {

			SetConsoleFontSize({ smallFontSizeW,smallFontSizeH }, L"Lucida Console");
			FixConsoleWindow(CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT);
			menu.Erase();
			DrawBoard();

			lane.clear();
			this->Init();
			PrintPeople();
			return;
		}
		else if (select == "MAIN MENU") {
			Deallocate();

			throw string("MAIN MENU");
		}
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

				s[k] += people.GetFigure().Get()[y - people_top];			// phần ký tự đè lên separator của people

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

				s[k] += people.GetFigure().Get()[y - people_top];			// phần ký tự đè lên separator của people

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
	//string s;
	//for (int i = BOARD_LEFT_EDGE; i <= BOARD_RIGHT_EDGE; i++) {
	//	s += ' ';
	//}

	//for (int i = BOARD_TOP_EDGE; i <= BOARD_BOTTOM_EDGE; i++) {
	//	GotoXY(BOARD_LEFT_EDGE, i);
	//	printf("%s", s.c_str());
	//}

	string s(BOARD_GAME_RIGHT - BOARD_GAME_LEFT + 1, ' ');		// constructor with duplicate a character n times

	for (int i = BOARD_GAME_TOP; i <= BOARD_GAME_BOTTOM; i++) {
		GotoXY(BOARD_GAME_LEFT, i);
		printf("%s", s.c_str());
	}
}

void Game::Deallocate()
{
	if (!lane.empty()) {
		for (int i = 0; i < lane.size(); i++) {
			lane[i].Deallocate();
		}
		lane.clear();
	}
}

void Game::TellObstacle()
{
	int n = lane.size();

	for (int i = 0; i < n; i++)
		lane[i].Tell(people);
}
