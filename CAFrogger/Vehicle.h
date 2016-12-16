/**
@file Vehicle
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#pragma once
#include "Entity.h"
namespace GEX
{
	class Vehicle : public Entity
	{
	public:
		enum class  Type { CarR, Tractor, CarL, RaceCar, Truck };
	public:
		Vehicle(Type type);
		virtual ~Vehicle() {};
		unsigned int	getCategory() const override;
		
		void			drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const; //draws the current instance of the car
		void			updateCurrent(sf::Time dt, CommandQueue& commands);
		
		sf::FloatRect	getBoundingRect() const override; //gets the hitbox
	

private:
	Type _type;
	sf::Sprite		_sprite;
	};
}