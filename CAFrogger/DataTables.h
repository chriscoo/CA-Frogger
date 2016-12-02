/**
@file DataTable.h
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/
#pragma once
#include "TextureHolder.h"
#include "Plane.h"

#include "Projectile.h"
#include "Particle.h"
#include "Pickup.h"
#include "Utility.h"
#include "Vehicle.h"
#include "Turtle.h"
#include "Log.h"
#include <map>
#include <vector>
namespace GEX {

	struct Direction
	{
		Direction(float a, float d);
		float angle;
		float distance;


	};
	struct AircraftData
	{
		int					    hitpoints;
		float				    speed;
		TextureID			    texture;
		sf::Time			    fireInterval;
		std::vector<Direction>  directions;
		sf::IntRect				textureRect;
	};

	struct ProjectileData
	{
		int			damage;
		float		speed;
		TextureID	texture;
		sf::IntRect	textureRect;
		float		approachRate;
	};
	struct PickupData {
		TextureID					texture;
		sf::IntRect					textureRect;
		std::function<void(Plane&)> action;
	};
	struct ParticleData {
		//TextureID					texture;
		//sf::IntRect					textureRect;
		sf::Time					lifeTime;
		sf::Color					color;

	};
	struct VehicleData {
		
		sf::IntRect					textureRect;
		float						speed;

	};

	struct LogData {
		sf::IntRect					textureRect;
		float						speed;

	};


	struct TurtleData {
		sf::IntRect					textureRect;
		float						speed;

	};
	std::map<Log::Type, LogData> InitializeLogData();
	std::map<Vehicle::Type, VehicleData> InitializeVehicleData();
	std::map<Turtle::Type, TurtleData> InitializeTurtleData();
	std::map<Plane::Type, AircraftData> InitializeAircraftData();
	std::map<Projectile::Type, ProjectileData> InitializeProjectileData();
	std::map<Pickup::Type, PickupData> InitializePickupData();
	std::map<Particle::Type, ParticleData> InitializeParticleData();
}
