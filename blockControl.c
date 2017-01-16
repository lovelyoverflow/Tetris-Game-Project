#include "common.h"
#include <time.h>
#include "blockControl.h"
#include "keyCurControl.h"
#include "BlockInfo.h"
#include "Point.h"
#include "MapInfo.h"
#include "StatusMenu.h"

#define MAP_POS_X	8
#define MAP_POS_Y	5

static int currentBlockModel;
static int nextBlockModel;
static int curPosX, curPosY;
static char gameBoardInfo[GBOARD_HIEGHT + 1][GBOARD_WIDTH + 2] = { 0, };

void InitNewBlockPos(int x, int y)
{
	if (x < 0 || y < 0)
		return;

	curPosX = x;
	curPosY = y;

	SetCurrentCursorPos(curPosX, curPosY);
}

void FirstSelectBlock(void)
{
	srand((size_t)time(NULL));
	currentBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4;
}

void SelectBlock(void)
{
	srand((size_t)time(NULL));
	nextBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4;
}

int GetCurrentBlockIdx(void)
{
	return currentBlockModel;
}

int GetNextBlockIdx(void)
{
	return nextBlockModel;
}

void DrawBlock(char(*blockInfo)[4])
{	
	Point curPos = GetCurrentCursorPos();

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			SetCurrentCursorPos(curPos.x + (x * 2),curPos.y + y);				

			if (blockInfo[y][x] == 1)
			{
				fputs("¡á", stdout);
			}
		}
	}

	SetCurrentCursorPos(curPos.x, curPos.y);
}

void DeleteBlock(char(*blockInfo)[4])
{
	Point curPos = GetCurrentCursorPos();

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			SetCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);		

			if (blockInfo[y][x] == 1)
			{
				fputs("  ", stdout);
			}
		}
	}

	SetCurrentCursorPos(curPos.x, curPos.y);
}

void Delete(void)
{
	Point curPos = GetCurrentCursorPos();

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			SetCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);
			fputs("  ", stdout);
		}
	}

	SetCurrentCursorPos(curPos.x, curPos.y);
}

int CheckCollision(int curX, int curY, char blockModel[][4])
{
	int IdxX, IdxY;

	IdxX = (curX - MAP_POS_X) / 2;
	IdxY = curY - MAP_POS_Y ;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (blockModel[y][x] == 1 && gameBoardInfo[IdxY + y][IdxX + x] == 1)
				return 1;
		}
	}

	return 0;
}

void ReDrawBlock(void)
{
	DeleteBlock(BlocksModel[GetCurrentBlockIdx()]);
	DrawBlock(BlocksModel[GetCurrentBlockIdx()]);
}

int BlockDown(void)
{
	if (CheckCollision(curPosX, curPosY + 1, (BlocksModel[GetCurrentBlockIdx()])))
		return 0;

	DeleteBlock(BlocksModel[GetCurrentBlockIdx()]);
	curPosY++;

	SetCurrentCursorPos(curPosX, curPosY);
	DrawBlock(BlocksModel[GetCurrentBlockIdx()]);

	return 1;
}

void MoveBlockLeft(void)
{
	if (CheckCollision(curPosX - 2, curPosY, (BlocksModel[GetCurrentBlockIdx()])))
		return;

	DeleteBlock(BlocksModel[GetCurrentBlockIdx()]);

	curPosX -= 2;
	SetCurrentCursorPos(curPosX, curPosY);

	DrawBlock(BlocksModel[GetCurrentBlockIdx()]);
}

void MoveBlockRight(void)
{
	if (CheckCollision(curPosX + 2, curPosY, (BlocksModel[GetCurrentBlockIdx()])))
		return;

	DeleteBlock(BlocksModel[GetCurrentBlockIdx()]);
	
	curPosX += 2;
	SetCurrentCursorPos(curPosX, curPosY);

	DrawBlock(BlocksModel[GetCurrentBlockIdx()]);
}

void RotateBlock(void)
{	
	int BeforeModel = GetCurrentBlockIdx();

	DeleteBlock(BlocksModel[GetCurrentBlockIdx()]);

	currentBlockModel++;

	if (GetCurrentBlockIdx() % 4 == 0)
		currentBlockModel -= 4;

	if (CheckCollision(curPosX, curPosY, BlocksModel[GetCurrentBlockIdx()]))
	{
		currentBlockModel = BeforeModel;
		return;
	}

	DrawBlock(BlocksModel[GetCurrentBlockIdx()]);
}

void drawMap(void)
{
	Point curPos = GetCurrentCursorPos();

	for (int y = 0; y < GBOARD_HIEGHT + 1; y++)
	{
		for (int x = 0; x < GBOARD_WIDTH + 2; x++)
		{
			SetCurrentCursorPos(curPos.x + MAP_POS_X + (x * 2), curPos.y + (y + MAP_POS_Y));

			if (y != GBOARD_HIEGHT && (x == 0 || x == GBOARD_WIDTH + 1))
			{
				printf("¦­");
			}

			if (y == GBOARD_HIEGHT)
			{
				if (x == 0)
				{
					printf("¦±");
				}
				else if (x == GBOARD_WIDTH + 1)
				{
					printf("¦°");
				}
				else
				{
					printf("¦¬");
				}
			}
		}
	}

	for (int y = 0; y<GBOARD_HIEGHT + 1; y++)
	{
		gameBoardInfo[y][0] = 1;
		gameBoardInfo[y][GBOARD_WIDTH + 1] = 1;
	}

	for (int x = 0; x<GBOARD_WIDTH + 2; x++)
	{
		gameBoardInfo[GBOARD_HIEGHT][x] = 1;
	}
}

void AddBlockgameBoard(void)
{
	Point curPos = GetCurrentCursorPos();
	char(*Block)[4];
	int IdxX;
	int IdxY;

	Block = BlocksModel[GetCurrentBlockIdx()];
	IdxX = (curPos.x - MAP_POS_X) / 2;
	IdxY = curPos.y - MAP_POS_Y;

	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (Block[y][x] == 1)
				gameBoardInfo[IdxY + y][IdxX + x] = 1;
		}
	}
}

int IsGameOver(void)
{
	if (CheckCollision(START_CURPOS_X, START_CURPOS_Y, BlocksModel[GetCurrentBlockIdx()]))
		return 1;

	return 0;
}

int IsFull(int CurY)
{
	for (int x = 1; x < GBOARD_WIDTH + 1; x++)
	{
		if (gameBoardInfo[CurY][x] == 0)
			return 0;
	}

	return 1;
}

void rm(int CurY)
{
	Point CurPos = GetCurrentCursorPos();

	for (int x = 1; x < GBOARD_WIDTH + 1; x++)
	{
		SetCurrentCursorPos(x * 2 + MAP_POS_X, CurY + MAP_POS_Y);
		gameBoardInfo[CurY][x] = 0;
		fputs("  ", stdout);
	}

	SetCurrentCursorPos(CurPos.x, CurPos.y);
}

void DrawDown(int CurY)
{
	for (int y = 0; y < CurY - 1; y++)
	{
		for (int x = 1; x < GBOARD_WIDTH + 1; x++)
		{
			gameBoardInfo[CurY - y][x] = gameBoardInfo[CurY - y - 1][x];
			gameBoardInfo[CurY - y - 1][x] = 0;
		}
	}
}

void ReDraw(void)
{
	Point CurPos = GetCurrentCursorPos();

	for (int y = 0; y < GBOARD_HIEGHT; y++)
	{
		for (int x = 1; x < GBOARD_WIDTH + 1; x++)
		{
			if (gameBoardInfo[y][x] == 0)
			{
				SetCurrentCursorPos(x * 2 + MAP_POS_X, y + MAP_POS_Y);
				fputs("  ", stdout);
			}
			else
			{
				SetCurrentCursorPos(x * 2 + MAP_POS_X, y + MAP_POS_Y);
				fputs("¡á", stdout);
			}
		}
	}

	SetCurrentCursorPos(CurPos.x, CurPos.y);
}

void removeWid(void)
{
	int combo = 0;

	for (int y = 0; y < GBOARD_HIEGHT; y++)
	{
		for (int x = 1; x < GBOARD_WIDTH + 1; x++)
		{
			if (IsFull(y))
			{
				rm(y);
				combo++;
				IncClearLine();
				DrawDown(y);
			}
		}
	}	

	currentBlockModel = nextBlockModel;
	IncScore(combo);
}

void HardDrop(void)
{
	while (!CheckCollision(curPosX, curPosY + 1, BlocksModel[GetCurrentBlockIdx()]))
		BlockDown();

	AddBlockgameBoard();
}