#pragma once
struct Instruction {
	int currentState;
	char currentSymbol;
	char newSymbol;
	char direction;
	int newState;
};
