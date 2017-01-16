#include "common.h"
#include "keyCurControl.h"
#include "Point.h"
#include "blockControl.h"
#include <conio.h>

static int KeyDelay;

void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

Point GetCurrentCursorPos(void)
{
	Point curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;
	
	GetConsoleScreenBufferInfo(
		GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.x = curInfo.dwCursorPosition.X;
	curPoint.y = curInfo.dwCursorPosition.Y;

	return curPoint;
}

void RemoveCursor(void)
{
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

void KeyInput(void)
{
	int i;
	int key;

	for (i = 0; i < FRAME_PER_SECOND; i++)
	{
		if (_kbhit())
		{
			key = _getch();

			switch (key)
			{
			case LEFT:
				MoveBlockLeft();
				break;
			case RIGHT:
				MoveBlockRight();
				break;
			case UP:
				RotateBlock();
				break;
			case DOWN:
				BlockDown();
				break;
			case SPACE:
				HardDrop();
				break;

			}
		}

		if (i % KeyDelay == 0)
			Sleep(SYS_DELAY);
	}
}

void KeyDelayInit(int rate)
{
	if (rate < 1)
		return;
	else
		KeyDelay = rate;
}