#include "include/snow.hpp"
//LOOK INTO FASTLED
SnowSet *snow_set;

//init method for snow
//must be called before any method in this file
void s_init(){
	snow_set = (SnowSet*)calloc(1, sizeof(SnowSet));

	snow_set->max_lit = 255;

	snow_set->in_length = 1;
	snow_set->de_length = 20;
	snow_set->ch_length = 50;

	Color col = {.R = 255, .G = 255, .B = 255};
	change_snow_color(col);
	randomSeed(analogRead(0));
}

//main loop method for snow
//call this in loop to use this setup
void snow(){
	static unsigned long in_cur = 0, de_cur = 0, ch_cur = 0;
	SnowSet *ss = snow_set;
	bool bright = false, dark = false;

	if(ch_cur + ss->ch_length < millis()){
		ch_cur = millis();
		ss->cur_b[random(LENGTH)] = true;
	}

	//is it time to brighten?
	if(in_cur + ss->in_length < millis()){
		in_cur = millis();
		bright = true;
	}
	if(de_cur + ss->de_length < millis()){
		de_cur = millis();
		dark = true;
	}

	for(int i = 0; i < LENGTH; i++){
		//find which ones to brighten
		if(bright){
			if(ss->cur_b[i]){
			//is it already bright enough?
				if(ss->cur_lit[i] >= ss->max_lit){
					ss->cur_b[i] = false;
				}else{
					ss->cur_lit[i]++;
				}
			}
		}
		if(dark){
			if(!ss->cur_b[i]){
				if(ss->cur_lit[i] > 0){
					ss->cur_lit[i]--;
				}
			}
		}
		leds.setPixelColor(i,
			scale(ss->col.R, ss->cur_lit[i]),
			scale(ss->col.G, ss->cur_lit[i]),
			scale(ss->col.B, ss->cur_lit[i])
			);
	}

	leds.show();

}

void change_snow_color(Color col){
	snow_set->col = col;
}
