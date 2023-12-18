/*
* This program was written by Alexander John for educational purposes.
*
*/

#include "Game.h"

int main(int argc, char** argv) {
	// create game
	Game game;

	// initialize game
	bool success = game.initialize();

	// if success?
	if (success) {
		game.runLoop();
	}

	game.shutdown();

	return 0;
}