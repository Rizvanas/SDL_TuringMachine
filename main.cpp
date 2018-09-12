#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "MyTexture.h"
#include "MyTimer.h"
#include "MyWindow.h"
#include "TuringMachine.h"

std::string WINDOW_TITLE{ "Turing Machine" };
std::string TTF_FONT_FILEPATH{ "OpenSans-Bold.ttf" };

std::string TAPE_1{ "1.txt" };
std::string TAPE_2{ "2.txt" };
std::string TAPE_3{ "3.txt" };
std::string TAPE_4{ "4.txt" };

SDL_Color textColorBlack = { 0, 0, 0, 255 };
SDL_Color textColorRed = { 255, 0, 0, 255 };
SDL_Color textColorGreen = { 0, 255, 0, 255 };

const int FONT_SIZE{ 32 };

MyWindow gWindow;
TTF_Font* gFont{ nullptr };

MyTexture leftOfTapeTexture;
MyTexture rightOfTapeTexture;
MyTexture centerOfTapeTexture;

bool init();
bool openTTF(std::string path, int textSize);
void close();

int main(int argc, char* argv[]) {

	if (init() && openTTF(TTF_FONT_FILEPATH, FONT_SIZE)) {

		TuringMachine machineT1(TAPE_1);
		TuringMachine machineT2(TAPE_2);
		TuringMachine machineT3(TAPE_3);
		TuringMachine machineT4(TAPE_4);

		std::vector<TuringMachine> machines;
		machines.push_back(machineT1);
		machines.push_back(machineT2);
		machines.push_back(machineT3);
		machines.push_back(machineT4);

		machines.at(0).setChosen(true);

		std::string leftPartOfTape;
		std::string rightPartOfTape;
		std::string centerOfTape;

		SDL_Event ev;

		bool run{ true };

		int frames{ 0 };
		while (run) {

			frames = 0;

			while (SDL_PollEvent(&ev) != 0) {
				if (ev.type == SDL_QUIT) {
					run = false;
				}

				if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_UP) {
					for (size_t i = 0; i < machines.size(); ++i) {
						if (machines.at(i).isChosen()) {
							machines.at(i).setChosen(false);
							if (i > 0) {
					     	machines.at(i - 1).setChosen(true);
							}
							if (i == 0){
								machines.back().setChosen(true);
							}
							break;
						}
					}
				}

				if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_DOWN) {
					for (size_t i = 0; i < machines.size(); ++i) {
						if (machines.at(i).isChosen()) {
							machines.at(i).setChosen(false);
							if (i < machines.size() - 1) {
								machines.at(i + 1).setChosen(true);
							}
							else if (i == machines.size() - 1) {
								machines.front().setChosen(true);
							}
							break;
						}
					}
				}

				for (auto &machine : machines) {
					if (machine.isChosen()) {
						machine.handleEvent(ev);
						break;
					}
				}
				gWindow.handleEvent(ev);
			}

			for (auto &machine : machines) {
				if (machine.isMachineRunning()) {
					machine.runInstructions();
				}
			}
			
			gWindow.render();

			int yPos{ 64 };
			SDL_Rect chosenOneContour;

			for (auto &machine : machines) {
			
				leftPartOfTape = machine.getTape().substr(0, machine.getHeadPos());
				centerOfTape = machine.getTape()[machine.getHeadPos()];
				rightPartOfTape = machine.getTape().substr(machine.getHeadPos() + 1, machine.getTape().length());

				leftOfTapeTexture.loadFromRenderedText(gWindow.getRenderer(), gFont, leftPartOfTape.c_str(), textColorBlack);
				centerOfTapeTexture.loadFromRenderedText(gWindow.getRenderer(), gFont, centerOfTape.c_str(), textColorRed);
				rightOfTapeTexture.loadFromRenderedText(gWindow.getRenderer(), gFont, rightPartOfTape.c_str(), textColorBlack);


				machine.render(gWindow.getRenderer(), leftOfTapeTexture, centerOfTapeTexture, rightOfTapeTexture,
					gWindow.getWidth(), gWindow.getHeight(), yPos);

				if (machine.isChosen()) {
					int totalWidth = leftOfTapeTexture.getWidth() + centerOfTapeTexture.getWidth() + rightOfTapeTexture.getWidth();
					chosenOneContour = { leftOfTapeTexture.getX(), leftOfTapeTexture.getY(), totalWidth, leftOfTapeTexture.getHeight() };
					SDL_SetRenderDrawColor(gWindow.getRenderer(), 255, 0, 0, 255);
					SDL_RenderDrawRect(gWindow.getRenderer(), &chosenOneContour);
				}

				yPos += gWindow.getHeight() / 4;
			}
			SDL_RenderPresent(gWindow.getRenderer());
		}
	}
	close();
	return 0;
}

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	if (!gWindow.init()) {
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		return false;
	}

	if (TTF_Init() == -1) {
		return false;
	}

	return true;
}

bool openTTF(std::string path, int textSize) {
	gFont = TTF_OpenFont(path.c_str(), textSize);
	return gFont;
}

void close() {
	TTF_CloseFont(gFont);
	gWindow.free();

	gFont = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}