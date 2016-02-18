//This should emulate a "candle" or fireplace along the strip of leds
//based on the information found on:
// https://www.reddit.com/r/programming/comments/3zsbw5/reverse_engineering_a_real_candle/

#include <Adafruit_NeoPixel.h>


#define PIN 8  //Pin on teensy used to control the strip
#define LENGTH 147 //number of leds in the strip

Adafruit_NeoPixel leds = Adafruit_NeoPixel(LENGTH, PIN, NEO_GRB + NEO_KHZ800);

const unsigned char max_br = 255; //max brightness
unsigned char targ_br = 128; //brightness to be aimed for (average)

unsigned char cur_br[LENGTH]; //current intesity of each led
unsigned char color[] = {0xFF, 0x60, 0x00}; //hardcoded orangish color

unsigned char variance = 5; //the amount the led should change with each step
double c_scale[3]; //scaled intensity of each color

char mode = 0;

// length in milliseconds for each loop
unsigned long startup_length = 50; 
unsigned long loop_length = 10;

//number of steps to converge to the targ_br
//the higher it is, the more variance in the intensity
double steps = 12800.0;

void setup(){
	mode = 0;
	randomSeed(analogRead(0));
  	leds.begin();
  	c_scale[0] = scaleFactor(color[0], max_br);
  	c_scale[1] = scaleFactor(color[1], max_br);
	c_scale[2] = scaleFactor(color[2], max_br);
	//calculates the scaling factor for each part of the given color
  	for(int i = 0; i < LENGTH; i++){
  		cur_br[i] = 0;
  	}
}

void loop(){
	burn();
}

void burn(){
	switch(mode){


		static unsigned long last_loop = 0;
		last_loop = millis();


		case 0:
			//starting procedure
			//progressively increase the brightness

			for(int i = 0; i < LENGTH; i++){
				leds.setPixelColor(i, scale(cur_br[i], c_scale[0]), scale(cur_br[i], c_scale[1]),
					scale(cur_br[i], c_scale[2]));
				cur_br[i]++;
			}
			if(cur_br[0] > targ_br){
				mode = 1;
			}
			if(last_loop + startup_length > millis()){
				delay(last_loop - millis() + startup_length);
			}
			break;


		case 1:
			greenColorScale(last_loop);
			
			break;
			

		default:
			break;

		}
	leds.show();

}

//scales all colors
void fullColorScale(long last_loop){
	for(int i = 0; i < LENGTH; i++){

		cur_br[i] = calcNextValue(cur_br[i], targ_br);
		leds.setPixelColor(i, scale(cur_br[i], c_scale[0]), scale(cur_br[i], c_scale[1]),
			scale(cur_br[i], c_scale[2]));
	}
	if(last_loop + loop_length > millis()){
		delay(last_loop - millis() + loop_length);
	}
}

//only scales green, may look more like a fire
void greenColorScale(long last_loop){
	for(int i = 0; i < LENGTH; i++){

		cur_br[i] = calcNextValue(cur_br[i], targ_br);
		leds.setPixelColor(i, color[0], scale(cur_br[i], c_scale[1]), color[2]);
	}
	if(last_loop + loop_length > millis()){
		delay(last_loop - millis() + loop_length);
	}
}

double calcThetaWalk(int cur, int target){
	double theta = target - cur;
	theta /= steps; //this is the amount of "steps" remianing to get to the 
				//desired value, but since this sould run indefinately,
				//its currently hardcoded
	theta = 1.0 - theta;
	theta /= 2.0;
	return theta;
}

int calcNextValue(int cur, int target){
	double theta = calcThetaWalk(cur, target);
	double randnum = random(1000);
	if(theta * 1000  < randnum){
		return (cur >= 255 - variance) ? 255 : cur + variance;
	}else{
		return (cur <= variance) ? 0 : cur - variance;
	}
}

int scale(int num, double scale){
	return (int) ((double) num * scale);
}

double scaleFactor(int startMax, int endMax){
	return (double) startMax / (double) endMax;
}