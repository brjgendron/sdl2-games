#include <renderer.hpp>

Renderer::Renderer(SDL_Window *window, int index /* = 0 */, int flags /* = -1 */) {
	this->window = window;
	this->index = index;
	this->flags = flags;
}

Renderer::~Renderer() {

}

void Renderer::init() {
	if (SDL_VideoInit(NULL) == 0) {
		renderer = SDL_CreateRenderer(this->window, this->index, this->flags);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
		std::cout << "renderer created for " << this->window << std::endl;
	}
}

	void Renderer::destroy() {
	SDL_DestroyRenderer(renderer);
	std::cout << "renderer destroyed" << std::endl;
}