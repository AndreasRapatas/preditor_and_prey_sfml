#ifndef BOARD_H
#define BOARD_H

#include <random>
#include <iostream>

#include <CAVIS/cellular_automaton.h>
#include <flat_matrix/flat_matrix.h>

class PredatorAndPrey : public CellularAutomaton {

private:

	enum class Type {
		PREY,
		PREDITOR,
		NOTHING,
	};

	struct Cell {

		Type type;
		unsigned health;

		Cell() :
			type(Type::NOTHING)
		{}

		Cell(Type t) :
			type(t)
		{
			health = (type == Type::PREDITOR)
				? 10 // Will die of age in 10 cycles
				: 0; // Can't die of age
		}
	};

	unsigned width;
	unsigned height;
	unsigned cell_number;
	flat_matrix<Cell> state;

	// Preditor - Prey - Nothing
	std::uniform_int_distribution<unsigned> type;
	// +1 or -1
	std::uniform_int_distribution<int> move;
	std::default_random_engine generator;

public:

	PredatorAndPrey(sf::Vector2u dim) :
		width(dim.x),
		height(dim.y),
		cell_number(height * width),
		state(width, height),
		type(0, 2),
		move(-1, 1)
	{
		fill_random();
	}

	void fill_random() {

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

	void fill_one() {

		for (unsigned i = 0; i < cell_number; ++i) {

			if (calc_x(i) > 150)
				state[i] = Cell(Type::PREY);
			else if(i % 2 == 0)
				state[i] = Cell(Type::PREDITOR);
			else
				state[i] = Cell(Type::NOTHING);
		}
	}

	unsigned calc_index(unsigned x, unsigned y) {
		return (x + y * width);
	}

	unsigned calc_x(unsigned index) {
		return index % width;
	}

	unsigned calc_y(unsigned index) {
		return index / width;
	}

	void step() {

		int x = 0;
		int y = 0;
		int new_x = 0;
		int new_y = 0;

		for (unsigned i = 0; i < cell_number; ++i) {

			if (state[i].type == Type::NOTHING) { continue; }

			x = calc_x(i);
			y = calc_y(i);

			new_x = move(generator) + x;
			new_y = move(generator) + y;

			// Won't move because it reached the end of the board
			if (new_x < 0 || (unsigned)new_x >= width) { continue; }
			if (new_y < 0 || (unsigned)new_y >= height) { continue; }
			// The random generator said it will not move
			if (new_x == x && new_y == y) { continue; }

			Cell &this_cell = state[i];
			Cell &other_cell = state(new_x, new_y);

			if (this_cell.type == Type::PREDITOR) {

				// Is it dead?
				if (--this_cell.health == 0) {
					this_cell = Cell();
					continue;
				}

				// Eat
				if (other_cell.type == Type::PREY) {
					this_cell.health += other_cell.health;
					other_cell = Cell(Type::PREDITOR);
				}

				// This keeps the healthier preditors in the front line
				std::swap(this_cell, other_cell);

			} else {

				++this_cell.health;
				if (other_cell.type == Type::NOTHING) {
					other_cell = Cell(Type::PREY);

					// This keeps the newborns behind the healthy ones
					std::swap(this_cell, other_cell);
				}
			}
		}
	}

	sf::Color get_pixel(unsigned i) {

		switch (state[i].type) {

		case Type::NOTHING:
			return {0, 0, 0};
		case Type::PREDITOR:
			return {255, 0, 0};
		case Type::PREY:
			return {0, 255, 0};
		}
	}

	sf::Vector2u get_dimentions() {
		return {width, height};
	}

	void set_dimentions(sf::Vector2u dim) {

		width       = dim.x;
		height      = dim.y;
		cell_number = width * height;
		state       = flat_matrix<Cell>(width, height);

		fill_random();
	}

	std::vector<Agent> get_agents() {
		// No agents here, just state
		return {};
	}
};

#endif // BOARD_H
