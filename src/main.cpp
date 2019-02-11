#include <CAVIS/window.h>

#include "predator_and_prey.h"

int main() {

	// HD aspect ratio = 16:9
	unsigned height = 100;
	unsigned width = height * 16 / 9;
	unsigned pixel_size = 4;

	auto pp = new PredatorAndPrey;

	Window window(pp, width, height, pixel_size, "Predator & Prey");
	window.run();

	delete pp;

	return 0;
}
