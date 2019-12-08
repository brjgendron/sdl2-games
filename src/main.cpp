#include <window.hpp>

int main(int argc, char *argv[]) {
	Window *window = new Window("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
	window->init();

	while(window->isRunning()) {
		window->handleEvents();
		window->update();
		window->render();
	}

	window->destroy();
	SDL_Quit();

	return 0;
}