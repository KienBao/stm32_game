#ifndef __SCR_EARTH_H__
#define __SCR_EARTH_H__

#include <stdint.h>

#define MOVEDOWN 1
#define MOVEUP 2

typedef struct
{
    int x;
    int y; 
}object;

extern object _earth;
extern uint8_t direarth;

extern void earth_move();
extern void earth_img(void);

#endif //__SCR_EARTH_H__
