/**
@file StateStack
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "StateStack.h"
#include <cassert>

namespace GEX {

	GEX::StateStack::StateStack(State::Context context) : _stack(), _pendingList(), _context(context), _factories()
	{
	}


	void StateStack::update(sf::Time dt)
	{
		// Iterate from top to bottom, stop as soon as update() returns false
		for (auto itr = _stack.rbegin(); itr != _stack.rend(); ++itr)
		{
			if (!(*itr)->update(dt))
				break;
		}

		applyPendingChanges();
	}

	void StateStack::draw()
	{
		// Draw all active states from bottom to top
		for (State::Ptr& state : _stack)
			state->draw();
	}

	void StateStack::handleEvent(const sf::Event & event)
	{
		// Iterate from top to bottom, stop as soon as handleEvent() returns false
		for (auto itr = _stack.rbegin(); itr != _stack.rend(); ++itr)
		{
			if (!(*itr)->handleEvent(event))
				break;
		}
		applyPendingChanges();

	}

	void StateStack::pushState(StateID stateID)
	{
		_pendingList.push_back(PendingChange(Push, stateID));
	}

	void StateStack::popState()
	{
		_pendingList.push_back(PendingChange(Pop));
	}

	void StateStack::clearStates()
	{
		_pendingList.push_back(PendingChange(Clear));
	}

	bool StateStack::isEmpty() const
	{
		return _stack.empty();
	}

	State::Ptr StateStack::createState(StateID stateID)
	{
		auto found = _factories.find(stateID); //creates the state passed in
		assert(found != _factories.end());

		return found->second();
	}

	void StateStack::applyPendingChanges()
	{
		//does what ever actions are on the pending list
		for (PendingChange change : _pendingList)
		{
			switch (change.action)
			{
			case Push:
				_stack.push_back(createState(change.stateID));
				break;
			case Pop:
				_stack.pop_back();
				break;
			case Clear:
				_stack.clear();
				break;
			}
		}
		_pendingList.clear();
	}

	StateStack::PendingChange::PendingChange(Action action, StateID stateID) : action(action), stateID(stateID)
	{
	}

}
