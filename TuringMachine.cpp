#include "TuringMachine.h"

void TuringMachine::moveHead(const Instruction & inst) {
	if (inst.direction == HEAD_DIRECTION_LEFT) {
		headPos--;
	}
	else {
		headPos++;
	}
}

TuringMachine::TuringMachine(std::string &filePath)
	: state{ 0 }, headPos{ 0 }, machineIsRunning{ false }, chosen{ false } {
	readData(filePath);
}

TuringMachine::~TuringMachine() {
}

void TuringMachine::readData(std::string &filePath) {
	std::ifstream input(filePath.c_str());

	int tempCurrState{ 0 };
	int tempNewState{ 0 };
	char tempCurrSymbol{};
	char tempNewSymbol{};
	char tempDirection{};

	if (!input) {
		std::cerr << "Failed to open file." << std::endl;
	}
	else {
		input >> headPos;
		input >> tape;
		while (input >> tempCurrState >> tempCurrSymbol >> tempNewSymbol >> tempDirection >> tempNewState || !input.eof()) {
			if (input.fail()) {
				input.clear();
				std::string dummy;
				input >> dummy;
				tempNewState = -1;
			}
			Instruction  inst = { tempCurrState, tempCurrSymbol, tempNewSymbol,  tempDirection, tempNewState };
			instructions.push_back(inst);
		}
	}
	input.close();
}

void TuringMachine::changeTape(std::string &filePath) {
	instructions.clear();
	state = 0;
	readData(filePath);
}

void TuringMachine::handleEvent(SDL_Event &ev) {
	if (ev.type == SDL_KEYDOWN) {

		switch (ev.key.keysym.sym) {
		case SDLK_e:
			if (!machineIsRunning) {
				runInstructions();
			}
			break;

		case SDLK_s:
			if (!machineIsRunning) {
				machineIsRunning = true;
			}
			else {
				machineIsRunning = false;
			}
			break;

		case SDLK_1:
			changeTape(TAPE_1);
			machineIsRunning = false;
			break;

		case SDLK_2:
			changeTape(TAPE_2);
			machineIsRunning = false;
			break;

		case SDLK_3:
			changeTape(TAPE_3);
			machineIsRunning = false;
			break;

		case SDLK_4:
			changeTape(TAPE_4);
			machineIsRunning = false;
			break;

		default:
			break;
		}
	}
}

void TuringMachine::render(SDL_Renderer *renderer, MyTexture &leftTape, MyTexture &centerTape, MyTexture &rightTape, int winWidth, int winHeight, int yPos) {
	int totalWidth = leftTape.getWidth() + centerTape.getWidth() + rightTape.getWidth();
	int upToCenterWidth = totalWidth - leftTape.getWidth() * 2;
	int upToRightWidth = upToCenterWidth - centerTape.getWidth() * 2;
	
	leftTape.render(renderer, (winWidth - totalWidth) / 2, yPos);
	centerTape.render(renderer, (winWidth - upToCenterWidth) / 2, yPos);
	rightTape.render(renderer, (winWidth - upToRightWidth) / 2, yPos);
}

bool TuringMachine::runInstructions() {
	bool run{ true };

	for (const auto& inst : instructions) {
		if (state == inst.currentState && tape[headPos] == inst.currentSymbol) {
			tape[headPos] = inst.newSymbol;
			state = inst.newState;
			moveHead(inst);
			break;
		}

		if (state == -1) {
			run = false;
			break;
		}
	}
	return run;
}

int TuringMachine::getState() {
	return state;
}

int TuringMachine::getHeadPos() {
	return headPos;
}

std::string & TuringMachine::getTape() {
	return tape;
}

std::vector<Instruction>& TuringMachine::getInstructions() {
	return instructions;
}

bool TuringMachine::isMachineRunning() {
	return machineIsRunning;
}

void TuringMachine::setChosen(bool value) {
	chosen = value;
}

bool TuringMachine::isChosen() {
	return chosen;
}