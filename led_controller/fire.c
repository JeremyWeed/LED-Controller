//This is the cpp file that implements all of the functions declared in the fire.h 
//header file. 
//Written by Jeremy Weed

#include "fire.h"

void init(){
	FireSet fs;
	fire_set = malloc(sizeof(FireSet));
	fire_set = &fs;

	fs->c_scale[0] = scaleFactor(fs->col.R, fs->max_br);
	fs->c_scale[1] = scaleFactor(fs->col.G, fs->max_br);
	fs->c_scale[2] = scaleFactor(fs->col.B, fs->max_br);
}

void burn(){

}

void change_color(Color col){
	FireSet *fs = fire_set;

	fs->col = col;

	fs->c_scale[0] = scaleFactor(fs->col.R, fs->max_br);
	fs->c_scale[1] = scaleFactor(fs->col.G, fs->max_br);
	fs->c_scale[2] = scaleFactor(fs->col.B, fs->max_br);
}

void fullColorScale(long last_loop){

}

void greenColorScale(long last_loop){

}

void compositeColorScale(long last_loop){

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
		return max_br;
	}else if(val < 0){
		return 0;
	}
	return val;
}