#ifndef __ARDUINO_H__
#define __ARDUINO_H__

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "sys_ctrl.h"
#include "sys_io.h"
#include "message.h"
#include "sys_cfg.h"

#define ARDUINO 100

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

#define PI 3.1415926535897932384626433832795
#define HALF_PI 1.5707963267948966192313216916398
#define TWO_PI 6.283185307179586476925286766559
#define DEG_TO_RAD 0.017453292519943295769236907684886
#define RAD_TO_DEG 57.295779513082320876798154814105
#define EULER 2.718281828459045235360287471352

#define SERIAL  0x0
#define DISPLAY 0x1

#define LSBFIRST 0
#define MSBFIRST 1

#define CHANGE 1
#define FALLING 2
#define RISING 3

#define 	_BV(bit)   (1 << (bit))

#ifndef cbi
#define cbi(sfr, bit) (sfr &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (sfr |= _BV(bit))
#endif

#define delayMicroseconds   sys_ctrl_delay_us
#define delay               sys_ctrl_delay_ms
#define micros              sys_ctrl_micros
#define millis              sys_ctrl_millis

// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif

//#define min(a,b) ((a)<(b)?(a):(b))
//#define max(a,b) ((a)>(b)?(a):(b))
//#define abs(x) ((x)>0?(x):-(x))
//#define round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))
//#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
//#define radians(deg) ((deg)*DEG_TO_RAD)
//#define degrees(rad) ((rad)*RAD_TO_DEG)
//#define sq(x) ((x)*(x))

typedef unsigned int word;

#define bit(b) (1UL << (b))

typedef bool boolean;
typedef uint8_t byte;

extern uint16_t makeWord(uint16_t w);
extern uint16_t makeWord(byte h, byte l);

#define word(...) makeWord(__VA_ARGS__)

// WMath prototypes
extern long random(long);
extern long random(long, long);
extern void randomSeed(unsigned long);
extern long map(long, long, long, long, long);

extern void pinMode(uint8_t, uint8_t);
extern void digitalWrite(uint8_t, uint8_t);
extern int digitalRead(uint8_t);

extern uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder);
extern void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val);

extern "C" { void yield(void); }

#endif // __ARDUINO_H__
