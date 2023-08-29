#ifndef __SCR_GAMEOVER_H__
#define __SCR_GAMEOVER_H__

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

extern view_dynamic_t dyn_view_item_game_over;

extern view_screen_t scr_gameover;
extern void scr_gameover_handle(ak_msg_t* msg);

#endif //__SCR_GAMEOVER_H__