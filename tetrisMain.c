#include "common.h"
#include <Windows.h>
#include <conio.h>
#include "keyCurControl.h"
#include "blockControl.h"
#include "BlockInfo.h"
#include "MapInfo.h"
#include "StatusMenu.h"

int main(void)
{
	drawMap();
	ShowStatus();

	KeyDelayInit(20);
	RemoveCursor();

	FirstSelectBlock();
	
	while (!IsGameOver())
	{
		InitNewBlockPos(START_CURPOS_X, START_CURPOS_Y);		

		while (BlockDown())
		{
			KeyInput();
		}

		AddBlockgameBoard();
		removeWid();
		ReDraw();		
		SelectBlock();
		ShowStatus();
	}

	return 0;
}