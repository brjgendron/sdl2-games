#include <game.hpp>

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char *title, int x, int y, int width, int height) {
	int flags = 0;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL initialized" << std::endl;

		window = SDL_CreateWindow(title, x, y, width, height, flags);
		if (window) {
			std::cout << "window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, 0, -1);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "renderer created" << std::endl;
		}

		isRunning = true;
	} else {
		isRunning = false;
		std::cout << "SDL failed to initialize" << std::endl;
	}
}

void Game::handleEvents() {
	SDL_Event e;
	SDL_PollEvent(&e);

	switch (e.type) {
		case SDL_QUIT:
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::update() {

}

void Game::render() {
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void Game::destroy() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	std::cout << "window destroyed" << std::endl << "renderer destroyed" << std::endl;
}

