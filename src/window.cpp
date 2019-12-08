#include <iostream>
#include <window.hpp>

Window::Window(const char *title, int x, int y, int width, int height) {
	this->title = title;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Window::~Window() {

}

void Window::init() {
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		std::cout << "SDL2 video subsystem initialized successfully" << std::endl;
		window = SDL_CreateWindow(this->title, this->x, this->y, this->width, this->height, SDL_WINDOW_SHOWN);
		if (window) {
			std::cout << "window created" << std::endl;
		} else {
			std::cout << "failed to create window: " << SDL_GetError() << std::endl;
		}

		renderer = SDL_CreateRenderer(window, 0, -1);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "renderer created" << std::endl;
		} else {
			std::cout << "failed to create renderer: " << SDL_GetError() << std::endl;
		}

		running = true;
	} else {
		running = false;
		std::cout << "SDL2 video subsystem failed to initialize: " << SDL_GetError() << std::endl;
	}
}

void Window::handleEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			running = false;
			break;
		
		default:
			break;
		}
	}
}

void Window::update() {

}

void Window::render() {
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void Window::destroy() {
	SDL_DestroyWindow(window);
	std::cout << "window destroyed" << std::endl;

	SDL_DestroyRenderer(renderer);
	std::cout << "renderer destroyed" << std::endl;

	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	std::cout << "SDL2 video subsystem quit" << std::endl;
}
