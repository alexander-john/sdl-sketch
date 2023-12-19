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

	void generateOutput();

	// SDL window
	SDL_Window* mWindow;

	// SDL renderer
	SDL_Renderer* mRenderer;

	// is running?
	bool mIsRunning;

	// Number of ticks since start of game
	Uint32 mTicksCount;

	// position of block
	Vector2 mBlockPos;

	// block direction 
	int mBlockDir;
};