/**
@file PlayerControl
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/
#pragma once
#include "SFML/Graphics.hpp"
#include "CommandQueue.h"
#include <map>
namespace GEX {

	enum class missionStatus {
		Active, 
		Sucess,
		Fail


	};
	class PlayerControl
	{
		enum class Action {
			moveLeft,
			moveRight,
			moveUp,
			moveDown,
			fireBullet,
			fireMissle
		};

	public:
											PlayerControl();
		
		void								handleEvent(const sf::Event& events, CommandQueue& commands);
		void								handleRealTimeInput(CommandQueue& commands);
		void								setMissionStatus(missionStatus status);
		missionStatus						getMissionStatus() const;

	private:
		void								initalizeKeyBindings();
		void								initalizeActionBindings();
		bool								isRealTimeAction(Action action);
	private:
		std::map<sf::Keyboard::Key, Action> _keyBindings;
		std::map<Action, Command>			_actionBindings;
		missionStatus						_missionStatus;
	};

}