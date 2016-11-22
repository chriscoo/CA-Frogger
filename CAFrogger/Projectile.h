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

#pragma once
#include "Entity.h"
#include "TextureHolder.h"
#include "TextNode.h"
#include "CommandQueue.h"
namespace GEX {

	class Projectile : public Entity
	{
	public:
		enum class Type
		{
			AlliedBullet,
			EnemyBullet,
			Missle


		};
	public:
		Projectile(Type type);

		unsigned int getCategory() const override;
		float getMaxSpeed() const;
		bool isGuided() const;
		void guideTowards(sf::Vector2f position);
		sf::FloatRect	getBoundingRect() const override;

	private:
		virtual void updateCurrent(sf::Time dt, CommandQueue& commands) override;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
		
	private:
		Type _type;
		sf::Sprite _sprite;
		sf::Vector2f _targetDirection; // unit vecor pointing at the closest enemy plane

	};
}
