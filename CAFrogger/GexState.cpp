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

#include "GexState.h"
#include "Utility.h"
#include "TextureHolder.h"
#include "FontHolder.h"
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\View.hpp>


namespace GEX {



	GexState::GexState(StateStack & stack, Context context) : State(stack, context), _backgroundSprite(), _pausedText(), _instructionText(), _logo()
	{
		sf::Font& font = FontHolder::getInstance().get(FontID::Main);
		sf::Vector2f viewSize = context.window->getView().getSize();

		//makes the logo with a bit of alpha so its see through but still visible
		_logo.setTexture(TextureHolder::getInstance().get(TextureID::GexLogo));
		sf::Color color(255, 255, 255, 100);
		_logo.setColor(color);

		centerOrigin(_logo);
		_logo.setPosition(0.5f * viewSize.x, 0.5f * viewSize.y);
		_pausedText.setFont(font);
		_pausedText.setString("Game Paused");
		_pausedText.setCharacterSize(70);
		centerOrigin(_pausedText);
		_pausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);


		//sets the text that tells the user what to do
		_instructionText.setFont(font);
		_instructionText.setString("(Press BackSpace to return to the main menu) \n (Press G to return to the game)");
		centerOrigin(_instructionText);
		_instructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
	}

	void GexState::draw()
	{

		sf::RenderWindow& window = *getContext().window;
		window.setView(window.getDefaultView());

		//sets the red background
		sf::RectangleShape backgroundShape;
		backgroundShape.setFillColor(sf::Color(255, 0, 0, 100));
		backgroundShape.setSize(window.getView().getSize());

		//draws all the objects starting with the red, logo, then the text
		window.draw(backgroundShape);
		window.draw(_logo);
		window.draw(_pausedText);
		window.draw(_instructionText);
	}

	bool GexState::update(sf::Time dt)
	{
		return false;
	}

	bool GexState::handleEvent(const sf::Event & event)
	{
		if (event.type != sf::Event::KeyPressed)
			return false;

		if (event.key.code == sf::Keyboard::G)
		{
			requestStackPop();
		}
		if (event.key.code == sf::Keyboard::BackSpace)
		{
			requestStateClear();
			requestStackPush(StateID::Menu);

		}
		return false;
	}

}
