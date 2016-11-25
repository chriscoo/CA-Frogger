/**
@file Plane
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/
#include "Plane.h"
#include "TextureHolder.h"
#include "TextNode.h"
#include "DataTables.h"
#include "Utility.h"
#include <iostream>
#include <cassert>
#include "SoundNode.h"
namespace GEX {

	const 	std::map<Plane::Type, AircraftData> table = InitializeAircraftData();;


	Plane::Plane(Type type) : Entity(table.at(type).hitpoints), _type(type), _player(TextureHolder::getInstance().get(table.at(type).texture)), _directionIndex(0), _travelDistance(0), _missleAmmo(8), _spreadLevel(1), _fireRateInterval(5), __fireCountdown(sf::Time::Zero), _isMarkedForRemoval(false), _showExplosion(true), _explosion(TextureHolder::getInstance().get(TextureID::Explosion)), _playedExplosionSound(false), _spawnedPickup(false)
	{
		_player.setTextureRect(table.at(type).textureRect);
		centerOrigin(_player);
		//sets up the health display
		std::unique_ptr<TextNode> HealthDisplay(new TextNode(std::to_string(GetHitPoints()) + " HP"));
		_healthDisplay = HealthDisplay.get();
		HealthDisplay->setPosition(0.f, 50.f);
		attatchChild(std::move(HealthDisplay));

		_explosion.setFrameSize(sf::Vector2i(256, 256));
		_explosion.setNumFrames(10);
		_explosion.setDuration(sf::seconds(2));
		centerOrigin(_explosion);

		//fire and launch commands

		_fireCommand.category = Category::SceneAirLayer;
		_fireCommand.action = [this](SceneNode& node, sf::Time dt) { //[this] is the plane since he makes he bullet and the node is the air layer so we can attatch the bullet to it
			this->createBullets(node);
			
		};
		_launchMissileCommand.category = Category::SceneAirLayer;
		_launchMissileCommand.action = [this](SceneNode& node, sf::Time dt) { //[this] is the plane since he makes he bullet and the node is the air layer so we can attatch the bullet to it
			this->createProjectile(node, Projectile::Type::Missle, 0.f, 0.5f);

		};


		_dropPickupCommand.category = Category::SceneAirLayer;
		_dropPickupCommand.action = [this](SceneNode& node, sf::Time)
		{
			this->createPickup(node);
		};

	}

	//unsigned int Plane::getCategory() const
	//{
	//	switch (_type) //sets the correct category for the different types of airplanes
	//	{
	//	case GEX::Plane::Type::EAGLE:
	//		return Category::playerAircraft;
	//
	//	case GEX::Plane::Type::RAPTOR:
	//		return Category::EnemyAircraft;
	//
	//	case GEX::Plane::Type::AVENGER:
	//		return Category::EnemyAircraft;
	//	default:
	//		assert(0); //missing type
	//
	//	}
	//
	//}

	void Plane::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{

		if (isDestroyed() && _showExplosion)
			target.draw(_explosion, state);
		else
		target.draw(_player, state);

	}

	void Plane::updateCurrent(sf::Time dt, CommandQueue& commands)
	{
		sf::Vector2f velo = getVelocity();
		if (velo.x != 0.f && velo.y != 0.f)
			setVelocity(velo / std::sqrt(2.f));

		
		if (isDestroyed())
		{
			
			//drops Pickups here

			_explosion.update(dt);

			if (!_spawnedPickup)
			{
				checkPickupDrop(commands);
				_spawnedPickup = true;
			}

			if (!_playedExplosionSound)
			{
				SoundEffectID soundEffect = (randomInt(2) == 0) ? SoundEffectID::Explosion1 : SoundEffectID::Explosion2;
				playLocalSound(commands, soundEffect);

				_playedExplosionSound = true;



			}
			return;


		}


		updateTexts();
		checkProjectileLaunch(dt, commands);

		movementUpdate(dt);
		Entity::updateCurrent(dt, commands);
	}

	void Plane::updateTexts() 
	{
		_healthDisplay->setText(std::to_string(GetHitPoints()) + " HP");

		_healthDisplay->setRotation(-getRotation());
		_healthDisplay->setPosition(0.f, 50.f);
	
	}

	void Plane::movementUpdate(sf::Time dt)
	{
		const std::vector<Direction>& directions = table.at(_type).directions;

		if (!directions.empty())
		{
			float distanceToTravel = directions.at(_directionIndex).distance;
			if (_travelDistance > distanceToTravel)
			{
				_directionIndex = (_directionIndex + 1) % directions.size();
				_travelDistance = 0;
			}
			_travelDistance += getMaxSpeed() * dt.asSeconds();

			float dirAngle = directions.at(_directionIndex).angle + 90;
			float xv = getMaxSpeed() * GEX::cos(dirAngle);
			float yv = getMaxSpeed() * GEX::sin(dirAngle);
			setVelocity(xv, yv);

		}


	}

	void Plane::fireMissle()
	{
		if (_missleAmmo > 0)
		{
			_isFiringMissle = true;
			_missleAmmo--;
		}
	}

	void Plane::fireBullet()
	{
		//only ships with fire rates that arn't zero can fire
		if (!isDestroyed())
		{
			if (table.at(_type).fireInterval != sf::Time::Zero)
				_isFiringBullets = true;
		}
		
	}
	void Plane::playLocalSound(CommandQueue & commands, SoundEffectID effect)
	{
		sf::Vector2f worldPos = getWorldPosition();

		Command command;
		command.category = Category::SoundEffect;
		command.action = derivedAction<SoundNode>([effect, worldPos](SoundNode& node, sf::Time) {node.playSound(effect, worldPos); });

		commands.push(command);
	}
	void Plane::collecMissiles(unsigned int count)
	{
		_missleAmmo += count;
	}
	void Plane::increaseFireRate()
	{
		if (_fireRateInterval < 10)
			++_fireRateInterval;
	}
	void Plane::increadFireSpread()
	{
		if (_spreadLevel < 3)
			++_spreadLevel;
	}
	bool Plane::isMarkedForRemoval() const
	{
		return isDestroyed() && (_explosion.isFinished() || !_showExplosion);
	}
	void Plane::checkProjectileLaunch(sf::Time dt, CommandQueue & commands)
	{
		//enemys always fire

		if (!isAllied())
			fireBullet();

		//for bullet fire
		if (_isFiringBullets && __fireCountdown <= sf::Time::Zero)
		{
			commands.push(_fireCommand);


			playLocalSound(commands, isAllied() ? SoundEffectID::AlliedGunfire : SoundEffectID::EnemyGunfire);
			//playLocalSound(commands, SoundEffectID::AlliedGunfire);
			_isFiringBullets = false;
			__fireCountdown += table.at(_type).fireInterval/(_fireRateInterval + 1.f);
		}
		else if (__fireCountdown > sf::Time::Zero)
		{
			__fireCountdown-=dt;
			_isFiringBullets = false;
		}

		if (_isFiringMissle)
		{
			commands.push(_launchMissileCommand);
			playLocalSound(commands, SoundEffectID::LaunchMissile);
			_isFiringMissle = false;
		}

	}
	float Plane::getMaxSpeed() const
	{
		return table.at(_type).speed;
	}

	sf::FloatRect Plane::getBoundingRect() const
	{
		return getWorldTrandform().transformRect(_player.getGlobalBounds());
	}

	void Plane::createBullets(SceneNode & node) const
	{
		Projectile::Type type = isAllied() ? Projectile::Type::AlliedBullet : Projectile::Type::EnemyBullet;
		

		switch (_spreadLevel)
		{
		case 1:
			createProjectile(node, type, 0.f, 0.5f);
			break;
		case 2:
			createProjectile(node, type, -0.3f, 0.33f);
			createProjectile(node, type, 0.3f, 0.33f);
			break;
		case 3:
			createProjectile(node, type, -0.5f, 0.33f);
			createProjectile(node, type, 0.f, 0.5f);
			createProjectile(node, type, 0.5f, 0.33f);
			break;
		default:
			break;

		}
	}

	void Plane::createProjectile(SceneNode & node, Projectile::Type type, float xOffset, float yOffset) const
	{
		//node is the scenelayerNode that the command was targeted to
		std::unique_ptr<Projectile> projectile(new Projectile(type));


		sf::Vector2f offSet(xOffset * _player.getGlobalBounds().width, yOffset * _player.getGlobalBounds().height);
		sf::Vector2f velocity(0.f, projectile->getMaxSpeed());

		float sign = isAllied() ? -1.f : 1.f;
		projectile->setPosition(getWorldPosition() + offSet * sign);
		projectile->setVelocity(velocity * sign);
		node.attatchChild(std::move(projectile));
	}

	bool Plane::isAllied() const
	{
		return _type == Plane::Type::EAGLE;
		
	}

	void Plane::checkPickupDrop(CommandQueue & commands)
	{
		if (!isAllied() && _spawnedPickup == false)
		{
			commands.push(_dropPickupCommand);
			//_spawnedPickup = true;
		}
	}

	void Plane::createPickup(SceneNode & node) const
	{
		int tmp = randomInt(4);
		
		if (tmp == 0)
		{
			std::unique_ptr<Pickup> pickup(new Pickup(Pickup::Type::FireRate));
			pickup->setPosition(node.getPosition());
			node.attatchChild(std::move(pickup));
		}
			
		if (tmp == 1)
		{
			std::unique_ptr<Pickup> pickup(new Pickup(Pickup::Type::FireSpread));
			pickup->setPosition(node.getPosition());
			node.attatchChild(std::move(pickup));
		}
		if (tmp == 2)
		{
			std::unique_ptr<Pickup> pickup(new Pickup(Pickup::Type::HealthRefill));
			pickup->setPosition(node.getPosition());
			node.attatchChild(std::move(pickup));
		}
		if (tmp == 3)
		{
			std::unique_ptr<Pickup> pickup(new Pickup(Pickup::Type::MissileRefill));
			pickup->setPosition(node.getPosition());
			node.attatchChild(std::move(pickup));
		}
			
	
	}


}