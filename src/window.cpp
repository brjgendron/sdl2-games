#include <iostream>
#include <window.hpp>

Window::Window(const char *title, int x, int y, int width, int height) {
	this->title = title;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Window::~Window() {}


int Window::windowInit() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL2 video subsystem failed to initialize: " << SDL_GetError() << std::endl;
		running = false;
		return -1;
	} else {
		running = true;
		std::cout << "SDL2 video subsystem initialized successfully" << std::endl;
	}

	// set opengl context version to opengl 3.3, disable deprecated functions
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// create an SDL window with an opengl context
	window = SDL_CreateWindow(this->title, this->x, this->y, this->width, this->height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!window) {
		std::cout << "failed to create window: " << SDL_GetError() << std::endl;
		running = false;
		return -1;
	} else {
		std::cout << "window created successfully" << std::endl;
		running = true;
	}

	glContext = SDL_GL_CreateContext(window);
	if (!glContext) {
		std::cout << "failed to create opengl context: " << SDL_GetError() << std::endl;
		running = false;
		return -1;
	} else {
		running = true;
		std::cout << "created opengl context" << std::endl;
	}

	// initialize GLEW
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK) {
		std::cout << "error initializing GLEW: " << glewGetErrorString(glewError) << std::endl;
		running = false;
		return -1;
	} else {
		std::cout << "GLEW initialized" << std::endl;
	}

	gWindowInit();

	return 0;
}

int Window::gWindowInit() {
	glViewport(0, 0, this->width, this->height);

	const GLchar *vertexShaderSource[] = {
		"#version 330 core\nlayout (location = 0) in vec3 vPos; void main() { gl_Position = vec4(vPos.x, vPos.y, vPos.z, 1.0); }"
	};

	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint vertexShaderCompiled = GL_FALSE;
	GLchar compileLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexShaderCompiled);
	if (vertexShaderCompiled != GL_TRUE) {
		glGetShaderInfoLog(vertexShader, 512, NULL, compileLog);
		std::cout << "failed to compile vertex shader " << vertexShader << std::endl << compileLog << std::endl;
		return -1;
	} else {
		std::cout << "compiled vertex shader " << vertexShader << std::endl;
	}

	const GLchar *fragmentShaderSource[] = {
		"#version 330 core\nout vec4 fragmentColor; void main() { fragmentColor = vec4(0.5f, 0.3f, 0.9f, 1.0f); }" 
	};

	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	GLint fragmentShaderCompiled = GL_FALSE;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentShaderCompiled);
	if (fragmentShaderCompiled != GL_TRUE) {
		std::cout << "failed to compiled fragment shader " << fragmentShader << std::endl;
		return -1;
	} else {
		std::cout << "compiled fragment shader " << fragmentShader << std::endl;
	}

	gProgramID = glCreateProgram();
	glAttachShader(gProgramID, vertexShader);
	glAttachShader(gProgramID, fragmentShader);
	glLinkProgram(gProgramID);

	GLint programLinked = GL_FALSE;
	glGetProgramiv(gProgramID, GL_LINK_STATUS, &programLinked);
	if (programLinked != GL_TRUE) {
		std::cout << "failed to link program " << gProgramID << std::endl;
		return -1;
	} else {
		std::cout << "linked program " << gProgramID << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLfloat vData[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &gVAO);
	glGenBuffers(1, &gVBO);
	glBindVertexArray(gVAO);

	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vData), vData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}

void Window::handleEvents() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			running = false;
			break;

		default:
			break;
		}
	}
}

void Window::update() {

}

void Window::render() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(gProgramID);
	glBindVertexArray(gVAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	SDL_GL_SwapWindow(this->window);
}

void Window::destroy() {
	glDeleteVertexArrays(1, &gVAO);
	glDeleteBuffers(1, &gVBO);

	SDL_DestroyWindow(window);
	std::cout << "window destroyed" << std::endl;

	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	std::cout << "SDL2 video subsystem quit" << std::endl;
}
