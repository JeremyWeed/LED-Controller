//This is the cpp file that implements all of the functions declared in the fire.h 
//header file. 
//Written by Jeremy Weed

#include "include/fire.h"

#define FIRE_NODES 5

FireSet *fire_set;

void f_init(){
	fire_set = (FireSet*)calloc(1, sizeof(FireSet));
	FireSet *fs = fire_set;

	fire_str_init(fs);
	randomSeed(analogRead(0));
}

static void fire_str_init(FireSet *fs){
	fs->max_br = 255;
	fs->targ_br = 128;

	//this is a default orangish color
	Color col = {.R = 0xFF, .G = 0x40, .B = 0x00};
	change_fire_color(col); 
	fs->mode = 0;
	fs->variance = 3;
	fs->steps = 12800;


	fs->startup_length = 50;
	fs->loop_length = 10;

	for(int i = 0; i < LENGTH; i++){
		fs->cur_color_inten[i] = fs->col.G;
	}
}

void burn(){
	static unsigned long last_loop = 0;
	last_loop = millis();
	switch(fire_set->mode){
		
		case 0:
			fadeIn();
			if(fire_set->cur_br[0] >= fire_set->targ_br){
				fire_set->mode = 1;
			}
			break;
		case 1:
			compositeColorScale();
			break;
		default:
			break;

	}
	if(last_loop + fire_set->startup_length > millis()){
				delay(last_loop - millis() + fire_set->startup_length);
			}
	leds.show();
}

//changes the default color 
void change_fire_color(Color col){
	FireSet *fs = fire_set;

	fs->col = col;

	fs->c_scale[0] = scaleFactor(fs->col.R, fs->max_br);
	fs->c_scale[1] = scaleFactor(fs->col.G, fs->max_br);
	fs->c_scale[2] = scaleFactor(fs->col.B, fs->max_br);
}

void fadeIn(){
	for(int i = 0; i < LENGTH; i++){
		leds.setPixelColor(i,
			scale(fire_set->cur_br[i], fire_set->c_scale[0]),
			scale(fire_set->cur_br[i], fire_set->c_scale[1]),
			scale(fire_set->cur_br[i], fire_set->c_scale[2])
			);
		if(fire_set->cur_br[i] < fire_set->targ_br){
			fire_set->cur_br[i]++;
		}
	}
	
}

//scales all colors
void fullColorScale(){
	for(int i = 0; i < LENGTH; i++){
		fire_set->cur_br[i] = calcNextValue(fire_set->cur_br[i], fire_set->targ_br);
		leds.setPixelColor(i, 
			scale(fire_set->cur_br[i], fire_set->c_scale[0]),
			scale(fire_set->cur_br[i], fire_set->c_scale[1]),
			scale(fire_set->cur_br[i], fire_set->c_scale[2])
			);
	}
}
//only scales green
void greenColorScale(){
	for(int i = 0; i < LENGTH; i++){
		fire_set->cur_br[i] = calcNextValue(fire_set->cur_br[i], fire_set->targ_br);
		leds.setPixelColor(i,
			fire_set->col.R,
			scale(fire_set->cur_br[i], fire_set->c_scale[1]),
			fire_set->col.B
			);
	}
}
//composite green/all scale
void compositeColorScale(){

	for(int i = 0; i < LENGTH; i++){
		
		fire_set->cur_br[i] = calcNextValue(fire_set->cur_br[i], 
			fire_set->targ_br);
		fire_set->cur_color_inten[i] = calcNextValue(fire_set->cur_color_inten[i], 
			fire_set->targ_br);
		fire_set->cur_color_inten[i] = clamp_t(fire_set->cur_color_inten[i], fire_set->col.G, 0x15);
		leds.setPixelColor(i,
			scale(fire_set->cur_br[i], fire_set->c_scale[0]),
			scale(fire_set->cur_br[i], scaleFactor(fire_set->cur_color_inten[i], fire_set->max_br)),
			scale(fire_set->cur_br[i], fire_set->c_scale[2])
			);
	}
}
//should look a bit more like a fire
//basically, it does everything compositeColorScale does,
//but includes FIRE_NODES number of points, distributed
//evenly across the strip. The values given by the
//compositeColorScale are then scaled by the average value
//between the two closest nodes
void fireScale(){
	static unsigned char fire[FIRE_NODES] = {0};
	static double step = LENGTH / (FIRE_NODES - 1);

	for(int i = 0; i < FIRE_NODES; i++){
		fire[i] = calcNextValue(fire[i], fire_set->targ_br);
	}

	for(int i = 0; i < LENGTH; i++){
		unsigned char lower = i / step;
		double d_low = fire[lower] / (i - lower * step);
		double d_hi = fire[lower + 1] / ((lower + 1) * step - i);
		double total = (d_low + d_hi) / step;
		unsigned char f_in = (char) total;

		fire_set->cur_br[i] = calcNextValue(fire_set->cur_br[i], 
			fire_set->targ_br);
		fire_set->cur_color_inten[i] = calcNextValue(fire_set->cur_color_inten[i], 
			fire_set->targ_br);
		fire_set->cur_color_inten[i] = clamp_t(fire_set->cur_color_inten[i], fire_set->col.G, 0x15);

		unsigned char r = scale(fire_set->cur_br[i], scaleFactor(scale(f_in, fire_set->c_scale[0]), fire_set->max_br));
		unsigned char g = scale(fire_set->cur_br[i], scaleFactor(scale(f_in, 
			scaleFactor(fire_set->cur_color_inten[i], fire_set->max_br)), fire_set->max_br));
		unsigned char b = scale(fire_set->cur_br[i], scaleFactor(scale(f_in, fire_set->c_scale[2]), fire_set->max_br));

		leds.setPixelColor(i, r, g, b);

	}
}

static double calcThetaWalk(int cur, int target){
	double theta = target - cur;

	//"steps" determines how much we want to get back to the average value
	//the default is very high, so this function is practically random

	theta /= fire_set->steps;
	theta =  1.0 - theta;
	theta /= 2.0;
	return theta;
}

static int calcNextValue(int cur, int target){
	double theta = calcThetaWalk(cur, target);
	double rand_num = random(1000);
	if(theta * 1000 < rand_num){
		return clamp(cur + fire_set->variance);
	}else{
		return clamp(cur - fire_set->variance);
	}
}

static int scale(int num, double scale){
	return (int) ((double) num * scale);
}

static double scaleFactor(int startMax, int endMax){
	return (double) startMax / (double) endMax;
}

static int clamp(int val){
	if(val > fire_set->max_br){
		return fire_set->max_br;
	}else if(val < 0){
		return 0;
	}
	return val;
}

static int clamp_t(int val, int target, int range){
	if(val > target + range){
		return clamp(target + range);
	}else if(val < target - range){
		return clamp(target - range);
	}
	return clamp(val);
}