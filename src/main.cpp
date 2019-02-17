#include <CAVIS/window.h>
#include <utility>

#include "predator_and_prey.h"

int main() {

	// HD aspect ratio = 16:9
	unsigned height = 100;
	unsigned width = height * 16 / 9;
	unsigned pixel_size = 4;

	Window window(std::make_unique<PredatorAndPrey>(), width, height, pixel_size, "Predator & Prey");
	window.run();

	return 0;
}
