#include <CAVIS/window.h>
#include <iostream>
#include <args.hxx>

#include "predator_and_prey.h"

int main(int argc, char *argv[]) {

	args::ArgumentParser parser(
		"Predator & Prey in SFML using Rapatas/CAVIS",
		""
	);

	args::HelpFlag help(
		parser,
		"help",
		"Display this help menu",
		{"help"}
	);
	args::ValueFlag<int> arg_width(
		parser,
		"cells",
		"The width of the arena in cells",
		{'w', "width"}
	);
	args::ValueFlag<int> arg_height(
		parser,
		"cells",
		"The height of the arena in cells",
		{'h', "height"}
	);
	args::ValueFlag<int> arg_cell_size(
		parser,
		"pixels",
		"The size of a cell in pixels",
		{'s', "cell-size"}
	);

	try {
		parser.ParseCLI(argc, argv);
	} catch (args::Help) {
		std::cout << parser;
		return 0;
	} catch (args::ParseError e) {
		std::cerr << e.what() << std::endl;
		std::cerr << parser;
		return 1;
	} catch (args::ValidationError e) {
		std::cerr << e.what() << std::endl;
		std::cerr << parser;
		return 1;
	}

	double hd_aspect_ratio = 16 / 9.0;
	unsigned height    = args::get(arg_height);
	unsigned width     = args::get(arg_width);
	unsigned cell_size = args::get(arg_cell_size);

	if (!arg_height && arg_width) {
		height = args::get(arg_width) / hd_aspect_ratio;
	}
	if (!arg_width && arg_height) {
		width = args::get(arg_height) * hd_aspect_ratio;
	}
	if (!arg_width && !arg_height) {
		height = 100;
		width = height * hd_aspect_ratio;
	}

	if (!arg_cell_size) {
		cell_size = 4;
	}

	Window window(
		std::make_unique<PredatorAndPrey>(),
		width,
		height,
		cell_size,
		"Predator & Prey"
	);
	window.run();

	return 0;
}
