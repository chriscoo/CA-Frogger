/**
@file GexState
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#pragma once
#include "State.h"
#include "SFML\Graphics\Sprite.hpp"
#include "SFML\Graphics\Text.hpp"

#include "CommandQueue.h"

namespace GEX {
	class GexState : public State
	{
	public:
		GexState(StateStack& stack, Context context);


		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);


	private:
		sf::Sprite	_backgroundSprite;
		sf::Sprite	_logo;
		sf::Text	_pausedText;
		sf::Text	_instructionText;

	};
}

