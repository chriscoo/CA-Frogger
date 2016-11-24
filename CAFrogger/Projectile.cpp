/**
@file Projectile
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "Projectile.h"
#include "TextureHolder.h"
#include "TextNode.h"
#include "DataTables.h"
#include "Utility.h"
#include "EmitterNode.h"
#include <iostream>
#include <cassert>


namespace GEX {
	const 	std::map<Projectile::Type, ProjectileData> table = InitializeProjectileData();


	Projectile::Projectile(Type type) : Entity(), _type(type), _sprite(TextureHolder::getInstance().get(table.at(type).texture), table.at(type).textureRect)
	{
		
		centerOrigin(_sprite);

		if (isGuided())
		{
			std::unique_ptr<EmitterNode> smoke(new EmitterNode(Particle::Type::Smoke));
			smoke->setPosition(0.f, getBoundingRect().height / 2);
			attatchChild(std::move(smoke));

			std::unique_ptr<EmitterNode> fire(new EmitterNode(Particle::Type::Propellant));
			fire->setPosition(0.f, getBoundingRect().height / 2);
			attatchChild(std::move(fire));

		}
	}

	//unsigned int Projectile::getCategory() const //to find out who the bullets should damage
	//{
	//	switch (_type)
	//	{
	//	case GEX::Projectile::Type::AlliedBullet:
	////		return Category::AlliedProjectile;
	////		break;
	////	case GEX::Projectile::Type::EnemyBullet:
	////		return Category::EnemyProjectile;
	////		break;
	////	case GEX::Projectile::Type::Missle:
	////		return Category::AlliedProjectile;
	////		break;
	////	default:
	////		break;
	////	}	
	//	
	//}


float Projectile::getMaxSpeed() const //gets the bullets/missiles speed
{
	return table.at(_type).speed;
}

bool Projectile::isGuided() const
{
	return _type == Type::Missle;
}

void Projectile::guideTowards(sf::Vector2f position) 
{
	assert(isGuided());
	_targetDirection = unitVector(position - getWorldPosition());
}

sf::FloatRect Projectile::getBoundingRect() const
{
	return getWorldTrandform().transformRect(_sprite.getGlobalBounds());
}

void Projectile::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	if (isGuided())
	{
		

		sf::Vector2f newVelocity = unitVector(table.at(_type).approachRate * dt.asSeconds() * _targetDirection + getVelocity());
		newVelocity = newVelocity * getMaxSpeed();
		setVelocity(newVelocity);
		setRotation(arctan2(newVelocity.x, newVelocity.y * -1));
	}

	Entity::updateCurrent(dt, commands);
}

void Projectile::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(_sprite, states);
}

}
