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

#include "TextureHolder.h"
#include <iostream>
#include <cassert>
#include <memory>

namespace GEX {
	TextureHolder* TextureHolder::_instance = nullptr;
	TextureHolder::TextureHolder()
	{
		
	}


	



	TextureHolder & TextureHolder::getInstance()
	{
		if (!TextureHolder::_instance) // lazy instantiation only constructs when called for
			TextureHolder::_instance = new TextureHolder();

		return *TextureHolder::_instance;
	}

	void TextureHolder::load(TextureID id,const std::string & path) //loads the textures from the given path and sets their id
	{
		std::unique_ptr<sf::Texture> texture(new sf::Texture);

		if (!texture->loadFromFile(path))
		{
			std::cout << "load failed!" << std::endl;
			assert(0);
		}
		auto rc = _textures.insert(std::make_pair(id, std::move(texture)));
		if (!rc.second)
			assert(0);
	}

	sf::Texture& GEX::TextureHolder::get(TextureID tID) // gets the texture hooked to the id passed in
	{

		auto found = _textures.find(tID);
		assert(found != _textures.end());

		return *found->second;
	}
}