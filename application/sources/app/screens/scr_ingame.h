#ifndef __SCR_INGAME_H__
#define __SCR_INGAME_H__

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"
#include "view_render.h"
#include "task_fish.h"

#include "buzzer.h"

#include <math.h>
#include <vector>

extern view_dynamic_t dyn_view_item_in_game;

extern view_screen_t scr_ingame;
extern void scr_ingame_handle(ak_msg_t* msg);
extern int reset;


#endif //__SCR_GAMECONCA_H__