#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <SDL2/SDL.h>

class Game {
	public:
		Game();
		~Game();

		void init(const char *title, int x, int y, int width, int height);

		void handleEvents();
		void update();
		void render();
		void destroy();

		bool running() {
			return isRunning;
		}
	private:
		bool isRunning;
		SDL_Window *window;
		SDL_Renderer *renderer;
};

#endif