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
#include "task_bullet.h"


struct bullet{
    const unsigned char newbull;
    int next;
};

void task_bullet(ak_msg_t* msg) {
	switch (msg->sig) {
    
    

	default:
		break;
	}
}