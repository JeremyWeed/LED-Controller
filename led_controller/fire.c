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

}

void fullColorScale(long last_loop){

}

void greenColorScale(long last_loop){

}

void compositeColorScale(long last_loop){

}

static double calcThetaWalk(int cur, int target){

}

static int calcNextValue(int cur, int target){

}

static int scale(int num, double scale){
	return (int) ((double) num * scale);
}

static double scaleFactor(int startMax, int endMax){
	return (double) startMax / (double) endMax;
}