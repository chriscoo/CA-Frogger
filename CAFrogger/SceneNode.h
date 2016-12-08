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

#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include "Command.h"
#include "Category.h"
#include "CommandQueue.h"
#include <set>
namespace GEX {
	class SceneNode : public sf::Transformable, public sf::Drawable 
	{

	public:
		typedef std::unique_ptr<SceneNode> ptr; //instead of typing out the whole unique ptr
		typedef std::pair<SceneNode*, SceneNode*> pair;
	public:
									SceneNode(Category::type type = Category::type::none);
									virtual ~SceneNode();

									SceneNode(const SceneNode&) = delete;
		SceneNode&					operator=(const SceneNode&) = delete;
		void						attatchChild(ptr);
		ptr							detachChild(const SceneNode& node);
		void						update(sf::Time dt, CommandQueue& commands);
		void						onCommand(const Command& command, sf::Time dt);
		virtual unsigned int		getCategory() const;
		virtual sf::FloatRect		getBoundingRect() const;
		sf::Vector2f				getWorldPosition() const;

		sf::Transform				getWorldTrandform() const;

		virtual bool				isDestroyed() const;

		void checkSceneCollision(SceneNode& sceneNode, std::set<pair>& collisionPairs);
		void checkNodeCollision(SceneNode& Node, std::set<pair>& collisionPairs);

		void removeWrecks();
		virtual bool isMarkedForRemoval() const;
	
	private:

		
		virtual void				updateCurrent(sf::Time dt, CommandQueue& commands);
		void						updateChildren(sf::Time dt, CommandQueue& commands);

		void						draw(sf::RenderTarget& target, sf::RenderStates state)const override final;
		virtual void				drawCurrent(sf::RenderTarget& target, sf::RenderStates state) const;
		void						drawChildren(sf::RenderTarget& target, sf::RenderStates state) const;
		void						drawBoundingRect(sf::RenderTarget& target, sf::RenderStates state) const;
		//draw methods go here
	private:
		SceneNode*					_parent;
		std::vector<ptr>			_children;
		Category::type				_defaultCategory;
	};

	bool							collision(const SceneNode& lhs, const SceneNode& rhs);
	float							distance(const SceneNode& lhs, const SceneNode& rhs);
}

