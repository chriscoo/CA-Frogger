/**
@file GameState
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "GameState.h"
#include "Utility.h"
#include "MusicPlayer.h"

namespace GEX {




	GameState::GameState(StateStack & stack, Context context) : State(stack, context), _world(*context.window, *context.soundEffects), _player(*context.player) {} //context.music->play(MusicID::Missiontheme); 

	void GameState::draw()
	{
		_world.draw();
	}

	bool GameState::update(sf::Time dt)
	{
		_world.update(dt);


		//check for game over
		if (!_world.playerHasLives())
		{
			_player.setMissionStatus(missionStatus::Fail);
			requestStackPush(StateID::GameOver);
		}
		else if (_world.hasReachedFinish())
		{
			_player.setMissionStatus(missionStatus::Sucess);
			requestStackPush(StateID::GameOver);
		}
		CommandQueue& commands = _world.getCommandQueue();
		_player.handleRealTimeInput(commands);

		return true;
	}

	bool GameState::handleEvent(const sf::Event & event)
	{
		CommandQueue& command = _world.getCommandQueue();

		_player.handleEvent(event, command);

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
			requestStackPush(StateID::Pause);

		//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)
		//{
		//	requestStackPop();
		//	requestStackPush(StateID::Menu);
		//}

		//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::G)
		//	requestStackPush(StateID::Gex);

		return true;
	}


}
