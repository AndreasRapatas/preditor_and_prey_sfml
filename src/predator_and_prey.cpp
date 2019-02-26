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
			state[i] = Cell(Type::Prey);
			break;
		case 2:
			state[i] = Cell(Type::Predator);
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

		if (state[i].type == Type::Nothing) { continue; }

		if (state[i].type == Type::Predator) {

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

		// Wrap on the edges
		if (new_x < 0) { new_x = width - 1; }
		if ((unsigned) new_x == width) { new_x = 0; }
		if (new_y < 0) { new_y = height - 1; }
		if ((unsigned) new_y == height) { new_y = 0; }

		Cell &other_cell = state(new_x, new_y);
		Cell &this_cell = state[i];

		if (this_cell.type == Type::Predator) {

			// Eat
			if (other_cell.type == Type::Prey) {
				other_cell = Cell(Type::Predator);
			}

		} else {

			if (other_cell.type == Type::Nothing) {
				other_cell = Cell(Type::Prey);
			}
		}
	}
}

sf::Color PredatorAndPrey::get_pixel(unsigned i) {

	switch (state[i].type) {

	case Type::Nothing:
		return {0, 0, 0};
	case Type::Predator:
		return {255, 0, 0};
	case Type::Prey:
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
