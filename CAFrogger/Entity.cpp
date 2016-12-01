/**
@file Entity
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "Entity.h"


namespace GEX {
	Entity::Entity(int hitpoints) : _hitPoints(hitpoints), _velocity(), _angularVelocity(), _spawn()
	{
	}


	Entity::~Entity()
	{
	}
	void Entity::setVelocity(sf::Vector2f velocity)
	{
		_velocity = velocity;
	}
	void Entity::setVelocity(float vx, float vy)
	{
		_velocity = sf::Vector2f(vx, vy);
	}
	sf::Vector2f Entity::getVelocity() const
	{
		return _velocity;
	}

	void Entity::setSpawn(sf::Vector2f spawn)
	{
		_spawn = spawn;
	}
	void Entity::setSpawn(float vx, float vy)
	{
		_spawn = sf::Vector2f(vx, vy);
	}
	sf::Vector2f Entity::getSpawn() const
	{
		return _spawn;
	}

	void Entity::accelerate(sf::Vector2f velocity)
	{
		
		setVelocity(velocity + getVelocity());
	}

	void Entity::accelerate(float vx, float vy)
	{
		setVelocity(sf::Vector2f(vx,vy) + getVelocity());
	}

	void Entity::angularAccelerate(float speed)
	{
		setAngularVelocity(speed + getAngularVelocity());
	}

	void Entity::setAngularVelocity(float rotaSpeed)
	{
		_angularVelocity = rotaSpeed;
	}

	float Entity::getAngularVelocity() const
	{
		return _angularVelocity;
	}

	int Entity::GetHitPoints() const
	{
		return _hitPoints;
	}

	void Entity::repair(int points)
	{
		_hitPoints += points;
	}

	void Entity::damage(int points)
	{
		_hitPoints -= points;
	}

	void Entity::distroy()
	{
		_hitPoints = 0;
	}

	bool Entity::isDestroyed() const
	{
		return _hitPoints <= 0;
	}

	void Entity::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		move(_velocity * dt.asSeconds());
	//	setRotation(_angularVelocity * dt.asSeconds());
		
	}
}