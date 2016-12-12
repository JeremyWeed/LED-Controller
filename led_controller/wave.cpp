#include "include/wave.hpp"

WaveSet *wave_set;

void wave_init(){
	wave_set = (WaveSet*) calloc(1, sizeof(WaveSet));
	setCol(&wave_set->col, 0x00D4FF);
}

void wave_main(){
	double t = millis() / 1000.0;
	for(int i = 0; i < LENGTH; i++){
		Color t_col = wave_calc_color(i, t);
		leds.setPixelColor(i, t_col.R, t_col.G, t_col.B);
	}
}

//basic scale between white and the set color
Color wave_calc_color(int x, double time){
	double val = clausen(x, time);
	Color newCol;
	val += 1;
	val /= 2;
	newCol.R = (255 - wave_set->col.R) * val + wave_set->col.R;
	newCol.G = (255 - wave_set->col.G) * val + wave_set->col.G;
	newCol.B = (255 - wave_set->col.B) * val + wave_set->col.B;
	return newCol;
}

double clausen(int x, double time){
	double theta = wave_set->k * x + wave_set->phi * time;
	double clausen = sin(theta);
	clausen += sin(2 * theta) / 4;
	clausen += sin(3 * theta) / 9;
	clausen += sin(4 * theta) / 16;
}
