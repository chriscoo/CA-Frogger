/**
@file Turtle
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "Turtle.h"
#include "TextureHolder.h"
#include "Utility.h"
#include "DataTables.h"


namespace GEX {


	const 	std::map<Turtle::Type, TurtleData> table = InitializeTurtleData();

	Turtle::Turtle(Type type) : Entity(1), _type(type), _sprite(TextureHolder::getInstance().get(TextureID::Atlas))
	{

		_sprite.setTextureRect(table.at(type).textureRect);
		setVelocity(table.at(type).speed, 0);
		centerOrigin(_sprite);

	}
	unsigned int Turtle::getCategory() const
	{
		return Category::Turtle;
	}

	void Turtle::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}
	void Turtle::updateCurrent(sf::Time dt, CommandQueue & commands)
	{
		sf::Vector2f velo = getVelocity();
		if (velo.x != 0.f && velo.y != 0.f)
			setVelocity(velo / std::sqrt(2.f));


		Entity::updateCurrent(dt, commands);
	}


	sf::FloatRect Turtle::getBoundingRect() const
	{
		return getWorldTrandform().transformRect(_sprite.getGlobalBounds());
	}


}
