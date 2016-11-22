/**
@file DemoNode.h
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
#include <string>
#include <iostream>
namespace GEX {
	class DemoNode : public Entity
	{
	public:
		DemoNode(std::string name) : _name(name) {};
		virtual ~DemoNode() {};
	private:
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override 
		{
			std::cout << "draw " << _name << std::endl;
		}
	private:
		std::string _name;
	};

}