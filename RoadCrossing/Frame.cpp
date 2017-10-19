#include "Frame.h"

Frame::Frame()
{

}

Frame::Frame(short W, short H, COORD pos)
{
	width = W;
	height = H;
	pos = pos;
}

void Frame::Set(short W, short H, COORD pos)
{
	width = W;
	height = H;
	this->pos = pos;
}

//#define printf(x) printf("%c",x)
//void Frame::Draw()					//Dùng GotoXY
//{
//	GotoXY(pos.X, pos.Y);
//
//	for (int i = 0; i < height; i++)
//	{
//		if (i == 0 || i == height - 1)
//		{
//			for (int j = 0; j < width; j++)
//				if (i == 0 && j == 0) printf(201);
//				else if (i == 0 && j == width - 1) printf(187);
//				else if (i == height - 1 && j == 0) printf(200);
//				else if (i == height - 1 && j == width - 1) printf(188);
//				else printf(205);
//		}
//		else
//		{
//			GotoXY(pos.X, pos.Y + i);
//			printf(186);
//			GotoXY(pos.X + width - 1, pos.Y + i);
//			printf(186);
//		}
//	}
//}
//
//void Frame::Draw_(char **buff)	//Dùng mảng 2 chiều buffer đại diện cho toàn bộ màn hình console
//{
//	int X, Y;
//	X = pos.X;
//	Y = pos.Y;
//	for (int i = 0 + Y; i < height + Y; i++)
//	{
//		if (i == 0 + Y || i == height - 1 + Y)
//		{
//			for (int j = 0 + X; j < width + X; j++)
//				if (i == 0 + Y && j == 0 + X) buff[i][j] = 201;
//				else if (i == 0 + Y && j == width - 1 + X) buff[i][j] = 187;
//				else if (i == height - 1 + Y && j == 0 + X) buff[i][j] = 200;
//				else if (i == height - 1 + Y && j == width - 1 + X) buff[i][j] = 188;
//				else buff[i][j] = 205;
//		}
//		else
//		{
//			buff[Y + i][X] = 186;
//			buff[Y + i][X + width - 1] = 186;
//		}
//	}
//}

void Frame::Draw()
{
	//GotoXY({ BOARD_LEFT_EDGE, BOARD_TOP_EDGE });		// Góc trên bên trái
	//printf("%c", 201);
	//GotoXY({ BOARD_RIGHT_EDGE, BOARD_TOP_EDGE });		// Góc trên bên phải
	//printf("%c", 187);
	//GotoXY({ BOARD_LEFT_EDGE, BOARD_BOTTOM_EDGE });		// Góc dưới bên trái
	//printf("%c", 200);
	//GotoXY({ BOARD_RIGHT_EDGE, BOARD_BOTTOM_EDGE });	//Góc dưới bên phải
	//printf("%c", 188);

	//for (short i = BOARD_LEFT_EDGE + 1; i < BOARD_RIGHT_EDGE; i++)	// Cạnh trên
	//{
	//	//GotoXY({ i, BOARD_TOP_EDGE });
	//	printf("%c", 205);
	//}

	//for (short i = BOARD_LEFT_EDGE + 1; i < BOARD_RIGHT_EDGE; i++)	// Cạnh dưới
	//{
	//	//GotoXY({ i, BOARD_BOTTOM_EDGE });
	//	printf("%c", 205);
	//}

	//for (short i = BOARD_TOP_EDGE + 1; i < BOARD_BOTTOM_EDGE; i++)	// Cạnh trái
	//{
	//	GotoXY({ BOARD_LEFT_EDGE, i });
	//	printf("%c", 186);
	//}

	//for (short i = BOARD_TOP_EDGE + 1; i < BOARD_BOTTOM_EDGE; i++)	// Cạnh phải
	//{
	//	GotoXY({ BOARD_RIGHT_EDGE, i });
	//	printf("%c", 186);
	//}


}