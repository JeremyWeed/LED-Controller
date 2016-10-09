#include "include/string_lights.hpp"

LightSet *light_set;



static void setColors(LightSet *ls){
	/* pastels
	ls->cols[0] = {.R = 0xFF, .G = 0x3F, .B = 0x3F}; //red
	ls->cols[1] = {.R = 0x3F, .G = 0xFF, .B = 0x3F}; //green
	ls->cols[2] = {.R = 0x3F, .G = 0x3F, .B = 0xFF}; //blue
	ls->cols[3] = {.R = 0x7F, .G = 0x7F, .B = 0x1F}; //yellow
	ls->cols[4] = {.R = 0x1F, .G = 0x7F, .B = 0x7F}; //cyan
	ls->cols[5] = {.R = 0x7F, .G = 0x1F, .B = 0x7F}; //purple
	*/
	//maybe christmas-y
	setCol(&ls->cols[0], 0x710f2f); //pinkish
	//setCol(&ls->cols[0], 0xF4D03F); //yellow
	setCol(&ls->cols[1], 0x006616); //green
	setCol(&ls->cols[2], 0x000099); //blue
	setCol(&ls->cols[3], 0x800000); //red
	setCol(&ls->cols[4], 0xd35400); //yellow
}

void sl_init(){
	light_set = (LightSet*)calloc(1, sizeof(LightSet));

	LightSet *ls = light_set;

	ls->in_len = 2;
	ls->de_len = 2;
	ls->ch_len = 50;

	setColors(ls);
}



void string_light_main(){
	static unsigned long in_cur = 0, de_cur = 0, ch_cur = 0;
	static bool is_lit[LENGTH] = {0};
	static int num_lit = 0;
	bool bright = false, dark = false;
	LightSet *ls = light_set;

	if(ch_cur + ls->ch_len < millis() && num_lit < LENGTH){
		int i;
		ch_cur = millis();
		while(is_lit[i = random(LENGTH)]){

		}
		is_lit[i] = true;
		ls->incre[i] = true;
		choose_color(i);
		num_lit++;
	}
	if(in_cur + ls->in_len < millis()){
		in_cur = millis();
		bright = true;
	}
	if(de_cur + ls->de_len < millis()){
		de_cur = millis();
		dark = true;
	}

	for(int i = 0; i < LENGTH; i++){
		if(is_lit[i]){
			if(bright && ls->incre[i]){
				if(ls->cur_lit[i] >= 255){
					ls->incre[i] = false;
				}else{
					ls->cur_lit[i]++;
				}
			}
			if(dark && !ls->incre[i]){
				if(ls->cur_lit[i] <= 0){
					ls->incre[i] = true;
					choose_color(i);
				}else{
					ls->cur_lit[i]--;
				}
			}
			leds.setPixelColor(i,
				scale(ls->cur_c[i].R, ls->cur_lit[i]),
				scale(ls->cur_c[i].G, ls->cur_lit[i]),
				scale(ls->cur_c[i].B, ls->cur_lit[i])
				);
	}
	}
 leds.show();
}

void choose_color(int i){
	int e = random(NUM_COLORS);
	if(
		light_set->cols[e].R == light_set->cur_c[i].R &&
		light_set->cols[e].G == light_set->cur_c[i].G &&
		light_set->cols[e].B == light_set->cur_c[i].B
		)
			return choose_color(i);
	light_set->cur_c[i] = light_set->cols[e];
}
