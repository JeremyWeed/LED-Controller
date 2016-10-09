#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>
#define PIN 8
#define LENGTH 147

typedef struct color{
	unsigned char R;
	unsigned char G;
	unsigned char B;
}Color;

extern Adafruit_NeoPixel leds;

static unsigned char scale(unsigned char col, unsigned char inten){
	float ratio =  inten / (float) 0xFF;
	ratio *= col;
	return (unsigned char) ratio;
}

static void setCol(Color *col, unsigned int color){

	col->R = (color & 0xFF0000) >> 16;
	col->G = (color & 0x00FF00) >> 8;
	col->B = (color & 0x0000FF);
}

#endif
