#ifndef __SCR_NEWGAME_H__
#define __SCR_NEWGAME_H__

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

extern view_dynamic_t dyn_view_item_game_UI;

extern view_screen_t scr_gameUI;

extern void scr_gameUI_handle(ak_msg_t* msg); 

#endif //__SCR_GAMECONCA_H__