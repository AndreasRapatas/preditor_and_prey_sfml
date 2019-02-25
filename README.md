# Predator & Prey
This project implements the [cellular automaton](https://en.wikipedia.org/wiki/Cellular_automaton) Predator & Prey using C++ and displays it using [Rapatas/CAVIS](https://github.com/Rapatas/CAVIS). Predator & Prey is simulating an environment where a predator (red) and a prey (green) exist in a harmonic balance using the following set of rules:
* If a prey moves, it multiplies in the previous position
* If a predator lands on a prey, it turns it into a predator
* Predators die after 10 rounds

# Usage
```bash
predator_and_prey_sfml --height 100
```

![Preview](https://i.imgur.com/LzmDeJM.gif "Preditor & Prey")

# Installation

## Dependencies
Follow the project's installation instructions.
* [Rapatas/flat_matrix](https://github.com/Rapatas/flat_matrix)
* [Rapatas/CAVIS](https://github.com/Rapatas/CAVIS)
* [Taywee/args](https://github.com/Taywee/args)

## Predator & Prey
```bash
git clone https://github.com/Rapatas/predator_and_prey_sfml
mkdir predator_and_prey_sfml/build
cd predator_and_prey_sfml/build
cmake ..
make install # As root
```
