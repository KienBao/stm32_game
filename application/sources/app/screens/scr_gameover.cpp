#include "scr_gameover.h"
#include "scr_idle.h"
#include "eeprom.h"

using namespace std;

static void view_scr_gameover();

view_dynamic_t dyn_view_item_game_over = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_gameover
};

view_screen_t scr_gameover = {
	&dyn_view_item_game_over,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

int scores=0, score_last=0, k=0;
int x=0;
int x1=0;

void view_scr_gameover() {
	eeprom_read(2, (uint8_t*)&scores, sizeof(scores));
	eeprom_read(6, (uint8_t*)&score_last, sizeof(score_last));
	view_render.setCursor(	100, 19);
	view_render.println(score_last);
	if(scores>=score_last){
		score_last=scores;
	}

	view_render.setCursor(33, 3);
	view_render.print(" GAME OVER");
	view_render.setCursor(20, 19);
	view_render.print("score: ");
	view_render.setCursor(60, 19);
	view_render.println(x);
}

void scr_gameover_handle(ak_msg_t* msg) {
	switch (msg->sig)
	{
		case AC_SCORE: {
			uint8_t* inData = get_data_common_msg(msg);
			x1 = *(int *)inData;
			x=x1;
		}
			break;	

		case AC_DISPLAY_BUTON_MODE_RELEASED: {
			APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
			eeprom_write(6, (uint8_t*)&score_last, sizeof(score_last));
			SCREEN_TRAN(scr_idle_handle, &scr_idle);
		}
			break;	
		
		case AC_DISPLAY_BUTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_UP_RELEASED\n");
			
		}
			break;
	}
}