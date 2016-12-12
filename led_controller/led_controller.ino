// This is the main file for all of my led controller stuff
// everything else is written in the included files

#include <Adafruit_NeoPixel.h>
#include "include/led.hpp"
#include "include/fire.hpp"
#include "include/snow.hpp"
#include "include/string_lights.hpp"
#include "include/soft_string.hpp"
#include "include/wave.hpp"

#define MODES 5
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LENGTH, PIN, NEO_GRB + NEO_KHZ800);
int mode = 0;

void setup(){
	randomSeed(analogRead(A0));
	mode = random(MODES);  //0 - 3
	switch(mode){
		case 0:
			sl_init();
			break;
		case 1:
			f_init();
			break;
		case 2:
			s_init();
			break;
		case 3:
			soft_string_init();
			break;
		case 4:
			wave_init();
		default:
			//R.I.P. little arduino
			;
	}
	leds.begin();
}

void loop(){
	switch(mode){
		case 0:
			string_light_main();
			break;
		case 1:
			burn();
			break;
		case 2:
			snow();
			break;
		case 3:
			soft_light();
			break;
		case 4:
			wave_main();
			break;
		default:
			//looks like we found an error, set something to red
			leds.setPixelColor(1, 255, 0, 0);
	}
}
