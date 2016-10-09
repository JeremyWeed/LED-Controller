#include "include/soft_string.hpp"

SoftSet *soft_set;

//init method for soft_string_init
//must be called before any other method in this file
void soft_string_init(){
	soft_set = (SoftSet*)calloc(1, sizeof(SoftSet));

	SoftSet *ss = soft_set;  //so I don't have to type it each tIncrease

	ss->brightness = 200;

	ss->tChoose = 15;
	ss->tIncrease = 2;
	ss->tDecrease = 4;
	ss->tStay = 3000;

	setCol(&(ss->col), 0xFFC58F);
	randomSeed(analogRead(0));
}

void soft_light(){

	static unsigned long curIncrease, curDecrease, curChoose, curStay;
	SoftSet *ss = soft_set;
	bool bright = false, dark = false;

	//choose a new light to turn on
	if(curChoose + ss->tChoose < millis()){
		curChoose = millis();
		int i = random(LENGTH);
		ss->cur_lit[i] = true;
		ss->curStay[i] = millis();
	}

	//Should we brighten anything this loop?
	if(curIncrease + ss->tIncrease < millis()){
		curIncrease = millis();
		bright = true;
	}

	//Should we darken anything this loop?
	if(curDecrease + ss->tDecrease < millis()){
		curDecrease = millis();
		dark = true;
	}

	//increment through all of the leds and change 'em
	for(int i = 0; i < LENGTH; i++){
		//brighten
		if(bright){
			if(ss->cur_lit[i]){
				if(ss->curBright[i] < ss->brightness){
					ss->curBright[i]++;
				}else if (ss->curStay[i] + ss->tStay < millis()){
					ss->cur_lit[i] = false;

				}
			}
		}
		//darken
		if(dark){
			if(!ss->cur_lit[i]){
				if(ss->curBright[i] > 0){
					ss->curBright[i]--;
				}
			}
		}
		//set the color of each leds
		leds.setPixelColor(i,
			scale(ss->col.R, ss->curBright[i]),
			scale(ss->col.G, ss->curBright[i]),
			scale(ss->col.B, ss->curBright[i])
		);
	}
	//need to call this to make the leds show up
	leds.show();
}

void change_soft_color(Color col){
	soft_set->col = col;
}
