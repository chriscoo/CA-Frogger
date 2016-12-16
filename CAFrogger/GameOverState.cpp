/**
@file gameOverState
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "GameOverState.h"
#include "Utility.h"
#include "TextureHolder.h"
#include "FontHolder.h"
#include "PlayerControl.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

namespace GEX {

	GameOverState::GameOverState(StateStack & stack, Context context) : State(stack, context), _GameOverText(),_elapsedTime(sf::Time::Zero)
	{
		sf::Font& font = FontHolder::getInstance().get(FontID::Main);
		sf::Vector2f windowSize(480, 600);

		_GameOverText.setFont(font);
		if (context.player->getMissionStatus() == missionStatus::Fail)
		{
			_GameOverText.setString("GAME OVER");
		}
		_GameOverText.setCharacterSize(50);
		centerOrigin(_GameOverText);
		_GameOverText.setPosition(0.5f * windowSize.x, 0.5f * windowSize.y);
	}

	void GameOverState::draw()
	{
		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor(sf::Color(100, 0, 0, 150));
		backgroundShape.setSize(window.getView().getSize());

		window.draw(backgroundShape);
		window.draw(_GameOverText);
		
	}

	bool GameOverState::update(sf::Time dt)
	{
		_elapsedTime += dt;
		if (_elapsedTime > sf::seconds(3))
		{
			requestStateClear();
			requestStackPush(StateID::Menu);
		}
		return false;
	}

	bool GameOverState::handleEvent(const sf::Event & event)
	{
		
		return false;
	}




}
