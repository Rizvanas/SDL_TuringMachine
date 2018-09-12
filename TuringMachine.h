#pragma once
#include <SDL.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "MyTexture.h"
#include "Instruction.h"

class TuringMachine {
private:
	int state;
	int headPos;
	std::string tape;
	std::vector<Instruction> instructions;
	bool machineIsRunning;
	void moveHead(const Instruction &inst);
	void changeTape(std::string &filePath);
	bool chosen;
public:
	static const char HEAD_DIRECTION_LEFT = 'L';
	static const char HEAD_DIRECTION_RIGHT = 'R';
	std::string TAPE_1{ "1.txt" };
	std::string TAPE_2{ "2.txt" };
	std::string TAPE_3{ "3.txt" };
	std::string TAPE_4{ "4.txt" };
	
	TuringMachine(std::string &filePath);
	~TuringMachine();
	void readData(std::string &filePath);
	void handleEvent(SDL_Event &ev);
	void render(SDL_Renderer *renderer, MyTexture &leftTape, MyTexture &centerTape, MyTexture &rightTape, int winWidth, int winHeight, int yPos);
	bool runInstructions();
	int getState();
	int getHeadPos();
	std::string &getTape();
	std::vector<Instruction> &getInstructions();
	bool isMachineRunning();
	void setChosen(bool value);
	bool isChosen();
};

