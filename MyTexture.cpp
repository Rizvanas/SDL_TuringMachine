#include "MyTexture.h"
#include <iostream>

MyTexture::MyTexture() 
	: gTexture{ nullptr }, width{ 0 }, height{ 0 }, x{ 0 }, y{ 0 } {
}

MyTexture::~MyTexture() {
	destroy();
}

void MyTexture::setColor(Uint8 r, Uint8 g, Uint8 b) {
	SDL_SetTextureColorMod(gTexture, r, g, b);
}

void MyTexture::setBlendMode(SDL_BlendMode blending) {
	SDL_SetTextureBlendMode(gTexture, blending);
}

void MyTexture::setAlpha(Uint8 alpha) {
	SDL_SetTextureAlphaMod(gTexture, alpha);
}

bool MyTexture::loadFromFile(SDL_Renderer* gRenderer, std::string path) {
	destroy();
	
	SDL_Surface* tempSurface{ nullptr };
	tempSurface = IMG_Load(path.c_str());

	SDL_Texture* newTexture{ nullptr };

	if (tempSurface) {

		SDL_SetColorKey(tempSurface, SDL_TRUE, SDL_MapRGB(tempSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);
		if (!newTexture) {
			std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
			return false;
		}

		width = tempSurface->w;
		height = tempSurface->h;

		SDL_FreeSurface(tempSurface);
		tempSurface = nullptr;

		gTexture = newTexture;

		return true;
	}
	return false;
}

#ifdef _SDL_TTF_H
bool MyTexture::loadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font* textFont, std::string text, SDL_Color textColor) {
	destroy();
	SDL_Surface* tempSurface = TTF_RenderText_Solid(textFont, text.c_str(), textColor);

	if (tempSurface) {
		gTexture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);

		width = tempSurface->w;
		height = tempSurface->h;

		SDL_FreeSurface(tempSurface);
		tempSurface = nullptr;
		return true;
	}
	return false;
}
#endif // _SDL_TTF_H

void MyTexture::render(SDL_Renderer* gRenderer, int x, int y, SDL_Rect* partOfTexture, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, width, height };
	if (partOfTexture) {
		renderQuad.w = partOfTexture->w;
		renderQuad.h = partOfTexture->h;
	}
	this->x = x;
	this->y = y;
	SDL_RenderCopyEx(gRenderer, gTexture, partOfTexture, &renderQuad, angle, center, flip);
}

int MyTexture::getWidth() {
	return width;
}

int MyTexture::getHeight() {
	return height;
}

int MyTexture::getX() {
	return x;
}

int MyTexture::getY() {
	return y;
}

void MyTexture::destroy() {
	if (gTexture) {
		width = 0;
		height = 0;
		SDL_DestroyTexture(gTexture);
		gTexture = nullptr;
	}
}
