#include "Frog.h"
#include "TextureHolder.h"
#include "TextNode.h"
#include "DataTables.h"
#include "Utility.h"
#include <iostream>
#include <cassert>
#include "SoundNode.h"
//#include "JsonFrameParser.hpp"

namespace GEX {
	Frog::Frog() : Entity(1), _player(TextureHolder::getInstance().get(TextureID::Atlas)), _directionIndex(0), _travelDistance(0), _isMarkedForRemoval(false), _playedMovementSound(true), _playedDeathSound(true), _state()
	{
		sf::IntRect rect(62,0,30,22);
		_player.setTextureRect(rect);
		centerOrigin(_player);
		

	}
	unsigned int Frog::getCategory() const
	{
		return Category::Frog;
	}
	void Frog::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_player, state);
	}
	void Frog::updateCurrent(sf::Time dt, CommandQueue & commands)
	{
		
		Entity::updateCurrent(dt, commands);
	}

	bool Frog::isMarkedForRemoval() const
	{
		return false;
	}

	float Frog::getMaxSpeed() const
	{
		return 40.f;
	}

	sf::FloatRect Frog::getBoundingRect() const
	{
		return sf::FloatRect();
	}

}