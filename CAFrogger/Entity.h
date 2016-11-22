/**
@file Entity.h
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#pragma once
#include "SceneNode.h"
namespace GEX {
	class Entity : public SceneNode
	{
	public:
		Entity(int hitpoints = 20);
		virtual ~Entity();

		void			setVelocity(sf::Vector2f velocity);
		void			setVelocity(float vx, float vy);
		sf::Vector2f	getVelocity() const;

		void			accelerate(sf::Vector2f velocity);
		void			accelerate(float vx, float vy);
		
		
		void			angularAccelerate(float speed);
		void			setAngularVelocity(float rotaSpeed);
		float			getAngularVelocity() const;

		int				GetHitPoints() const;
		void			repair(int points);
		void			damage(int points);
		void			distroy();
		bool			isDestroyed() const override;
	protected:
		
		void			updateCurrent(sf::Time dt, CommandQueue& commands) override;
	private:
		int					_hitPoints;
		float			_angularVelocity = 0;
		sf::Vector2f	_velocity;
	};
}

