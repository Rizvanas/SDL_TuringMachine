#include "MyWindow.h"
#include <sstream>

MyWindow::MyWindow()
	: myWindow{ nullptr }, width{ 0 }, height{ 0 },
	mouseFocus{ false }, keyboardFocus{ false },
	fullScreen{ false }, minimized{ false } {
}

bool MyWindow::init() {
	myWindow = SDL_CreateWindow("Turing Machine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!myWindow) {
		return false;
	}

	myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!myRenderer) {
		SDL_DestroyWindow(myWindow);
		myWindow = nullptr;
		return false;
	}
	SDL_SetRenderDrawColor(myRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	mouseFocus = true;
	keyboardFocus = true;
	windowID = SDL_GetWindowID(myWindow);

	return true;
}

void MyWindow::handleEvent(SDL_Event& ev) {
	if (ev.type == SDL_WINDOWEVENT && ev.window.windowID == windowID) {
		bool updateCaption{ false };

		switch (ev.window.event) {

		case SDL_WINDOWEVENT_SHOWN:
			shown = true;
			break;

		case SDL_WINDOWEVENT_HIDDEN:
			shown = false;
			break;

		case SDL_WINDOWEVENT_RESIZED: 
			width = ev.window.data1;
			height = ev.window.data2;
			SDL_RenderPresent(myRenderer);
			break;

		case SDL_WINDOWEVENT_EXPOSED: 
			SDL_RenderPresent(myRenderer);
			break;

		case SDL_WINDOWEVENT_ENTER: 
			mouseFocus = true, updateCaption = true;
			break;

		case SDL_WINDOWEVENT_LEAVE: 
			mouseFocus = false, updateCaption = true;
			break;

		case SDL_WINDOWEVENT_FOCUS_GAINED:
			keyboardFocus = true, updateCaption = true;
			break;

		case SDL_WINDOWEVENT_FOCUS_LOST: 
			keyboardFocus = false, updateCaption = true;
			break;

		case SDL_WINDOWEVENT_MINIMIZED: 
			minimized = true;
			break;

		case SDL_WINDOWEVENT_MAXIMIZED: 
			minimized = false;
			break;

		case SDL_WINDOWEVENT_RESTORED: 
			minimized = false;
			break;

		case SDL_WINDOWEVENT_CLOSE: 
			SDL_HideWindow(myWindow);
			break;

		default: 
			break;
		}

		if (updateCaption) {
			std::stringstream caption{};
			caption << "Turing Machine: windowID -> " << windowID << " mouseFocus -> " << (mouseFocus ? "On" : "Off") << " keyboardFocus -> " << (keyboardFocus ? "On" : "Off");
			SDL_SetWindowTitle(myWindow, caption.str().c_str());
		}
	}
}

SDL_Renderer* MyWindow::getRenderer() {
	return myRenderer;
}

void MyWindow::focus() {
	if (!shown) {
		SDL_ShowWindow(myWindow);
	}
	SDL_RaiseWindow(myWindow);
}

void MyWindow::render() {
	if (!minimized) {
		SDL_SetRenderDrawColor(myRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(myRenderer);
	}
}

bool MyWindow::hasMouseFocus() {
	return mouseFocus;
}

bool MyWindow::hasKeyboardFocus() {
	return keyboardFocus;
}

bool MyWindow::isMinimized() {
	return minimized;
}

bool MyWindow::isShown() {
	return shown;
}

int MyWindow::getWidth() {
	return width;
}

int MyWindow::getHeight() {
	return height;
}

void MyWindow::free() {

	SDL_DestroyRenderer(myRenderer);
	SDL_DestroyWindow(myWindow);

	myWindow = nullptr;
	myRenderer = nullptr;
}

MyWindow::~MyWindow() {
}
