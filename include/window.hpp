#ifndef window_hpp
#define window_hpp

#include <GL/glew.h>
// #include <GL/glu.h>
#include <SDL2/SDL.h>

class Window {
	public:
		Window(const char *title, int x, int y, int width, int height);
		~Window();

		int windowInit();
		void handleEvents();
		void update();
		void render();
		void destroy();

		bool isRunning() {
			return running;
		}

	private:
		int num = 0;
		const char *title;
		int width;
		int height;
		int x;
		int y;
		bool running = true;
		
		SDL_Window *window;
		SDL_GLContext glContext;

		GLuint gProgramID = 0,
		       gVBO = 0,
		       gVAO = 0;

		int gWindowInit();
};

#endif /* window_hpp */