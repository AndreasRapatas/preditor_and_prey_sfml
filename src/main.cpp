#include <CAVIS/window.h>

#include "preditor_and_prey.h"

int main() {

	// HD aspect ratio = 16:9
	unsigned height = 100;
	unsigned width = height * 16 / 9;
	unsigned pixel_size = 4;

	Window<PreditorAndPrey> window(width, height, pixel_size, "Preditor & Prey");
	window.run();

	return 0;
}
