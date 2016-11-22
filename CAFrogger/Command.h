/**
@file Command.h
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/
#pragma once
#include <cassert>
#include "SFML/System/Time.hpp"
#include <functional>
namespace GEX {
	class SceneNode;
	class Command
	{
	public:
		Command();
		std::function<void(SceneNode&, sf::Time)> action;
		unsigned int							  category;
	};

	template <typename GameObject, typename function>
	std::function<void(SceneNode&, sf::Time)>derivedAction(function fn)
	{
		return[=](SceneNode& node, sf::Time dt)
		{
			assert(dynamic_cast<GameObject*>(&node) != nullptr); //if it cant downcast to that it crashes
			//downcasting
			fn(static_cast<GameObject&>(node), dt);
		};//stuff
	}
}

