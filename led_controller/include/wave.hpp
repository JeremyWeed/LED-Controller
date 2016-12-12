#ifndef WAVE_HPP
#define WAVE_HPP

#include "led.hpp"
//the number of peaks present in the strip at one time
#define WAVES_PER_STRIP 4
//number of waves generated per second
#define WAVES_PER_SEC 1
typedef struct wave_set{

/**
 * look into trochoid/clausen function
 * theta = kx + phi*t
 * A: amplitude, or color shade in this implementation
 * x: distance across strip/LED index (0...LENGTH)
 * t: time
 */

	//double A;
	double k = WAVES_PER_STRIP * 2 * 3.14 / LENGTH;
	//phi assumes seconds
	double phi = WAVES_PER_SEC * 2 * 3.14;
	//base color of the wave
	Color col;

}WaveSet;

void wave_init();
void wave_main();
Color wave_calc_color(int x, double time);
double clausen(int x, double t);

#endif //WAVE_HPP
