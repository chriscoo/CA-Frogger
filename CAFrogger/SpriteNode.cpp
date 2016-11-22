/**
@file SpriteNode
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "SpriteNode.h"

namespace GEX {

	SpriteNode::SpriteNode(sf::Texture& texture, sf::IntRect rect) : _sprite(texture, rect)
	{
		
	}

	SpriteNode::SpriteNode(sf::Texture& texture) : _sprite(texture)
	{
		
	}

	SpriteNode::~SpriteNode()
	{
	}
	void SpriteNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}
}