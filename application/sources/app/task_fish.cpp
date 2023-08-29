#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h" 
#include "sys_io.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_if.h"
#include "app_dbg.h"

#include "task_list.h"
#include "task_list_if.h"
#include "view_render.h"

#include "task_fish.h"

static const unsigned char PROGMEM logo_fish[] = { 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 
	0x06, 0x01, 0xc0, 0x00, 0x03, 0x07, 0xfc, 0x00, 0x01, 0xfc, 0x03, 0xe0, 0x01, 0xc0, 0x06, 0xe0, 
	0x01, 0xc0, 0x02, 0xc0, 0x01, 0x20, 0x00, 0x80, 0x06, 0x0f, 0x81, 0x00, 0x00, 0x03, 0xfc, 0x00, 
	0x00, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

class fish{
    public:
    int x=5,y=10;

    fish(){
	view_render.drawBitmap(5,y,logo_fish, 32, 32, 1);
    view_render.update();
    }

    void move(){
        if(y<=-10){
			y=-10;
		}
        if(y>=40){
			y=40;
		}
    }
};

static int l=0;

void task_fish(ak_msg_t* msg) {
	switch (msg->sig) {
	// case AC_HELLO_PRINT_1:
	// 	task_post_common_msg(AC_TASK_HELLO1_ID, AC_HELLO1_PRINT_1, (uint8_t *)&l, sizeof(l));
	// 	l=l+1;
	// 	break;

	default:
		break;
	}
}