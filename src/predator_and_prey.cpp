#include "predator_and_prey.h"

PredatorAndPrey::PredatorAndPrey() :
	type(0, 2),
	move(-1, 1)
{}

void PredatorAndPrey::fill_random() {

	for (unsigned i = 0; i < cell_number; ++i) {
		switch (type(generator)) {
		case 0:
			state[i] = Cell();
			break;
		case 1:
			state[i] = Cell(Type::PREY);
			break;
		case 2:
			state[i] = Cell(Type::PREDITOR);
			break;
		}
	}
}

unsigned PredatorAndPrey::calc_index(unsigned x, unsigned y) {
	return (x + y * width);
}

unsigned PredatorAndPrey::calc_x(unsigned index) {
	return index % width;
}

unsigned PredatorAndPrey::calc_y(unsigned index) {
	return index / width;
}

void PredatorAndPrey::step() {

	int x = 0;
	int y = 0;
	int new_x = 0;
	int new_y = 0;

	for (unsigned i = 0; i < cell_number; ++i) {

		if (state[i].type == Type::NOTHING) { continue; }

		if (state[i].type == Type::PREDITOR) {

			// Is it dead?
			if (--state[i].health == 0) {
				state[i] = Cell();
				continue;
			}
		}

		x = calc_x(i);
		y = calc_y(i);

		new_x = move(generator) + x;
		new_y = move(generator) + y;

		// The random generator said it will not move
		if (new_x == x && new_y == y) { continue; }
		// Won't move because it reached the end of the board
		if (new_x < 0 || (unsigned)new_x >= width) { continue; }
		if (new_y < 0 || (unsigned)new_y >= height) { continue; }

		Cell &other_cell = state(new_x, new_y);
		Cell &this_cell = state[i];

		if (this_cell.type == Type::PREDITOR) {

			// Eat
			if (other_cell.type == Type::PREY) {
				other_cell = Cell(Type::PREDITOR);
			}

		} else {

			if (other_cell.type == Type::NOTHING) {
				other_cell = Cell(Type::PREY);
			}
		}
	}
}

sf::Color PredatorAndPrey::get_pixel(unsigned i) {

	switch (state[i].type) {

	case Type::NOTHING:
		return {0, 0, 0};
	case Type::PREDITOR:
		return {255, 0, 0};
	case Type::PREY:
		return {0, 255, 0};
	}
}

sf::Vector2u PredatorAndPrey::get_dimentions() {
	return {width, height};
}

void PredatorAndPrey::set_dimentions(sf::Vector2u dim) {

	width       = dim.x;
	height      = dim.y;
	cell_number = width * height;
	state       = flat_matrix<Cell>(width, height);

	fill_random();
}

std::vector<Agent> PredatorAndPrey::get_agents() {
	// No agents here, just state
	return {};
}
