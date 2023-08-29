#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "ak.h"
#include "task.h"
#include "message.h"
#include "timer.h"
#include "tsm.h"

#include "app.h"
#include "app_dbg.h"
#include "app_flash.h"
#include "task_list.h"
#include "task_sm.h"

#include "app_if.h"
#include "task_list_if.h"

#include "platform.h"
#include "io_cfg.h"
#include "sys_cfg.h"

#include "sys_dbg.h"


#define TAG "TaskSM"


/* Extern variables ----------------------------------------------------------*/
tsm_tbl_t slStateMachine;


/* Private function prototypes -----------------------------------------------*/
void in1(ak_msg_t* msg){
    (void)msg;
    APP_PRINT("in1\n");

    // task_post_pure_msg(AC_TASK_SM_ID, AC_SM_IN2);
}
void in2(ak_msg_t* msg){
    (void)msg;
    APP_PRINT("in2\n");
    // task_post_pure_msg(AC_TASK_SM_ID, AC_SM_IN1);
}
void in3(ak_msg_t* msg){
    (void)msg;
    APP_PRINT("in3\n");
    // task_post_pure_msg(AC_TASK_SM_ID, AC_SM_IN2);
}
void in4(ak_msg_t* msg){
    (void)msg;
    APP_PRINT("in4\n");
    // task_post_pure_msg(AC_TASK_SM_ID, AC_SM_IN2);
}
/*---------------------------------------------
 * State machine table control
 *
 ---------------------------------------------*/
static tsm_t tblSmIdling[] = {
    { AC_SM_IN1,  SL_SM_IDLE,     in1   },
    { AC_SM_IN2,  SL_SM_FIRMW,    in2   },
   
};

static tsm_t tblFirmwareUpdate[] = {
    { AC_SM_IN1,  SL_SM_FIRMW,     in3   },
    { AC_SM_IN2,  SL_SM_IDLE,      in4   },
    
};

tsm_t* slStateMachineTbl[] = {
    tblSmIdling,
    tblFirmwareUpdate,
};


/* Private variables ----------------------------------------------------------*/


/* Function implementation ---------------------------------------------------*/
void task_sm(ak_msg_t* msg) {
    tsm_dispatch(&slStateMachine, msg);
}

/*----------------------------------------------------------------------------*/
void slStateMachineOnState(tsm_state_t state) {
    (void)state;

    APP_PRINT("XXXXXX %d\n", state);

   
}

