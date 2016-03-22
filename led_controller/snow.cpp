#include "include/snow.h"

SnowSet *snow_set;

void s_init(){
	snow_set = (SnowSet*)calloc(1, sizeof(SnowSet));

	snow_set->max_lit = 255;

	snow_set->in_length = 3;
	snow_set->de_length = 10;
	snow_set->ch_length = 750;

	Color col = {.R = 0xFF, .G = 0xFF, .B = 0xFF};
	change_snow_color(col);
	randomSeed(analogRead(0));
}

void snow(){
	static unsigned long in_cur = 0, de_cur = 0, ch_cur = 0;
	SnowSet *ss = snow_set;

	if(ch_cur + ss->ch_length > millis()){
		ch_cur = millis();
		ss->cur_b[random(LENGTH)] = true;
	}

	//is it time to brighten?
	if(in_cur + ss->in_length > millis()){
		for(int i = 0; i < LENGTH; i++){
			//find which ones to brighten
			if(ss->cur_b[i]){
				//is it already bright enough?
				if(ss->cur_lit[i] >= ss->max_lit){
					ss->cur_b[i] = false;
				}else{
					ss->cur_lit[i]++;
					leds.setPixelColor(i, 
						scale(ss->col.R, ss->max_lit),
						scale(ss->col.G, ss->max_lit),
						scale(ss->col.B, ss->max_lit)
						);
				}
			}
		}
	}
	//time to decrease?
	if(de_cur + ss->de_length > millis()){
		for(int i = 0; i < LENGTH; i++){
			if(!ss->cur_b[i]){
				if(ss->cur_lit[i] > 0){
					ss->cur_lit[i]--;
					leds.setPixelColor(i, 
						scale(ss->col.R, ss->max_lit),
						scale(ss->col.G, ss->max_lit),
						scale(ss->col.B, ss->max_lit)
						);
				}
			}
		}
	}

}

void change_snow_color(Color col){
	snow_set->col = col;
}

static unsigned char scale(unsigned char col, unsigned char inten){
	float ratio =  inten / 0xFF.0p0;
	ratio *= col;
	return (char) ratio;
}