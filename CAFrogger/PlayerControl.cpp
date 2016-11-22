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

#include "PlayerControl.h"
#include "Plane.h"
#include "Category.h"

namespace GEX {
	struct AircraftMover{ //to move the aircraftk
	
		AircraftMover(float vx, float vy) : velocity(vx, vy){}
		void operator() (Plane& plane, sf::Time) const {
			plane.accelerate(velocity);
		}

		sf::Vector2f velocity;
	
	};

	struct AircraftSpinner {//to spin the plane(not currently implemented)

		AircraftSpinner(float vSpeed) : rotation(vSpeed) {}
		void operator() (Plane& plane, sf::Time) const {
			plane.angularAccelerate(rotation);
		}

		float rotation;

	};
	PlayerControl::PlayerControl() : _missionStatus(missionStatus::Active)
	{
		
		initalizeKeyBindings();
		initalizeActionBindings();
	}

	void PlayerControl::handleEvent(const sf::Event& events, CommandQueue & commands)
	{
		if (events.type == sf::Event::KeyPressed)
		{
			auto found = _keyBindings.find(events.key.code);
			if (found != _keyBindings.end() && !isRealTimeAction(found->second))
				commands.push(_actionBindings[found->second]);
		}
		
	}

	void PlayerControl::handleRealTimeInput(CommandQueue& commands)
	{

		for (auto pair : _keyBindings)
		{
			if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
				commands.push(_actionBindings[pair.second]);



		}
	}
	void PlayerControl::setMissionStatus(missionStatus status)
	{
		_missionStatus = status;
	}
	missionStatus PlayerControl::getMissionStatus() const
	{
		return _missionStatus;
	}
	bool PlayerControl::isRealTimeAction(Action action)
	{
		switch (action)
		{
		case Action::moveDown:
		case Action::moveLeft:
		case Action::moveRight:
		case Action::moveUp:
			return true;
		default:
			return false;
			break;
		}
	}
	void PlayerControl::initalizeKeyBindings()
	{
		
		_keyBindings[sf::Keyboard::Left] = Action::moveLeft;
		_keyBindings[sf::Keyboard::Right] = Action::moveRight;
		_keyBindings[sf::Keyboard::Up] = Action::moveUp;
		_keyBindings[sf::Keyboard::Down] = Action::moveDown;
		_keyBindings[sf::Keyboard::Space]= Action::fireBullet;
		_keyBindings[sf::Keyboard::RControl] = Action::fireMissle;
	}

	void PlayerControl::initalizeActionBindings()
	{
		const float playerSpeed = 200.f;
		const float spinSpeed = 10.f;

		_actionBindings[Action::moveLeft].action = derivedAction<Plane>(AircraftMover(-playerSpeed, 0));
		_actionBindings[Action::moveRight].action = derivedAction<Plane>(AircraftMover(playerSpeed, 0));
		_actionBindings[Action::moveUp].action = derivedAction<Plane>(AircraftMover(0, -playerSpeed));
		_actionBindings[Action::moveDown].action = derivedAction<Plane>(AircraftMover(0, playerSpeed));
		_actionBindings[Action::fireBullet].action = derivedAction<Plane>([](Plane& a, sf::Time& dt) {return a.fireBullet(); });
		_actionBindings[Action::fireMissle].action = derivedAction<Plane>([](Plane& a, sf::Time& dt) {return a.fireMissle(); });


		for (auto& pair : _actionBindings)
			pair.second.category = Category::playerAircraft;
	}



}

