#include "common.h"
#include "point.h"
#include "StatusMenu.h"
#include "keyCurControl.h"
#include "blockControl.h"
#include "BlockInfo.h"

static int score = 0;
static int numOfClearLine = 0;

void IncScore(int combo)
{
	score += (combo * 10);

	if(combo > 1)
		score += combo * 3;
}

int GetScore(void)
{
	return score;
}

void IncClearLine(void)
{
	numOfClearLine++;
}

int GetClearLine(void)
{
	return numOfClearLine;
}

void ShowScore(void)
{
	Point CurPos = GetCurrentCursorPos();

	SetCurrentCursorPos(SCORE_BOARD_X, SCORE_BOARD_Y);
	printf("┏━━━━━━━━ \n");
	SetCurrentCursorPos(SCORE_BOARD_X, SCORE_BOARD_Y + 1);
	printf("┃ 현재 점수: %d \n", GetScore());
	SetCurrentCursorPos(SCORE_BOARD_X, SCORE_BOARD_Y + 2);
	printf("┗━━━━━━━━ \n");

	SetCurrentCursorPos(CurPos.x, CurPos.y);
}

void ShowClearLine(void)
{
	Point CurPos = GetCurrentCursorPos();

	SetCurrentCursorPos(CLEAR_LINE_X, CLEAR_LINE_Y);
	printf("┏━━━━━━━━━━━ \n");
	SetCurrentCursorPos(CLEAR_LINE_X, CLEAR_LINE_Y + 1);
	printf("┃ 클리어 라인 수: %d \n", GetClearLine());
	SetCurrentCursorPos(CLEAR_LINE_X, CLEAR_LINE_Y + 2);
	printf("┗━━━━━━━━━━━ \n");

	SetCurrentCursorPos(CurPos.x, CurPos.y);
}

void ShowNextBlock(void)
{
	Point CurPos = GetCurrentCursorPos();

	SetCurrentCursorPos(NEXT_BLOCK_X - 2, NEXT_BLOCK_Y);
	fputs("-----NEXT-----", stdout);

	SetCurrentCursorPos(NEXT_BLOCK_X, NEXT_BLOCK_Y + 1);

	Delete();
	DrawBlock(BlocksModel[GetNextBlockIdx()]);

	SetCurrentCursorPos(CurPos.x, CurPos.y);
}

void ShowStatus(void)
{
	ShowScore();
	ShowClearLine();
	ShowNextBlock();
}