/**
@file Utility
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "Utility.h"
#include <SFML\Graphics\Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <random>
#include <cmath>


namespace GEX {


	namespace {
		std::default_random_engine createEngine(){
			auto seed = static_cast<unsigned long>(std::time(nullptr));

			return std::default_random_engine(seed);
		}
		auto randomengine = createEngine();

	}
	int randomInt(int max)
	{
		std::uniform_int_distribution<> distr(0, max - 1);
		return distr(randomengine);
	
	}
	void centerOrigin(sf::Sprite& sprite) { //centers the origin of sprites
		sf::FloatRect bounds = sprite.getLocalBounds();
		sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}



	void centerOrigin(sf::Text& text) { //centers the origin of text nodes
		sf::FloatRect bounds = text.getLocalBounds();
		text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	void centerOrigin(Animation& anim)
	{
		sf::FloatRect bounds = anim.getLocalBounds();
		anim.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	float length(sf::Vector2f vector)
	{
		return sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	sf::Vector2f unitVector(sf::Vector2f vector)
	{
		assert(vector != sf::Vector2f(0.f, 0.f));
		return vector / length(vector);
	}



}