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

void Game::PrintMessage(string type)
{
	Figure fig;
	if (type == "lose") {
		fig = Figure("Figure\\YOULOSE");
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

vector<string> Game::GetFileName(const char * path)
{
	vector<string> v;
	experimental::filesystem::path p(path);

	for (auto i = directory_iterator(p); i != directory_iterator(); i++)
	{
		if (!is_directory(i->path())) // eliminate directories in a list
			v.push_back(i->path().filename().string());
	}

	return v;
}

Game::Game()
{
	level = 1;
}

void Game::DrawGame()
{
	int n = lane.size();

	//for (int i = 0; i < n; i++) {
	//	lane[i].Print();
	//}

	for_each(lane.begin(), lane.end(), mem_fn(&Lane::Print));

	people.Print();
}

Game::~Game()
{
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
			for (int j = 1; j < n; j++) {
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
			break;

		case 2:
			n = 1 + (n - 1) * 2;
			v.push_back(new Bird(0, 0, direc));

			for (int j = 1; j < n; j++) {
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
			break;

		case 3:
			v.push_back(new Truck(0, 0, direc));

			for (int j = 1; j < n; j++) {
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
			break;

		case 4:
			v.push_back(new Dinosaur(0, 0, direc));

			for (int j = 1; j < n; j++) {
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

			break;

		}

		height += lane[i].Height() + 1;				// cộng 1 là cộng thêm độ cao của dải phân cách
		v.clear();
	}

	people = People((BOARD_GAME_LEFT + BOARD_GAME_RIGHT) / 2, BOARD_GAME_BOTTOM - people.Height());
	people.SetStage(true);
	busy = false;
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
			while (busy == true);
			TerminateThread(t.native_handle(), 0);
			t.join();
			ClearConsole();
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
			while (busy == true);

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

		ch = ' ';
	}
}

void Game::ThreadFunct()
{
	while (true) {

		UpdatePosObstacle();
		busy = true;

		lock_guard<mutex> *lock = new lock_guard<mutex>(theLock);
		PrintSeparator();
		PrintObstacle();
		TellObstacle();
		delete lock;

		if (IsImpact()) {
			people.SetStage(false);

			try
			{
				ProcessDead();
			}
			catch (string s)
			{
				if (s == "MAIN MENU");
				busy = false;
				return;
			}
		}
		busy = false;

		Sleep(SLEEP_TIME);
	}
}

void Game::ResetGame()
{
	Deallocate();
	this->Init();
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

	PlaySound("Sound\\sfx_sounds_pause4_in.wav", NULL, SND_ASYNC);
	menu.Set("pause");
	
	while (true)
	{
		select = menu.Select();
		menu.EraseMenu();

		if (select == "CONTINUE") {
			ResumeGame();
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
	ClearConsole();

	while (true)
	{
		select = menu.Select();
		menu.EraseMenu();

		if (select == "NEW GAME") {
			SetConsoleFontSize({ smallFontSizeW,smallFontSizeH }, L"Lucida Console");
			FixConsoleWindow(CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT);
			level = 1;
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
			ClearConsole();
		}
		else if (select == "ABOUT") {
			menu.AboutAnimation();
			ClearConsole();
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

/**
 * Phương thức load dữ liệu cho game.\n
 * 
 * Đọc thông tin từ file theo mode nhị phân.\n
 * 
 * Lúc bắt đầu, phương thức sẽ đọc thông tin thư mục lưu game, lấy tất cả tên file save có trong thư mục.
 * Sau đó, với mỗi tên file, phương thức sẽ đọc thông tin level của file save đó (đọc 4 byte đầu) rồi hiển thị
 * tất cả tên data save + level tương ứng ra console, người chơi chỉ việc chọn 1 trong số những data đó,
 * tránh được trường hợp người chơi không nhớ tên data.\n
 * 
 * Sau khi người chơi chọn data, phương thức sẽ đọc thông tin từ file lưu đó theo cấu trúc lúc lưu file.
 * (các thông tin cân đọc chính là thuộc tính của lớp Game).
 * Đối với những lớp thuộc tính mà dữ liệu có chứa con trỏ, do không thể đọc trực tiếp được nên
 * phải cài đặt thêm phương thức đọc ở các lớp của thuộc tính đó.\n
 */

void Game::LoadGame()
{
	char fileName[50];
	int num;
	string path = "Saved\\";		// chứa đường dẫn tới file
	vector<string> v = GetFileName("Saved");
	vector<int> lvl;
	vector<tm> time_info;
	ifstream is;

	if (!v.empty()) {
		lvl.resize(v.size());
		time_info.resize(v.size());

		for (int i = 0; i < v.size(); i++) {
			is.open((path + v[i]).c_str(), ios::binary);
			is.read((char*)&lvl[i], sizeof(int));
			is.read((char*)&time_info[i], sizeof(tm));
			is.close();
		}
	}

	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	CONSOLE_CURSOR_INFO info;

	GetConsoleScreenBufferInfo(ConsoleHandle, &csbi);		// lấy thông tin kích thước cửa sở và buffer của console
															// ở đây chỉ quan tâm kích thước cửa sổ
	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	/*int x = (width - strlen("Choose data")) / 2 - 5;*/
	int x = (width - strlen("Choose data")) / 2 - 15;
	int y = (csbi.srWindow.Bottom) / 3 - 5;


	GotoXY(x + 16, y - 1);
	TextColor(BACKGROUND_BLACK | FOREGROUND_YELLOW);
	printf("LOAD GAME");
	TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
	GotoXY(x + 15, y);
	printf("Choose data");

	GotoXY(x, y + 4);
	TextColor(BACKGROUND_BLACK | FOREGROUND_CYAN);
	printf("%-20s %-10s %-20s", "Name", "Level", "Date");
	TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
	if (!v.empty()) {
		for (int i = 0; i < v.size(); i++) {
			GotoXY(x, y + 6 + i);
			printf("%-20s %-10d %d/%d/%d %d:%d:%d", v[i].c_str(), lvl[i],
				time_info[i].tm_mday, time_info[i].tm_mon + 1, time_info[i].tm_year + 1900,
				time_info[i].tm_hour, time_info[i].tm_min, time_info[i].tm_sec);
		}
	}
	int x_sel = x - 2;
	int y_sel = y + 6;

	TextColor(BACKGROUND_BLACK | FOREGROUND_LIGHTCYAN);
	GotoXY(x_sel, y_sel);
	printf("%c", 175);
	string select;

	while (true) {
		const char ch = toupper(_getch());
		if (ch == 'W') {
			if (y_sel > y + 6) {
				GotoXY(x_sel, y_sel);
				printf(" ");
				y_sel--;
				PlaySound("Sound\\sfx_menu_move4.wav", NULL, SND_ASYNC);
			}
		}
		else if (ch == 'S') {
			if (y_sel < y + 6 + v.size() - 1) {
				GotoXY(x_sel, y_sel);
				printf(" ");
				y_sel++;
				PlaySound("Sound\\sfx_menu_move4.wav", NULL, SND_ASYNC);
			}
		}
		else if (ch == 13) {
			path += v[y_sel - y - 6];
			TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
			break;
		}
	
		GotoXY(x_sel, y_sel);
		printf("%c", 175);
	}

	tm tm1;
	ifstream inFile(path, ios::binary);

	inFile.read((char*)&level, sizeof(level));
	inFile.read((char*)&tm1, sizeof(tm));
	inFile.read((char*)&num, sizeof(num));
	lane.resize(num);

	for (int i = 0; i < num; i++) {
		lane[i].Read(inFile);
	}

	people.Read(inFile);
	menu.Read(inFile);
	inFile.read((char*)&busy, sizeof(busy));

	inFile.close();
	ClearConsole();
}

/**
 * Phương thức lưu dữ liện của game hiện tại vào file.\n
 * 
 * Ghi theo mode nhị phân (để dễ dàng và người chơi không thể tự ý
 * thay đổi được thông tin của file save).\n
 * 
 * Game sẽ yêu cầu người chơi nhập tên để lưu, sau đó game tiến hành kiểm tra tên vừa nhập
 * đã có tồn tại từ trước hay chưa, nếu chưa thì bắt đầu mở file và ghi, nếu đã tồn tại, game sẽ hỏi
 * người chơi muốn ghi đè (xóa file cũ) không, nếu đồng ý ghi đè thì tiến hành mở file và ghi thông tin,
 * nếu không thì người chơi sẽ nhập tên khác.\n
 * 
 * Các thông tin được ghi vào file là các thuộc tính của đối tượng game hiện tại
 * được ghi theo thứ tự từ trên xuống.\n
 * 
 * Riêng thuộc tính level được ưu tiên ghi đầu tiên để khi load game, có thể
 * dễ dàng lấy được thông tin level của file save (chỉ cần đọc 4 byte đầu)
 * sau đó hiện thị ra để người chơi dễ phân biệt và lựa chọn.\n
 *		
 * Các thuộc tính mà dữ liệu của nó có chứa con trỏ vì không ghi trực tiếp được
 * nên sẽ được đĩnh nghĩa phương thức ghi cụ thể và được gọi trong phương thức SaveGame().\n
 */
void Game::SaveGame()
{

	char fileName[51];
	Menu m;
	string path = "Saved\\";		// chứa đường dẫn tới file

	// lấy thông số hiện tại của console (chiều rộng, cao của cửa sổ), nhằm canh lề cho các đoạn text sắp được in ra
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;

	SMALL_RECT rect = GetWindowSize();
	int width = rect.Right - rect.Left + 1;
	COORD pos;
	pos.Y = (rect.Bottom) / 3 - 4;
	pos.X = (width - strlen("File already exists! Overwrite?")) / 2;

	// kiểm tra trùng file.
	while (true)
	{
		GotoXY((width - strlen("Save Game")) / 2, pos.Y - 2);
		TextColor(BACKGROUND_BLACK | FOREGROUND_YELLOW);
		printf("Save Game");
		TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);
		GotoXY(pos.X + strlen("File already exists! Overwrite?") / 4, pos.Y);
		printf("Input name to save: ");
		GotoXY(pos.X + strlen("File already exists! Overwrite?") / 3, pos.Y + 1);

		// hiện con trỏ trước khi nhập
		info.dwSize = 100;
		info.bVisible = TRUE;					
		SetConsoleCursorInfo(ConsoleHandle, &info);

		TextColor(BACKGROUND_BLACK | FOREGROUND_GREEN);
		cin.getline(fileName, 50);
		TextColor(BACKGROUND_BLACK | FOREGROUND_WHITE);

		// ẩn con trỏ sau khi nhập
		info.bVisible = FALSE;
		SetConsoleCursorInfo(ConsoleHandle, &info);	

		path += fileName;
		if (IsExistFile(path.c_str()))		// file đã tồn tại
		{
			int x = (width - strlen("File already exists! Overwrite?")) / 2;
			GotoXY(x, pos.Y + 2);
			printf("File already exists! Overwrite?");
			m.Set("yes_no");
			string select = m.Select();

			if (select == "YES") {
				m.Erase();
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

	time_t current_time;
	time(&current_time);
	tm * time_info = localtime(&current_time);

	// mở file và bắt đầu ghi
	ofstream outFile(path, ios::binary);

	outFile.write((char*)&level, sizeof(level));
	outFile.write((char*)time_info, sizeof(tm));

	int num = lane.size();
	outFile.write((char*)&num, sizeof(num));
	for (int i = 0; i < num; i++) {
		lane[i].Write(outFile);
	}

	people.Write(outFile);
	menu.Write(outFile);
	outFile.write((char*)&busy, sizeof(busy));

	outFile.close();

	// thông báo đã lưu thành công
	GotoXY((width - strlen("Saved!")) / 2, pos.Y + 6);
	printf("Saved!");
	GotoXY((width - strlen("Press 'Enter' key to go back to the Main Menu"))/2, pos.Y + 7);
	printf("Press 'Enter' key to go back to the Main Menu");
	
	while (_getch() != 13);		// chờ nhấn Enter
	ClearConsole();
}

bool Game::IsLevelUp()
{
	const short people_bot = people.GetPosition().Y + people.Height() - 1;

	return people_bot < HEIGHT_OFFSET + 1 + SIDE_WALK_HEIGHT;
}

void Game::LevelUp()
{
	ClearConsole();
	SuspendThread(t.native_handle());
	Deallocate();
	
	level = (level == MAX_LEVEL) ? 1 : ++level;
	Init();
	PrintLevel();
	DrawBoard();
	PrintPeople();
	ResumeThread(t.native_handle());
}

/**
 * Phương thức tiếp tục game khi đang tạm dừng.\n
 * 
 * Các thao tác cài đặt: phát âm thanh, điều chỉnh lại font chữ của console,
 * thay đổi kích thước cửa sổ của console, vẽ lại game và resume lại thread.
 */
void Game::ResumeGame()
{
	PlaySound("Sound\\sfx_sounds_pause4_out.wav", NULL, SND_ASYNC);
	SetConsoleFontSize({ smallFontSizeW, smallFontSizeH }, L"Lucida Console");
	FixConsoleWindow(CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT);
	DrawBoard();
	PrintPeople();
	ResumeThread(t.native_handle());
}

void Game::UpdatePosPeople(const char MOVING)
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
	lock_guard<mutex> lock(theLock);

	PlaySound("Sound\\sfx_deathscream_human4.wav", NULL, SND_ASYNC);

	Sleep(2000);
	PrintMessage("lose");

	ClearConsole();
	SetConsoleFontSize({ bigFontSizeW, bigFontSizeH }, L"Consolas");
	FixConsoleWindow(CONSOLE_MENU_WIDTH, CONSOLE_MENU_HEIGHT);

	menu.Set("lose");
	char ch;

	while (true)
	{
		const string select = menu.Select();
		menu.EraseMenu();

		if (select == "RESTART") {

			SetConsoleFontSize({ smallFontSizeW,smallFontSizeH }, L"Lucida Console");
			FixConsoleWindow(CONSOLE_MAX_WIDTH, CONSOLE_MAX_HEIGHT);
			menu.Erase();
			level = 1;
			ResetGame();
			DrawBoard();
			PrintPeople();
			return;
		}
		
		if (select == "MAIN MENU") {
			Deallocate();
			ClearConsole();
			throw string("MAIN MENU");
		}
	}
}

void Game::PrintObstacle()
{
	//int n = lane.size();

	//for (int i = 0; i < n; i++) {
	//	lane[i].Print();
	//}

	for_each(lane.begin(), lane.end(), mem_fn(&Lane::Print));		// chuyển thành functor để tăng hiệu suất
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
	
	//for (int i = 0; i < n; i++)
	//	lane[i].Tell(people);

	// chuyển thành functor để tăng hiệu suất
	for_each(lane.begin(), lane.end(), bind(mem_fn(&Lane::Tell), std::placeholders::_1, people));
}