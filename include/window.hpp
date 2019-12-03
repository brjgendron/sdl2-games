#ifndef window_hpp
#define window_hpp

#include <iostream>
#include <SDL2/SDL_video.h>

class Window {
private:
	const char *title;
	int x;
	int y;
	int width;
	int height;
	int flags;

	SDL_Window *window;
public:
	Window(const char *title, int x, int y, int width, int height, int flags = -1);
	~Window();

	void init();
	void destroy();
};

#endif /* window_hpp */