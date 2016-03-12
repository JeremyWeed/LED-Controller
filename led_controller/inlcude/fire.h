#ifndef FIRE_H
#define FIRE_H
//header file for the fire led strip procdedures
//Written by Jeremy Weed

#include <Adafruit_NeoPixel.h>
#include "led.h"

typedef struct fire_set{
	//average and maximum brightness of the leds
	unsigned char max_br = 255;
	unsigned char targ_br = 128;

	//arrays to hold the color and brightness of each led
	unsigned char cur_br[LENGTH];
	unsigned char cur_color_inten[LENGTH];
	Color col = {.R = 0xFF, .G = 0x.60, .B = 0x00}; 

	//value pre-calc'ed to scale each part of the color
	double c_scale[3];

	//the mode for the fire
	unsigned char mode = 0;

	//amount the led should change with each interation
	unsigned char variance = 3;
}FireSet;

FireSet *fire_set;

void init();
void change_color(Color col);
void burn();
void fullColorScale(long last_loop);
void greenColorScale(long last_loop);
void compositeColorScale(long last_loop);

static double calcThetaWalk(int cur, int target);
static int calcNextValue(int cur, int target);
static int scale(int num, double scale);
static double scaleFactor(int startMax, int endMax);




#endif