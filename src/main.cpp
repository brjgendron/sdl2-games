#include <window.hpp>


int main(int argc, char *argv[]) {
	Window *w = new Window("window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	w->init();
	w->destroy();

	return 0;
}