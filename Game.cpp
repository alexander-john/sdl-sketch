/*
* This program was written by Alexander John for educational purposes.
*
*/

#include "Game.h"

// global variables
const int thickness = 15;

// call game constructor and initialize variables
Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mIsRunning(true)
	, mTicksCount(0)
	, mBlockDirY(0)
	, mBlockDirX(0)
	, mBlockPos{0,0}
{}

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

	mBlockPos.x = 250;
	mBlockPos.y = 300;

	return true;
}

// shutdown SDL
void Game::shutdown() {
	// destroy window
	SDL_DestroyWindow(mWindow);

	// destroy renderer
	SDL_DestroyRenderer(mRenderer);

	// quit SDL
	SDL_Quit();
}

// iterates game loop
void Game::runLoop() {
	while (mIsRunning) {
		processInput();

		updateGame();

		generateOutput();
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

	// update block direction based on W/S/A/D keys
	mBlockDirY = 0;
	mBlockDirX = 0;

	// move up
	if (state[SDL_SCANCODE_W]) {
		mBlockDirY -= 1;
	}

	// move down
	if (state[SDL_SCANCODE_S]) {
		mBlockDirY += 1;
	}

	// move left
	if (state[SDL_SCANCODE_A]) {
		mBlockDirX -= 1;
	}

	// move right
	if (state[SDL_SCANCODE_D]) {
		mBlockDirX += 1;
	}
}

void Game::generateOutput() {
	// specify drawing color
	SDL_SetRenderDrawColor(
		mRenderer,			// renderer
		150,				// R
		50,					// G
		55,					// B
		255					// A
	);

	// clear current buffer with drawing color
	SDL_RenderClear(mRenderer);

	SDL_SetRenderDrawColor(
		mRenderer,			// renderer
		50,					// R
		50,					// G
		255,				// B
		255					// A
	);

	// draw rectangle
	SDL_Rect block{
		static_cast<int>(mBlockPos.x - thickness/2),		// top left x
		static_cast<int>(mBlockPos.y - thickness/2),		// top left y
		thickness,											// width
		thickness											// height
	}; // draw rectangle to current buffer
	SDL_RenderFillRect(mRenderer, &block); 

	// update buffer with rendering performed since
	SDL_RenderPresent(mRenderer);
}

void Game::updateGame() {
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	/*
	* A game running at 30 FPS has roughly 33 milliseconds (ms) elapse
	* from frame to frame. (1000 ms in 1 s)The game loop actually runs
	* several times per second, and every iteration of the game loop
	* updates the game in a discrete (distinct) time step. In 30 FPS, each iteration
	* of the game loop should simulate 33ms of time progression in the game.
	* 
	* It is important to distinguish  real time, the time elapsing in the real
	* world, from game time, the time elapsing in the games world. There
	* are many other instances where real time and game time might diverge.
	* For example, in a football game, rather than requiring a player
	* to sit through 15 full minutes per quarter, the game may update
	* the clock twice as fast, so each quarter takeszs only 7.5 minutes.
	* 
	* When assuming a fixed frame rate, code that updates the position
	* of an enemy might look like this:
	* 
	* // update x position by 5 pixels
	* enemy.mPosition.x += 5;
	* 
	* if the code moves the enemy at the desired speed on an 8 MHz
	* processor, what happens on a 16 MHz processor? Because the
	* game loop now runs twice as fast, the enemy will now also
	* move twice as fast.
	* 
	* To solve this issue, games use delta time: the amount of elapsed
	* game time since the last frame. To convert the preceding code
	* to using delta time, instead of thinking of movement as
	* pixels per frame, you should think of it as pixels per second.
	* If the ideal movement speed is 150 pixels per second, the following
	* code is much more flexible:
	* 
	* // update x position by 150 pixels/second
	* enemy.mPosition.x += 150 * deltaTime;
	* 
	* Now the code will work well regardless of the frame rate. At
	* 30 FPS, the delta time is ~0.033, so the enemy will move 5
	* pixels per frame, for a total of 150 pixels per second. At
	* 60 FPS, the enemy will move only 2.5 pixels per frame but will
	* still move a total of 150 pixels per second. The movement certainly
	* will be smoother in the 60 FPS case, but the overall per-second
	* speed remains the same.
	* 
	* To help calculate delta time, SDL provides an SDL_GetTicks member
	* function that returns the number of milliseconds elapsed since the SDL_Init
	* function call. By saving the result of SDL_GetTicks from the
	* previous frame in a member variabel, you can use the current
	* value to calculate delta time.
	*/

	// delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();

	// Because mTicksCount starts at zero, you end up with
	// some positive value of SDL_GetTicks (the milliseconds
	// since initialization) and divide it by 1000.0f to get
	// a delta time in seconds. Next you save the current value
	// of SDL_GetTicks in mTicksCount. On the next frame, the
	// deltaTime line calculates a new delta time based on the
	// old value of mTicksCount and the new value.

	// clamp maximum delta time value
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	// update block based on delta time
	if (mBlockDirY != 0) {
		mBlockPos.y += mBlockDirY * 300.0f * deltaTime;

		// make sure block does not move off screen
		if (mBlockPos.y < (thickness / 2.0f)) {

			mBlockPos.y = thickness / 2.0f;

		}
		else if (mBlockPos.y > (768.0f - thickness / 2.0f)) {
			mBlockPos.y = 768.0f - (thickness / 2.0f);
		}
	}

	// update block based on delta time
	if (mBlockDirX != 0) {
		mBlockPos.x += mBlockDirX * 300.0f * deltaTime;

		// make sure block does not move off screen
		if (mBlockPos.x < (thickness / 2.0f)) {

			mBlockPos.x = thickness / 2.0f;

		}
		else if (mBlockPos.x > (1024.0f - thickness / 2.0f)) {
			mBlockPos.x = 1024.0f - (thickness / 2.0f);
		}
	}
}