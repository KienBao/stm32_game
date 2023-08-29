#include "scr_ingame.h"
#include "task_sm.h"
#include "scr_gameover.h"
#include "eeprom.h"

#include <queue>

#define MAX_BULLET_DISPLAY	(16)
using namespace std;

#define NUM_CANDLE		(15)
#define LOGO_HEIGHT		(4)
#define LOGO_WIDTH		(4)

static const unsigned char PROGMEM logo_game_conca[] = { 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 
	0x06, 0x01, 0xc0, 0x00, 0x03, 0x07, 0xfc, 0x00, 0x01, 0xfc, 0x03, 0xe0, 0x01, 0xc0, 0x06, 0xe0, 
	0x01, 0xc0, 0x02, 0xc0, 0x01, 0x20, 0x00, 0x80, 0x06, 0x0f, 0x81, 0x00, 0x00, 0x03, 0xfc, 0x00, 
	0x00, 0x03, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM logo_bullet[] = {
	0x00, 0x3c, 0x7e, 0x7e, 0x7e, 0x7e, 0x3c, 0x00
};

static const unsigned char PROGMEM logo_boom[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x0f, 0x80, 
	0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x27, 0xe0, 0x00, 
	0x00, 0x1f, 0xe0, 0x00, 0x00, 0xbf, 0xf0, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x01, 0x7f, 0xf8, 0x00, 
	0x01, 0x7f, 0xf8, 0x00, 0x00, 0xff, 0xf8, 0x00, 0x00, 0xbf, 0xf0, 0x00, 0x00, 0xff, 0xf0, 0x00, 
	0x00, 0x7f, 0xe0, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM logo_coral[] = {
	0x00, 0x00, 0x04, 0x20, 0x2a, 0x30, 0x6a, 0x28, 0x2c, 0xe0, 0x29, 0x70, 0x31, 0x20, 0x7e, 0x34, 
	0x7d, 0x8e, 0x1d, 0x10, 0x3e, 0x00, 0x38, 0x00, 0x0d, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const unsigned char PROGMEM logo_coral_tal[] = {
	0x00, 0x00, 0x02, 0x00, 0x06, 0x20, 0x10, 0x60, 0x28, 0x20, 0x28, 0x70, 0x2a, 0x78, 0x6a, 0x6c, 
	0x68, 0xe8, 0x28, 0x68, 0xa8, 0x70, 0x19, 0x70, 0xb5, 0x70, 0xb7, 0x64, 0x36, 0x74, 0x7e, 0x80, 
	0x7d, 0x8e, 0x45, 0x9e, 0x5d, 0x94, 0x39, 0x00, 0x3c, 0x00, 0x1a, 0x80, 0x52, 0x20, 0x30, 0x0c, 
	0x3c, 0x0c, 0x0d, 0x1c, 0x0c, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM logo_10[] = {
	0x00, 0x07, 0xf0, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x38, 0x0e, 0x00, 
	0x00, 0x70, 0x07, 0x00, 0x00, 0x6e, 0x7b, 0x00, 0x00, 0x6e, 0xdb, 0x00, 0x00, 0x46, 0xd9, 0x80, 
	0x00, 0x46, 0xd9, 0x80, 0x00, 0x66, 0xdb, 0x00, 0x00, 0x6f, 0x7b, 0x00, 0x00, 0x70, 0x07, 0x00, 
	0x00, 0x38, 0x0e, 0x00, 0x00, 0x1c, 0x1c, 0x00, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x07, 0xf0, 0x00

};

static int y = 10;
static int b_init=0, diem=0;
static float damage_x_bullet=0, damage_y_bullet=0, dame_boom=0;
float diem_x=0,diem_y=0;
int score=0;
int non_fatal=0;

class coral{
	public:
	static int total;
	int id;
	float x=120, y=50;

	coral(){
		
	}

	void moving(){
		x-=2;
	}

	bool isOutOfScreen() {
        if (x <= -10) {
            return true;
        }
        return false;
    }
};

class boom{
	public:
	static int total;
	int id,radius;
	float x,y;
	float axis_x_t, axis_x_b, axis_y_t, axis_y_b;

	boom(){
		x=120;
		y=((rand() % 3) * 20)-10;
	}

	void moving(){
		x=x-1;
		axis_x_t=x+13;
		axis_x_b=x+3;
		
		axis_y_t=y+25;
		axis_y_b=y+5;
	}

	bool isOutOfScreen() {
        if (x <= -20) {
            return true;
        }
        return false;
    }
};

class bullet{
    public:
	static int total;
	int id;
	float x=25, z=y+12;

	float defaut_x=25, defaut_z=y+12;

	bullet(){
	
	}

	void moving(){
		x+=5;
	}

	bool isOutOfScreen() {
        if (x >= 128) {
            return true;
        }
        return false;
    }
	
};

vector<bullet> v_idle_bullet;
int bullet::total;

vector<coral> v_idle_coral;
int coral::total;

vector<boom> v_idle_boom;
int boom::total;

static void view_scr_ingame();

view_dynamic_t dyn_view_item_in_game = {
	{ 
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_ingame
};

view_screen_t scr_ingame = {
	&dyn_view_item_in_game,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_ingame() {
	view_render.setCursor(0, 0);
	view_render.print("score: ");
	view_render.setCursor(35, 0);
	view_render.println(score);

	/*CON CA*/
	view_render.drawBitmap(0,y,logo_game_conca, 32, 32, 1);
	// star_img();
	/*SAN HO*/
	for(coral _coral : v_idle_coral) {
			view_render.drawBitmap(_coral.x,_coral.y,logo_coral, 16, 16, 1);
	}
	/*BOOM*/
	for(boom _boom : v_idle_boom) {
			view_render.drawBitmap(_boom.x,_boom.y,logo_boom, 32, 32, 1);
	}
	/*DAN*/
	if(b_init==1){
		for(bullet _bullet : v_idle_bullet) {
			view_render.drawBitmap(_bullet.x,_bullet.z,logo_bullet, 8, 8, 1);
		}
	}
	/*HIEU UNG +10 DIEM*/
	if(diem==1){
		view_render.setCursor(diem_x, diem_y);
		view_render.print("+10");
		diem=0;
	}
}

void scr_ingame_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case AC_GAME_PUSH :{
		coral new_coral;
		new_coral.id = coral::total++;
		v_idle_coral.push_back(new_coral);

		boom new_boom;
		new_boom.id = boom::total++;
		v_idle_boom.push_back(new_boom);
	}
		break;

	case SCREEN_ENTRY:{
		APP_DBG_SIG("SCREEN_ENTRY\n"); 
		timer_set(AC_TASK_DISPLAY_ID, AC_GAME_PUSH , 4000, TIMER_PERIODIC); 

		timer_set(AC_TASK_DISPLAY_ID, \
				  AC_DISPLAY_GAME_MOVING_UPDATE, \
				  AC_DISPLAY_GAME_MOVING_UPDATE_INTERAL, \
				  TIMER_PERIODIC);
	}
		break;
	
	case AC_DISPLAY_GAME_MOVING_UPDATE:{
		for (unsigned int i = 0; i < v_idle_coral.size(); i++) {
			v_idle_coral[i].moving();
			if(v_idle_coral[i].isOutOfScreen()){
				v_idle_coral.erase(v_idle_coral.begin(), v_idle_coral.begin() + 1);
			}
			if(y>=v_idle_coral[i].y-10 && v_idle_coral[i].x<=20){
				v_idle_coral.clear();
				v_idle_boom.clear();
				v_idle_bullet.clear();
				y=10;
				task_post_common_msg(AC_TASK_DISPLAY_ID, AC_SCORE, (uint8_t *)&score, sizeof(score));
				eeprom_write(2, (uint8_t*)&score, sizeof(score));
				score=0;
				SCREEN_TRAN(scr_gameover_handle, &scr_gameover);
			}
		}

		/*XU LY CAC SU KIEN VA CHAM*/
		if(v_idle_boom.size()==0){
			for(unsigned int j=0; j < v_idle_bullet.size(); j++){
				v_idle_bullet[j].moving();
			}
		}
		else {
			for(unsigned int i=0; i < v_idle_boom.size(); i++){
				v_idle_boom[i].moving();
				for(unsigned int j=0; j < v_idle_bullet.size(); j++){
					v_idle_bullet[j].moving();
					diem_x = v_idle_bullet[j].x;
					diem_y = v_idle_bullet[j].z;
					
					damage_y_bullet = v_idle_bullet[j].z;
					damage_x_bullet = v_idle_bullet[j].x;
					if(damage_y_bullet <= v_idle_boom[i].axis_y_t && damage_y_bullet >= v_idle_boom[i].axis_y_b && damage_x_bullet <= v_idle_boom[i].axis_x_t && damage_x_bullet >= v_idle_boom[i].axis_x_b){
						v_idle_boom.erase(v_idle_boom.begin() + i, v_idle_boom.begin() + i + 1);
						
						diem=1;
						score=score+10;
						dame_boom=1;
						
						damage_x_bullet =0;
						damage_y_bullet =0;
					}
					if(dame_boom==1){
						non_fatal-=1;
						v_idle_bullet.erase(v_idle_bullet.begin() + j, v_idle_bullet.begin() + j + 1);
						dame_boom=0;
					}
					if(v_idle_bullet[j].isOutOfScreen()){
						non_fatal-=1;
						v_idle_bullet.erase(v_idle_bullet.begin(), v_idle_bullet.begin() + 1);
					}			
				}
				if(y <= (v_idle_boom[i].axis_y_t-10) && y >= (v_idle_boom[i].axis_y_b-5) && v_idle_boom[i].x<=15 && v_idle_boom[i].x>=0){
						v_idle_coral.clear();
						v_idle_boom.clear();
						v_idle_bullet.clear();
						y=10;
						task_post_common_msg(AC_TASK_DISPLAY_ID, AC_SCORE, (uint8_t *)&score, sizeof(score));
						score=0;
						SCREEN_TRAN(scr_gameover_handle, &scr_gameover);
					}
				if(v_idle_boom[i].isOutOfScreen()){
					v_idle_boom.erase(v_idle_boom.begin(), v_idle_boom.begin() + 1);
				}		
			}
		}

		/*CHONG FATAL*/
		if(non_fatal==15){
			v_idle_coral.clear();
			v_idle_boom.clear();
			v_idle_bullet.clear();
			non_fatal=0;
			SCREEN_TRAN(scr_idle_handle, &scr_idle);
		}
	}
		break;

	case AC_DISPLAY_BUTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
			b_init=1;
			non_fatal+=1;
			bullet new_bullet;
			new_bullet.id = bullet::total++;
			v_idle_bullet.push_back(new_bullet);
	}
		break;

	case AC_DISPLAY_BUTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_UP_RELEASED\n");
        y=y-10;
		if(y<=-10){
			y=-10;
		}
	}
		break;

	case AC_DISPLAY_BUTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_DOWN_RELEASED\n");
        y=y+10;
		if(y>=40){
			y=40;
		}
	}
		break;

	default:
		break;
	}
}
