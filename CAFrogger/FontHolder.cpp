/**
@file FontHolder
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "FontHolder.h"
#include<cassert>

namespace GEX {

	FontHolder* FontHolder::_instance = nullptr;
	FontHolder & GEX::FontHolder::getInstance()
	{
		if (!FontHolder::_instance)
			FontHolder::_instance = new FontHolder();

		return *FontHolder::_instance;
	}

	void FontHolder::load(FontID id, const std::string & path)
	{
		std::unique_ptr<sf::Font> texture(new sf::Font);
		if (!texture->loadFromFile(path))
			throw std::runtime_error("load failed - " + path);

		auto rc = _fonts.insert(std::make_pair(id, std::move(texture)));
		if (!rc.second)
			assert(0);
	}

	sf::Font & FontHolder::get(FontID id) const
	{
		auto found = _fonts.find(id);
		assert(found != _fonts.end());

		return *found->second;
	}

	
}