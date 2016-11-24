/**
@file TextureHolder
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/
#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include <map>
namespace GEX
{
	enum class TextureID {AIRPLANE=0, RAPTOR, AVENGER, MISSLE, BULLET, DESERT, PARTICLE, TitleScreen, GexLogo, FireRate, FireSpread, HealthRefill, MissileRefill, Explosion, FinishLine, Background, Frog
	};

	class TextureHolder
	{
	public:
		static TextureHolder& getInstance();
		
		
		
		void load(TextureID id, const std::string& path);
		sf::Texture& get(TextureID);
		
		
	private:
		TextureHolder();
		static TextureHolder* _instance;
		
		std::map<TextureID, std::unique_ptr<sf::Texture>> _textures;
	};
}
