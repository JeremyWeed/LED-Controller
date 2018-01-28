#ifndef OUTRUN_H
#define OUTRUN_H

#include <Adafruit_NeoPixel.h>
#include "led.hpp"

#define OUTRUN_NODES 5
#define NUM_COLORS 4

typedef struct outrun_struct {
	Color colors[4];
	long length;
	int node_locations[OUTRUN_NODES];
	Color node_colors[OUTRUN_NODES];
} OutrunSet;

extern OutrunSet *outrun_set;

void outrun_init();
void drive();

static Color combine(Color one, Color two, int dist_one, int dist_two);

#endif
