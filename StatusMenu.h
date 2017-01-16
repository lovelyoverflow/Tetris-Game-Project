#ifndef __SCORE_H_
#define __SCORE_H_

#define SCORE_BOARD_X	40
#define SCORE_BOARD_Y	5

#define CLEAR_LINE_X	40
#define CLEAR_LINE_Y	8

#define NEXT_BLOCK_X	45
#define NEXT_BLOCK_Y	20

void IncScore(int combo);
int GetScore(void);

void IncClearLine(void);
int GetClearLine(void);

void ShowNextBlock(void);

void ShowStatus(void);

#endif