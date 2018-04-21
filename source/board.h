#ifndef BOARD_H_
#define BOARD_H_

#include <random>
#include <iostream>

class Board {

private:

	struct Cell {

		enum class State {
			PREY,
			PREDITOR,
			NOTHING,
		};

		State state;
		unsigned health;

		Cell() :
			state(State::NOTHING)
		{}

		Cell(State s) :
			state(s)
		{
			if (state == State::PREDITOR) {
				health = 10;
			} else {
				health = 0;
			}
		}
	};

	Cell *data;
	unsigned width;
	unsigned height;
	unsigned cell_num;

	// Preditor - Prey - Nothing
	std::uniform_int_distribution<unsigned> type;
	// +1 or -1
	std::uniform_int_distribution<int> move;
	std::default_random_engine generator;

public:

	Board (unsigned width, unsigned height) :
		width(width),
		height(height),
		cell_num(height * width)
	{
		data = new Cell[cell_num];
		if (!data) {
			std::cout << "Malloc " << cell_num * sizeof(Cell) << " failed!\n";
			exit(1);
		}

		for (unsigned i = 0; i < cell_num; ++i) {
			data[i] = Cell();
		}

		type = std::uniform_int_distribution<unsigned>(0, 2);
		move = std::uniform_int_distribution<int>(-1, 1);

		fill_random();
		// fill_one();
	}

	virtual ~Board () {
		delete[] data;
	}

	void fill_random() {

		for (unsigned i = 0; i < cell_num; ++i) {
			switch (type(generator)) {
			case 0:
				data[i] = Cell();
				break;
			case 1:
				data[i] = Cell(Cell::State::PREY);
				break;
			case 2:
				data[i] = Cell(Cell::State::PREDITOR);
				break;
			}
		}
	}

	void fill_one() {

		for (unsigned i = 0; i < cell_num; ++i) {

			if (calc_x(i) > 150)
				data[i] = Cell(Cell::State::PREY);
			else if(i % 2 == 0)
				data[i] = Cell(Cell::State::PREDITOR);
			else
				data[i] = Cell(Cell::State::NOTHING);
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

		for (unsigned i = 0; i < cell_num; ++i) {

			if (data[i].state == Cell::State::NOTHING) { continue; }

			x = calc_x(i);
			y = calc_y(i);

			new_x = move(generator) + x;
			new_y = move(generator) + y;

			if (new_x < 0 || new_x >= width) { continue; }
			if (new_y < 0 || new_y >= height) { continue; }
			if (new_x == x && new_y == y) { continue; }

			Cell &this_cell = data[i];
			Cell &other_cell = data[calc_index(new_x, new_y)];

			if (this_cell.state == Cell::State::PREDITOR) {

				// Is it dead?
				if (--this_cell.health == 0) {
					this_cell = Cell();
					continue;
				}

				// Eat
				if (other_cell.state == Cell::State::PREY) {
					this_cell.health += other_cell.health;
					other_cell = Cell(Cell::State::PREDITOR);
				}

				// Moves anyway
				std::swap(this_cell, other_cell);

			} else {

				++this_cell.health;
				if (other_cell.state == Cell::State::NOTHING) {
					other_cell = Cell(Cell::State::PREY);
					std::swap(this_cell, other_cell);
				}
			}
		}
	}

	uint32_t inline color32(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) const {
		// Asume litle-endian
		return (r << 8 * 0) + (g << 8 * 1) + (b << 8 * 2) + (a << 8 * 3);
	}

	// Used for rendering
	uint32_t inline operator[](unsigned i) const {

		if (data[i].state == Cell::State::PREDITOR) {
			return color32(255,0,0);

		} else if (data[i].state == Cell::State::PREY) {
			return color32(0, 255, 0);

		} else {
			return color32(0, 0, 0);
		}
	}
};

#endif /* end of include guard: BOARD_H_ */
