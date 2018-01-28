#ifndef OUTRUN_H
#define OUTRUN_H

#include <Adafruit_NeoPixel.h>
#include "led.hpp"

#define OUTRUN_NODES 5

typedef struct outrun_struct {
	Color colors[4];

} OutrunSet;

extern OutrunSet *outrun_set;

void outrun_init();
void drive();

static Color combine(Color one, Color two, int dist_one, int dist_two);

#endif
