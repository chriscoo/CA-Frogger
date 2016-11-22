/**
@file Particle
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/


#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\System.hpp"
namespace GEX {

	struct Particle
	{
		enum class Type {
			Propellant,
			Smoke

		};

		sf::Vector2f position;
		sf::Color color;
		sf::Time lifeTime;

	};
	

}