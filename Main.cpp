/*
* This program was written by Alexander John for educational purposes.
*
* All this program does is allow you to move a block around the screen.
* You move it by using WASD. There is a bit of collision detection so 
* the block remains in view.
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