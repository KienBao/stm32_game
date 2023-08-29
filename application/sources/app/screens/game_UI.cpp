#include "game_UI.h"
#include "earth.h"
#include "star.h"

using namespace std;

static void view_scr_gameUI();
static void view_scr_earth();
static void view_scr_star();

view_dynamic_t dyn_view_item_game_UI = {
	{ 
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_gameUI
};

view_dynamic_t dyn_view_earth = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_earth
};

view_dynamic_t dyn_view_star = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_star
};

view_screen_t scr_gameUI = {
	&dyn_view_item_game_UI,
	&dyn_view_earth,
	&dyn_view_star,
	.focus_item = 0,
};

void scr_gameUI_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY:{
		APP_DBG_SIG("SCREEN_ENTRY\n"); 
		timer_set(AC_STAR_ID, AC_STAR_MOVE, 150, TIMER_PERIODIC);
		timer_set(AC_TASK_DISPLAY_ID, AC_STAR_MOVE, 150, TIMER_PERIODIC);
	}
		break;
	
	case AC_STAR_MOVE:{
		APP_DBG_SIG("SCREEN_ENTRY\n"); 
		view_render_screen(&scr_gameUI);
		
	}
		break;

	default:
		break;
	}
}

void view_scr_gameUI() {

}

void view_scr_earth() {
	earth_img();
}

void view_scr_star() {
	star_img();
}