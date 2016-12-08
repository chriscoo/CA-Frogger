/**
@file utility
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#pragma once
#include <cmath>
#include <cassert>
#include <SFML/System.hpp>
#include "Animation.h"
namespace sf {
	class Sprite;
	class Text;
}
namespace GEX {

		void centerOrigin(sf::Sprite& sprite);
		void centerOrigin(sf::Text& text);
		void centerOrigin(Animation& anim);

		int randomInt(int max);

		const float PI = 3.14159265f;
		inline float degreesToRadians(float degress) { return degress*PI / 180.f; }
		inline float radiansToDegress(float radians) { return radians * 180.f / PI; }
		inline float sin(float degress) { return std::sin(degreesToRadians(degress)); }
		inline float cos(float degress) { return std::cos(degreesToRadians(degress)); }
		inline float arctan2(float opp, float adj) {
			float result = atan2(opp, adj) * 180 / PI;
			return result;
		}
		float length(sf::Vector2f vector);
		sf::Vector2f unitVector(sf::Vector2f vector);

}
