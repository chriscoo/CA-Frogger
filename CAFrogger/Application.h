/** 
@file Application.h
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/
#pragma once
#include "PlayerControl.h"
#include "StateStack.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
namespace GEX {
	class Application
	{
	public:
		Application();
		void run();


	private:

		void processInputs(); //real time events(movement)
		void update(sf::Time dt);
		void render();
		void updateStats(sf::Time dt);
		void registerStates();


	private:
		static const sf::Time timePerFrame;

		sf::RenderWindow	_window;


		PlayerControl		_player;
		StateStack _stateStack;
		MusicPlayer _music;
		SoundPlayer _soundPlayer;

		sf::Font _font;
		sf::Text _statText;

	};
}
