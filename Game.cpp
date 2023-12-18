/*
* This program was written by Alexander John for educational purposes.
*
*/

#include "Game.h"

// initialize game
bool Game::initialize() {
	// initialize
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	// if initialize fails?
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());

		return 0;
	}

	// create window
	mWindow = SDL_CreateWindow(
		"Game Programming",		// window title
		100,					// top left x-coordinate of window
		100,					// top left y-coordinate of window
		1024,					// width of window
		768,					// height of window
		0						// flag (0 for no flag set)
	);

	// if window creation fails?
	if (!mWindow) {
		SDL_Log("Failed to create window: %s", SDL_GetError());

		return false;
	}

	// create renderer
	mRenderer = SDL_CreateRenderer(
		mWindow,			// window to create renderer
		-1,					// usually -1
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	// if renderer fails
	if (!mRenderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	return true;
}

// shutdown SDL
void Game::shutdown() {
	// destroy window
	SDL_DestroyWindow(mWindow);

	// quit SDL
	SDL_Quit();
}

// iterates game loop
void Game::runLoop() {
	while (mIsRunning) {
		processInput();

		//updateGame();

		//generateOutput();
	}
}

// process input
void Game::processInput() {
	SDL_Event event;

	// while there are still events in queue
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:		// SDL_QUIT when user tries to close window
			mIsRunning = false;
			break;
		}
	}

	// get state of keyboard
	const Uint8* state = SDL_GetKeyboardState(NULL);

	// if escape is pressed, end loop
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
}