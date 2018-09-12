#ifndef _MY_WINDOW_H_
#define _MY_WINDOW_H_
#include <SDL.h>
#include<SDL_image.h>

class MyWindow {
private:
	SDL_Window* myWindow;
	SDL_Renderer* myRenderer;
	int width, height;
	int windowID;
	bool mouseFocus, keyboardFocus;
	bool fullScreen;
	bool minimized;
	bool shown;
public:
	static const int SCREEN_WIDTH{ 640 };
	static const int SCREEN_HEIGHT{ 480 };
	MyWindow();
	~MyWindow();
	bool init();
	void handleEvent(SDL_Event& ev);
	SDL_Renderer* getRenderer();
	void focus();
	void render();
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
	bool isShown();
	int getWidth();
	int getHeight();
	void free();
};

#endif // !_MY_WINDOW_H_



