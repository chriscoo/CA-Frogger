/**
@file FontHolder.h
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#pragma once
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics.hpp"

#include <map>
#include <memory>
namespace GEX {

	enum class FontID{Main};

	class FontHolder
	{
	private:
		FontHolder() {};// must use getinstance()
	public:
		static FontHolder& getInstance();

		void load(FontID id, const std::string& path);
		sf::Font&  get(FontID) const;
	private:
		static FontHolder* _instance;

		std::map<FontID, std::unique_ptr<sf::Font>> _fonts;
	};
}

