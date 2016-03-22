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

#endif