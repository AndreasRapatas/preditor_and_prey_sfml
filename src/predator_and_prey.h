#ifndef BOARD_H
#define BOARD_H

#include <random>

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

	PredatorAndPrey();

	void fill_random();

	void fill_one() ;

	unsigned calc_index(unsigned x, unsigned y);

	unsigned calc_x(unsigned index);

	unsigned calc_y(unsigned index);

	void step();

	sf::Color get_pixel(unsigned i);

	sf::Vector2u get_dimentions();

	void set_dimentions(sf::Vector2u dim);

	std::vector<Agent> get_agents();
};

#endif // BOARD_H
