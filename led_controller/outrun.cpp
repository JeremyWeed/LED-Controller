// Implements functions in outrun.hpp

#include "include/outrun.hpp"

OutrunSet *outrun_set;

void outrun_init() {

	outrun_set = (OutrunSet*) calloc(1, sizeof(OutrunSet));
	OutrunSet *os = outrun_set;

	setCol(&os->cols[0], 0x07d8cf); // blue
	setCol(&os->cols[1], 0xea0ab3); //pink
	setCol(&os->cols[2], 0xf7a481); //orange/yellow
	setCol(&os->cols[3], 0x170562); // dark blue
}

void drive() {

}

static Color combine(Color one, Color two, int dist_one, int dist_two) {
	Color ret;
	ret.R = (one.R * dist_one + two.R * dist_two) / (dist_one + dist_two);
	ret.G = (one.G * dist_one + two.G * dist_two) / (dist_one + dist_two);
	ret.B = (one.B * dist_one + two.B * dist_two) / (dist_one + dist_two);
	return ret;
}
