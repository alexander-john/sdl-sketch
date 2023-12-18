/*
* This program was written by Alexander John for educational purposes.
*
*/

#pragma once
#include <SDL.h>

struct Vector2 {
	float x;
	float y;
};

class Game {
public:
	// constructor
	Game();

	// initialize game
	bool initialize();

	// run game loop until over
	void runLoop();

	// shutdown game
	void shutdown();

private:
	// helper functions
	void processInput();

	void updateGame();

	// SDL window
	SDL_Window* mWindow;

	// SDL renderer
	SDL_Renderer* mRenderer;

	// is running?
	bool mIsRunning;

	// direction of paddle
	int paddleDir;

	// position of paddle
	vect
};