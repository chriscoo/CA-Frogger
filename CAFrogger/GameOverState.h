/**
@file GameoverState
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
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"

namespace GEX {
	class GameOverState : public State
	{
	public:
		GameOverState(StateStack& stack, Context context);


		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);

	private:
		sf::Text _GameOverText;
		sf::Time _elapsedTime;
	};

}