#ifndef __BLOCKS_H_
#define __BLOCKS_H_

#define START_CURPOS_X	(5 * 4 - 2)
#define START_CURPOS_Y	(2)

void InitNewBlockPos(int x, int y);

void FirstSelectBlock(void);
void SelectBlock(void);
int GetNextBlockIdx(void);
int GetCurrentBlockIdx(void);

void DrawBlock(char(*blockInfo)[4]);
void DeleteBlock(char(*blockInfo)[4]);
void Delete(void);
void ReDrawBlock(void);
int BlockDown(void);

void MoveBlockLeft(void);
void MoveBlockRight(void);
void RotateBlock(void);
void KeyInput(void);

void drawMap(void);

int CheckCollision(int curX, int curY, char blockModel[][4]);
void AddBlockgameBoard(void);
int IsGameOver(void);

int IsFull(int CurY);
void removeWid(void);
void rm(int CurY);
void ReDraw(void);
void HardDrop(void);

#endif