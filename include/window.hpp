#ifndef window_hpp
#define window_hpp

#include <SDL2/SDL.h>

class Window {
	public:
		Window(const char *title, int x, int y, int width, int height);
		~Window();

		void init();
		void handleEvents();
		void update();
		void render();
		void destroy();

		bool isRunning() {
			return running;
		}

	private:
		const char *title;
		int width;
		int height;
		int x;
		int y;
		bool running;
		SDL_Window *window;
		SDL_Renderer *renderer;
};

#endif /* window_hpp */