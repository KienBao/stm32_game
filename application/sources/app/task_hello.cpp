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
#include "task_hello.h"



// static int x=0;

void task_hello(ak_msg_t* msg) {
	switch (msg->sig) {
	case AC_HELLO_PRINT_1:
		// xprintf("Counter: %d\n",x);
		// task_post_common_msg(AC_TASK_HELLO1_ID, AC_HELLO1_PRINT_1, (uint8_t *)&x, sizeof(x));
		// task_post_common_msg(AC_TASK_DISPLAY_ID, AC_HELLO1_PRINT_1, (uint8_t *)&x, sizeof(x));
		// task_post_pure_msg(AC_TASK_DISPLAY_ID, AC_HELLO1_PRINT_1);
		// x=x+1;
		
		// uint8_t* inData = get_data_common_msg(msg);
		// int x2 = *(int *)inData;
		break;

	default:
		break;
	}
}