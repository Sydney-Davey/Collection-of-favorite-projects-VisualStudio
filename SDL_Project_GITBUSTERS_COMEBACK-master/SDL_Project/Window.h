#ifndef WINDOW_H
#define WINDOW_H

class Window {
private:
	struct SDL_Window* window;   
	int width, height;
	
public:
	Window(int width_, int height_ );
	~Window();
	bool OnCreate();
	void OnDestroy();
	SDL_Window* GetSDL_Window();
};

#endif // ! WINDOW_H
