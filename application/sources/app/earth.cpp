#include "earth.h"
#include "game_UI.h"
#include "star.h"

object _earth;
uint8_t direarth = 0;

static const unsigned char PROGMEM logo_earth[] = {
	0x0f, 0xe0, 0x3f, 0xf8, 0x66, 0xfc, 0x60, 0xfc, 0xc3, 0xfe, 0xef, 0xfe, 0xff, 0xfe, 0xff, 0xfe, 
	0xfc, 0x7e, 0xfc, 0x3e, 0xfc, 0x3e, 0x7e, 0x7c, 0x3e, 0xf8, 0x1f, 0xf0, 0x0f, 0xe0
};

void earth(ak_msg_t* msg) {
	switch (msg->sig) {
	case AC_EARTH_MOVE:
		earth_move();
		break;

	default:
		break;
	}
}

void earth_img(){
	view_render.drawBitmap(_earth.x, _earth.y, logo_earth, 15, 15, 1);
}

void earth_move(){
	switch (direarth)
	{
	case MOVEDOWN: {
		direarth = 0;
		_earth.y += 10;
	}
		break;
	
	case MOVEUP: {
		direarth = 0;
		_earth.y -= 10;
	}
		break;

	default:
		break;
	}
}