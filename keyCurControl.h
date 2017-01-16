#ifndef __CURSOR_H_

#define __CURSOR_H_

#include "Point.h"
#define FRAME_PER_SECOND		60
#define SYS_DELAY				60

#define	LEFT	75
#define RIGHT	77
#define UP		72
#define	DOWN	80
#define SPACE	32

void SetCurrentCursorPos(int x, int y);
Point GetCurrentCursorPos(void);
void RemoveCursor(void);

void KeyInput(void);
void KeyDelayInit(int rate);

#endif