#include <iostream>

#include <GL/glew.h>
#include <SDL2/SDL.h>

int main (int argc, char *argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window *gWindow = SDL_CreateWindow("opengl window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	
	SDL_GLContext gContext = SDL_GL_CreateContext(gWindow);
	if (!gContext) {
			std::cout << "failed to create opengl context: " << SDL_GetError() << std::endl;
			return -1;
		} else {
			std::cout << "created opengl context" << std::endl;
		}

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		std::cout << "error initializing GLEW: " << glewGetErrorString(glewError) << std::endl;
		return -1;
	} else {
		std::cout << "GLEW initialized" << std::endl;
	}

	while (true) {
		SDL_GL_SwapWindow(gWindow);
		glClearColor(0.0f, 0.0f, 0.0f, 255.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}


	return 0;
}