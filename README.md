# Preditor & Prey
Preditor & Prey is a [cellular automaton](https://en.wikipedia.org/wiki/Cellular_automaton) simulating an environment where a preditor (red) and a prey (green) exist in a harmonic balance using the following set of rules:
* If a prey moves, it multiplies in the previous position
* If a preditor lands on a prey, it turns it into a preditor
* Preditors die after 10 rounds

![Preview](https://i.imgur.com/QzlzzWK.png "Preditor & Prey")

This project implements Preditor & Prey using C++ and displays it using [Rapatas/CAVIS](https://github.com/Rapatas/CAVIS)

# Requirements
* [Rapatas/flat_matrix](https://github.com/Rapatas/flat_matrix)
* [Rapatas/CAVIS](https://github.com/Rapatas/CAVIS)
* [SFML](https://www.sfml-dev.org/index.php)
