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
#include "Frog.h"
#include "Category.h"

namespace GEX {
	struct FrogMover{ //to move the aircraftk
	
		FrogMover(float vx, float vy, float rotation) : velocity(vx, vy), rotation(rotation){}
		void operator() (Frog& frog, sf::Time) const {
			frog.setPosition(frog.getPosition().x + velocity.x, frog.getPosition().y + velocity.y);
			frog.setRotation(rotation);
		}

		sf::Vector2f velocity;
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
		return false;
	}
	void PlayerControl::initalizeKeyBindings()
	{
		
		_keyBindings[sf::Keyboard::Left] = Action::moveLeft;
		_keyBindings[sf::Keyboard::Right] = Action::moveRight;
		_keyBindings[sf::Keyboard::Up] = Action::moveUp;
		_keyBindings[sf::Keyboard::Down] = Action::moveDown;
		//_keyBindings[sf::Keyboard::Space]= Action::fireBullet;
		//_keyBindings[sf::Keyboard::RControl] = Action::fireMissle;
	}

	void PlayerControl::initalizeActionBindings()
	{
		const float playerSpeed = 200.f;
		const float spinSpeed = 10.f;

		_actionBindings[Action::moveLeft].action = derivedAction<Frog>(FrogMover(-40, 0, 270));
		_actionBindings[Action::moveRight].action = derivedAction<Frog>(FrogMover(40, 0, 90));
		_actionBindings[Action::moveUp].action = derivedAction<Frog>(FrogMover(0, -40, 0));
		_actionBindings[Action::moveDown].action = derivedAction<Frog>(FrogMover(0, 40, 180));
		//_actionBindings[Action::fireBullet].action = derivedAction<Plane>([](Plane& a, sf::Time& dt) {return a.fireBullet(); });
		//_actionBindings[Action::fireMissle].action = derivedAction<Plane>([](Plane& a, sf::Time& dt) {return a.fireMissle(); });


		for (auto& pair : _actionBindings)
			pair.second.category = Category::Frog;
	}



}

