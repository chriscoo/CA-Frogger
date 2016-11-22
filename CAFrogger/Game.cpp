#include "Game.h"
#include "TextureHolder.h"
#include "SceneNode.h"
#include "Plane.h"
#include <string>
#include "Category.h"
#include <iostream>
#include "Command.h"

namespace GEX {
	Game::Game() : _window(sf::VideoMode(1024, 640), "----GEX----"), _world(_window), _font(), _statText(), _player()
	{
		_font.loadFromFile("Media/Sansation.ttf");
		_statText.setFont(_font);
		_statText.setPosition(5.f, 5.f);
		_statText.setCharacterSize(15);
		_statText.setFillColor(sf::Color(255,0,0,255));
		_statText.setOutlineColor(sf::Color::Black);
		_statText.setOutlineThickness(1.f);
	}

	void Game::run()
	{
		const int FPS = 90;
		const sf::Time SPF = sf::seconds(1.f / FPS);
		sf::Clock clock;
		sf::Time sinceLastUpdate = sf::Time::Zero;

		while (_window.isOpen())
		{
		
			processInputs();
			sinceLastUpdate = clock.restart();
			while (sinceLastUpdate > SPF) {
				

				sinceLastUpdate -= SPF;
				
				processInputs();
				update(SPF);
			}
			update(sinceLastUpdate);

			render();
		}
	
	}
	
	void Game::processInputs()
	{

		CommandQueue& commands = _world.getCommandQueue();
		sf::Event events;
		while (_window.pollEvent(events))
		{
			_player.handleEvent(events, commands);

			if (events.type == sf::Event::Closed)
				_window.close();
		}
		
		_player.handleRealTimeInput(commands);

			
	}
	
	void Game::update(sf::Time deltaTime)
	{	
		_world.update(deltaTime);
		updateStats(deltaTime);
	}
	
	void Game::render()
	{

		_window.clear();
		_world.draw();

		_window.setView(_window.getDefaultView());
		_window.draw(_statText);
		
		_window.display();

	}
	
	void Game::updateStats(sf::Time dt)
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
	

}