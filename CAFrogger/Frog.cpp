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

namespace GEX {
	Frog::Frog() : Entity(1), _player(TextureHolder::getInstance().get(TextureID::Atlas)), _life(TextureHolder::getInstance().get(TextureID::Atlas), sf::IntRect(395,100,39,40)), _isMarkedForRemoval(false), _state(), _lives(3)
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
		_life.setPosition(440.f, 5.f);
		for (int i = 0; i < _lives; ++i)
		{
			target.draw(_life);
			_life.setPosition(_life.getPosition().x - 40.f, _life.getPosition().y);
		}
	}
	void Frog::updateCurrent(sf::Time dt, CommandQueue & commands)
	{
		
		Entity::updateCurrent(dt, commands);
	}

	void Frog::die()
	{
		_lives--;
	}

	bool Frog::isMarkedForRemoval() const
	{
		
		return isDestroyed();
	}


	sf::FloatRect Frog::getBoundingRect() const
	{
			return getWorldTrandform().transformRect(_player.getGlobalBounds());		
	}

	int Frog::getLives()
	{
		return _lives;
	}

}