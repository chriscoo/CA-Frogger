/**
@file MenuState
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "MenuState.h"
#include "Utility.h"
#include "TextureHolder.h"
#include "FontHolder.h"
#include "MusicPlayer.h"

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/View.hpp"

namespace GEX {



	MenuState::MenuState(StateStack & stack, Context context) : State(stack, context), _options(), _optionsIndex(0)
	{
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::TitleScreen);
		sf::Font& font = FontHolder::getInstance().get(FontID::Main);

		_backgroundSprite.setTexture(texture);

		sf::Text playOption;
		playOption.setFont(font);
		playOption.setString("PLAY");
		playOption.setOutlineThickness(1);
		centerOrigin(playOption);
		playOption.setPosition(context.window->getView().getSize() / 2.f);
		_options.push_back(playOption);

		sf::Text exitOption;
		exitOption.setFont(font);
		exitOption.setString("EXIT");
		exitOption.setOutlineThickness(1);
		centerOrigin(exitOption);
		exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
		_options.push_back(exitOption);

		//context.music->play(MusicID::MenuTheme);

		updateOptionText();
	}
	
	void MenuState::draw()
	{
		sf::RenderWindow& window = *getContext().window;

		window.setView(window.getDefaultView());
		window.draw(_backgroundSprite);

		for (const sf::Text& text : _options)
			window.draw(text);
	}

	bool MenuState::update(sf::Time dt)
	{
		return true;
	}

	bool MenuState::handleEvent(const sf::Event & event)
	{
		if (event.type != sf::Event::KeyPressed)
			return false;

		if (event.key.code == sf::Keyboard::Return)
		{
			if (_optionsIndex == Play)
			{
				requestStackPop();
				requestStackPush(StateID::Game);

			}
			else if (_optionsIndex == Exit)
			{
				requestStackPop(); //game will close since there will be nothing left on the stack

			}

		}

		else if (event.key.code == sf::Keyboard::Up)
		{

			if (_optionsIndex > 0)
				_optionsIndex--;
			else
				_optionsIndex = 0;
				//_optionsIndex = _options.size()-1;

			updateOptionText();
		}

		else if (event.key.code == sf::Keyboard::Down)
		{

			if (_optionsIndex < _options.size()-1)
				_optionsIndex++;
			else
				_optionsIndex = 0;

			updateOptionText();
		}
		return false;
		
	}

	void MenuState::updateOptionText()
	{
		if (_options.empty())
			return;

		for (sf::Text& text : _options)
			text.setFillColor(sf::Color::White);

		_options[_optionsIndex].setFillColor(sf::Color::Red);
	}

}