#ifndef FIRE_H
#define FIRE_H
//header file for the fire led strip procdedures
//Written by Jeremy Weed

#include <Adafruit_NeoPixel.h>
#include "led.h"

#define FIRE_NODES 5

typedef struct fire_set{
	//average and maximum brightness of the leds
	unsigned char max_br;
	unsigned char targ_br;

	//arrays to hold the color and brightness of each led
	unsigned char cur_br[LENGTH];
	unsigned char cur_color_inten[LENGTH];
	Color col; 

	//value pre-calc'ed to scale each part of the color
	double c_scale[3];

	//the mode for the fire
	unsigned char mode;

	// length in milliseconds for each loop
	unsigned long startup_length; 
	unsigned long loop_length;

	//amount the led should change with each interation
	unsigned char variance;

	//determines how random the variations are
	//the higher the number, the more random
	unsigned long steps;

	unsigned char fire[FIRE_NODES];

}FireSet;

extern FireSet *fire_set;

void f_init();
void change_fire_color(Color col);
void burn();
void fadeIn();
void fullColorScale();
void greenColorScale();
void compositeColorScale();
void fireScale();
void fireScale2();

static void fire_str_init(FireSet *fs);
static double calcThetaWalk(int cur, int target);
static int calcNextValue(int cur, int target);
static int fscale(int num, double scale);
static double scaleFactor(int startMax, int endMax);
static int clamp(int val);
static int clamp_t(int val, int target, int range);


#endif