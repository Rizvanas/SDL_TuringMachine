#ifndef _MY_TEXTURE_H_
#define _MY_TEXTURE_H_
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>

class MyTexture {
private:
	SDL_Texture* gTexture;
	int width, height;
	void destroy();
	int x, y;
public:
	MyTexture();
	~MyTexture();
	void setColor(Uint8 r, Uint8 g, Uint8 b);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	bool loadFromFile(SDL_Renderer* gRenderer, std::string path);
#ifdef _SDL_TTF_H
	bool loadFromRenderedText(SDL_Renderer* gRenderer, TTF_Font* textFont, std::string text, SDL_Color textColor);
#endif // _SDL_TTF_H
	void render(SDL_Renderer* gRenderer, int x = 0, int y = 0, SDL_Rect* partOfTexture = nullptr,
		double angle = 0.0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth();
	int getHeight();
	int getX();
	int getY();
};

#endif // !_MY_TEXTURE_H_



