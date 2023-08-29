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
#include "task_hello1.h"


void task_hello1(ak_msg_t* msg) {
	switch (msg->sig) {
	// case AC_HELLO1_PRINT_1:

	// 	uint8_t* inData = get_data_common_msg(msg);
	// 	int x1 = *(int *)inData;
    //     xprintf("counter2:%d\n", x1);

        
	// 	break;

	}
}