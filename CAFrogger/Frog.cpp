/**
@file Frog
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

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
		return isDestroyed();
	}

	float Frog::getMaxSpeed() const
	{
		return 40.f;
	}

	sf::FloatRect Frog::getBoundingRect() const
	{
			return getWorldTrandform().transformRect(_player.getGlobalBounds());		
	}

}