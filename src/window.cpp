#include <window.hpp>

Window::Window(const char *title, int x, int y, int width, int height, int flags) {
	this->title = title;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->flags = flags;
}

Window::~Window() {

};

void Window::init() {
	if (SDL_VideoInit(NULL) == 0) {
		std::cout << "SDL2 video subsystem initialized successfully" << std::endl;
		
		window = SDL_CreateWindow(this->title, this->x, this->y, this->width, this->height, this->flags);
		if (window) {
			std::cout << "window created" << std::endl;
		}
	} else {
		std::cout << "SDL2 video subsytem failed to initialize" << std::endl;
	}
}

void Window::destroy() {
	SDL_DestroyWindow(window);
	std::cout << "window destroyed" << std::endl;
}