// This is the main file for all of my led controller stuff
// everything else is written in the included files

#include <Adafruit_NeoPixel.h>
#include "include/led.h"
#include "include/fire.h"
#include "include/snow.h"

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LENGTH, PIN, NEO_GRB + NEO_KHZ800);

void setup(){
	s_init();
	leds.begin();
}

void loop(){
	snow();
}

