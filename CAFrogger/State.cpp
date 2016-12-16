/**
@file State
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "State.h"
#include "stateStack.h"

namespace GEX {
	State::Context::Context(sf::RenderWindow& window, PlayerControl& player) : window(&window), player(&player) {}

	State::State(StateStack& stack, Context context) : _stack(&stack), _context(context) {}

	State::~State()
	{
	}

	void State::requestStackPush(StateID stateID) { _stack->pushState(stateID); } //puts a state onto the stack
	void State::requestStackPop() { _stack->popState(); } //takes one off the stack
	void State::requestStateClear() { _stack->clearStates(); } //clears the stack

	State::Context State::getContext() const { return _context; }
	
}
