/**
@file Application
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "Application.h"
#include "TextureHolder.h"
#include "Utility.h"
#include "State.h"
#include "StateIdentifiers.h"
#include "TitleState.h"
#include "PauseState.h"
#include "MenuState.h"
#include "GameState.h"
#include "GexState.h"
#include "GameOverState.h"
#include "FontHolder.h"

namespace GEX {
	const sf::Time Application::timePerFrame = sf::seconds(1.f / 60.f);

	Application::Application() : _window(sf::VideoMode(480, 600), "states", sf::Style::Close), _player(), _stateStack(State::Context(_window, _player, _music, _soundPlayer)), _statText()
	{
		_window.setKeyRepeatEnabled(false);

		FontHolder::getInstance().load(FontID::Main, "Media/Sansation.ttf");
		TextureHolder::getInstance().load(TextureID::TitleScreen, "Media/Textures/FroggerTitle.png");
		TextureHolder::getInstance().load(TextureID::Background, "Media/Textures/background.png");

		_statText.setFont(FontHolder::getInstance().get(FontID::Main));
		_statText.setPosition(5.f, 5.f);
		_statText.setCharacterSize(10u);

		registerStates();
		_stateStack.pushState(StateID::Title);
	}

	void Application::run()
	{
		sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;

		while (_window.isOpen())
		{
			sf::Time dt = clock.restart();
			timeSinceLastUpdate += dt;
			while (timeSinceLastUpdate > timePerFrame)
			{


				timeSinceLastUpdate -= timePerFrame;

				processInputs();
				update(timePerFrame);

				if (_stateStack.isEmpty())
					_window.close();
			}


			updateStats(dt);
			render();
		}
	}

	void GEX::Application::processInputs()
	{
		sf::Event event;
		while (_window.pollEvent(event))
		{
			_stateStack.handleEvent(event);

			if (event.type == sf::Event::Closed)
				_window.close();
		}
	}
	void Application::update(sf::Time dt)
	{
		_stateStack.update(dt);
	}
	void Application::render()
	{
		_window.clear();
		_stateStack.draw();

		_window.setView(_window.getDefaultView());

		_window.draw(_statText);

		_window.display();
	}
	void Application::updateStats(sf::Time dt)
	{

		static int numFrames = 0;
		static sf::Time timePassed = sf::Time::Zero;

		timePassed += dt;
		numFrames += 1;

		if (timePassed >= sf::seconds(1.f))
		{

			_statText.setString("FPS: " + std::to_string(numFrames) + "\n" + "Time / update = " + std::to_string(timePassed.asMicroseconds() / numFrames) + " us");

			numFrames = 0;
			timePassed -= sf::seconds(1.f);
		}


	}
	void Application::registerStates()
	{
		_stateStack.registerState<TitleState>(StateID::Title);
		_stateStack.registerState<MenuState>(StateID::Menu);
		_stateStack.registerState<GameState>(StateID::Game);
		_stateStack.registerState<PauseState>(StateID::Pause);
		_stateStack.registerState<GexState>(StateID::Gex);
		_stateStack.registerState<GameOverState>(StateID::GameOver);
	}
}


