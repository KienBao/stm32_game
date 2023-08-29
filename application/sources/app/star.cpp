#include "earth.h"
#include "game_UI.h"
#include "star.h"

object _star;

static const unsigned char PROGMEM logo_star[] = {
	0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x80, 0x0f, 0xe0, 0x0f, 0xe0, 0x07, 0xc0, 0x07, 0xc0, 
	0x07, 0xc0, 0x04, 0x40, 0x00, 0x00, 0x00, 0x00
};

void star(ak_msg_t* msg) {
	switch (msg->sig) {
	case AC_STAR_MOVE:
		star_move();
		break;

	default:
		break;
	}
}

void star_img(){
    _star.y = 0;
	view_render.drawBitmap(_star.x, _star.y, logo_star, 15, 12, 1);
}

void star_move(){
    _star.x -= 1;
	if(_star.x <= 0) _star.x = 128;
}
