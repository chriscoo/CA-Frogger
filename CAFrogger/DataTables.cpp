/**
@file DataTables
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "DataTables.h"


namespace GEX {
	std::map<Vehicle::Type, VehicleData> InitializeVehicleData()
	{
		std::map<Vehicle::Type, VehicleData> data;

		data[Vehicle::Type::CarL].speed = 40.f;
		data[Vehicle::Type::CarL].textureRect = sf::IntRect(69, 100, 37, 37);

		data[Vehicle::Type::CarR].speed = -40.f;
		data[Vehicle::Type::CarR].textureRect = sf::IntRect(139, 100, 38, 39);

		data[Vehicle::Type::RaceCar].speed = -60.f;
		data[Vehicle::Type::RaceCar].textureRect = sf::IntRect(1, 62, 35, 29);

		data[Vehicle::Type::Tractor].speed = 25.f;
		data[Vehicle::Type::Tractor].textureRect = sf::IntRect(214, 62, 33, 33);

		data[Vehicle::Type::Truck].speed = -25.f;
		data[Vehicle::Type::Truck].textureRect = sf::IntRect(293, 1, 61, 28);


		return data;
	}

	std::map<Log::Type, LogData> InitializeLogData()
	{
		std::map<Log::Type, LogData> data;

		data[Log::Type::ShortL].speed = -40.f;
		data[Log::Type::ShortL].textureRect = sf::IntRect(198,31,93,29);

		data[Log::Type::ShortR].speed = 40.f;
		data[Log::Type::ShortL].textureRect = sf::IntRect(198, 31, 93, 29);

		data[Log::Type::LongL].speed = -40.f;
		data[Log::Type::LongL].textureRect = sf::IntRect(1,31,195,28);

		data[Log::Type::LongR].speed = 40.f;
		data[Log::Type::LongR].textureRect = sf::IntRect(1, 31, 195, 28);


		return data;
	}
	//planes
	std::map<Plane::Type, AircraftData> GEX::InitializeAircraftData()
	{
		std::map<Plane::Type, AircraftData> data;


		data[Plane::Type::RAPTOR].hitpoints = 20;
		data[Plane::Type::RAPTOR].speed = 80;
		data[Plane::Type::RAPTOR].texture = TextureID::RAPTOR;
		data[Plane::Type::RAPTOR].fireInterval = sf::seconds(4);
		data[Plane::Type::RAPTOR].textureRect = sf::IntRect(144, 0, 84, 64);

		data[Plane::Type::RAPTOR].directions.push_back(Direction(80.f, 80.f));
		data[Plane::Type::RAPTOR].directions.push_back(Direction(-80.f, 100.f));
		data[Plane::Type::RAPTOR].directions.push_back(Direction(80.f, 80.f));

		data[Plane::Type::AVENGER].hitpoints = 40;
		data[Plane::Type::AVENGER].speed = 50;
		data[Plane::Type::AVENGER].texture = TextureID::AVENGER;
		data[Plane::Type::AVENGER].fireInterval = sf::seconds(4);
		data[Plane::Type::AVENGER].textureRect = sf::IntRect(228, 0, 60, 59);

		data[Plane::Type::AVENGER].directions.push_back(Direction(-70.f, 150.f));
		data[Plane::Type::AVENGER].directions.push_back(Direction(0.f, 25.f));
		data[Plane::Type::AVENGER].directions.push_back(Direction(150.f, 80.f));

		data[Plane::Type::EAGLE].hitpoints = 100;
		data[Plane::Type::EAGLE].speed = 200;
		data[Plane::Type::EAGLE].texture = TextureID::AIRPLANE;
		data[Plane::Type::EAGLE].fireInterval = sf::seconds(1);
		data[Plane::Type::EAGLE].textureRect = sf::IntRect(0, 0, 48, 64);


		return data;
	}
	Direction::Direction(float a, float d) : angle(a), distance(d)
	{
	}

	//projectiles
	std::map<Projectile::Type, ProjectileData> GEX::InitializeProjectileData()
	{
		std::map<Projectile::Type, ProjectileData> data;

		data[Projectile::Type::EnemyBullet].damage = 100;
		data[Projectile::Type::EnemyBullet].speed = 200;
		data[Projectile::Type::EnemyBullet].texture = TextureID::BULLET;
		data[Projectile::Type::EnemyBullet].textureRect = sf::IntRect(178, 64, 3, 14);

		data[Projectile::Type::AlliedBullet].damage = 100;
		data[Projectile::Type::AlliedBullet].speed = 200;
		data[Projectile::Type::AlliedBullet].texture = TextureID::BULLET;
		data[Projectile::Type::AlliedBullet].textureRect = sf::IntRect(178, 64, 3, 14);

		data[Projectile::Type::Missle].damage = 100;
		data[Projectile::Type::Missle].speed = 450;
		data[Projectile::Type::Missle].approachRate = 1000.f;
		data[Projectile::Type::Missle].texture = TextureID::MISSLE;
		data[Projectile::Type::Missle].textureRect = sf::IntRect(160, 64, 15, 32);

		return data;
	}

	//pick ups
	std::map<Pickup::Type, PickupData> InitializePickupData()
	{
		std::map<Pickup::Type, PickupData> data;

		data[Pickup::Type::FireRate].texture = TextureID::FireRate;
		data[Pickup::Type::FireRate].action = [](Plane& a) {a.increaseFireRate(); };
		data[Pickup::Type::FireRate].textureRect = sf::IntRect(120,	64,	40,	40);

		data[Pickup::Type::FireSpread].texture = TextureID::FireSpread;
		data[Pickup::Type::FireSpread].action = [](Plane& a) {a.increadFireSpread(); };
		data[Pickup::Type::FireSpread].textureRect = sf::IntRect(80,	64,	40,	40);

		data[Pickup::Type::HealthRefill].texture = TextureID::HealthRefill;
		data[Pickup::Type::HealthRefill].action = [](Plane& a) {a.repair(25); };
		data[Pickup::Type::HealthRefill].textureRect = sf::IntRect(0, 64, 40, 40);

		data[Pickup::Type::MissileRefill].texture = TextureID::MissileRefill;
		data[Pickup::Type::MissileRefill].action = [](Plane& a) {a.collecMissiles(3); };
		data[Pickup::Type::MissileRefill].textureRect = sf::IntRect(40, 64, 40, 40);

		return data;
	}
	std::map<Particle::Type, ParticleData> InitializeParticleData()
	{
		std::map<Particle::Type, ParticleData> data;

		//data[Particle::Type::Propellant].texture = TextureID::PARTICLE;
		data[Particle::Type::Propellant].lifeTime = sf::seconds(0.6f);
		data[Particle::Type::Propellant].color = sf::Color(255, 255, 50);

		//	data[Particle::Type::Smoke].texture = TextureID::PARTICLE;
		data[Particle::Type::Smoke].lifeTime = sf::seconds(4.f);
		data[Particle::Type::Smoke].color = sf::Color(50,50,50);
		return data;
	}
}