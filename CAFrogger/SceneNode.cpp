/**
@file SceneNode
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "SceneNode.h"
#include "Utility.h"
#include <cassert>

namespace GEX {
	SceneNode::SceneNode(Category::type _type) : _parent(nullptr), _defaultCategory(_type)
	{
	}


	SceneNode::~SceneNode()
	{
	}

	void SceneNode::attatchChild(ptr child) //adds children to the current parent
	{
		child->_parent = this;
		_children.push_back(std::move(child));
	}

	SceneNode::ptr SceneNode::detachChild(const SceneNode & node) //emoves a child ptr
	{

		
		auto found = std::find_if(_children.begin(), _children.end(), [&](ptr& p)->bool {return p.get() == &node; });
		assert(found == _children.end()); //wasn't found
		ptr result = std::move(*found);
		result->_parent = nullptr;
		_children.erase(found);
			return result;
	}

	void SceneNode::update(sf::Time dt, CommandQueue& commands)
	{
		updateCurrent(dt, commands);
		updateChildren(dt, commands);
	}

	void SceneNode::onCommand(const Command & command, sf::Time dt) //cascades through the parent and child pointers until it finds the correct category for the command then executes it
	{
		if(command.category & getCategory())
		command.action(*this, dt);
		for (auto& child : _children)
			child->onCommand(command, dt);
	}

	unsigned int SceneNode::getCategory() const
	{
		return _defaultCategory;
	}

	sf::FloatRect SceneNode::getBoundingRect() const
	{
		return sf::FloatRect();
	}

	sf::Vector2f SceneNode::getWorldPosition() const
	{
		return getWorldTrandform() *  sf::Vector2f();
	}

	sf::Transform SceneNode::getWorldTrandform() const
	{
		sf::Transform transform = sf::Transform::Identity;
		for (const SceneNode* node = this; node != nullptr; node = node->_parent)
		{
			transform = node->getTransform() * transform;
		}
		return transform;
	}

	bool SceneNode::isDestroyed() const
	{
		return false;
	}

	void SceneNode::checkSceneCollision(SceneNode & node, std::set<pair>& collisionPairs)
	{
		this->checkNodeCollision(node, collisionPairs);

		for (auto& child : node._children)
			this->checkSceneCollision(*child, collisionPairs);

		
	}

	void SceneNode::checkNodeCollision(SceneNode & node, std::set<pair>& collisionPairs)
	{
		if (this != &node && collision(*this, node) && !isDestroyed() && !node.isDestroyed()) { collisionPairs.insert(std::minmax(this, &node)); }
		for (auto& child : _children)
			child->checkNodeCollision(node, collisionPairs);
	}

	void SceneNode::removeWrecks()
	{
		auto wreckfieldBegin = std::remove_if(_children.begin(), _children.end(), std::mem_fn(&SceneNode::isMarkedForRemoval));	

		_children.erase(wreckfieldBegin, _children.end());

		std::for_each(_children.begin(), _children.end(), std::mem_fn(&SceneNode::removeWrecks));
	}

	bool SceneNode::isMarkedForRemoval() const
	{
		return isDestroyed();
	}

	void SceneNode::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		//overridden from elsewheres
	}

	void SceneNode::updateChildren(sf::Time dt, CommandQueue& commands)
	{
		for (const ptr& child : _children)
		{
			child->update(dt, commands);
		}
	}

	void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates state) const //draws all nodes
	{
		state.transform *= getTransform();

		drawCurrent(target, state);
		drawBoundingRect(target, state);
		drawChildren(target, state);
		
	}

	void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{}

	void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates state) const //draws all the nodes under the one who calls the moethod
	{
		for (const ptr& child : _children)
		{
			child->draw(target, state);
		}
	}

	void SceneNode::drawBoundingRect(sf::RenderTarget & target, sf::RenderStates state) const //creates the outline so we know the hitboxes of our sprites
	{
		sf::FloatRect rect = getBoundingRect();

		sf::RectangleShape shape;
		shape.setPosition(sf::Vector2f(rect.left, rect.top));
		shape.setSize(sf::Vector2f(rect.width, rect.height));
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Red);
		shape.setOutlineThickness(1.f);
		target.draw(shape);
	}


	bool collision(const SceneNode & lhs, const SceneNode & rhs)
	{
		return lhs.getBoundingRect().intersects(rhs.getBoundingRect());
	}

	float distance(const SceneNode & lhs, const SceneNode & rhs)
	{
		return length(lhs.getWorldPosition() - rhs.getWorldPosition());
	}

	

}
