#ifndef renderer_hpp
#define renderer_hpp

#include <iostream>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>

class Renderer
{
private:
	int index;
	int flags;

	SDL_Window *window;
	SDL_Renderer *renderer;
public:
	Renderer(SDL_Window *window, int index = 0, int flags = -1);
	~Renderer();

	void init();
	void update();
	void render();
	void destroy();
};


#endif /* renderer_hpp */