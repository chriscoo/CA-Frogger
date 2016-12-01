#include "Vehicle.h"
#include "TextureHolder.h"
#include "Utility.h"
#include "DataTables.h"

namespace GEX 
{
	const 	std::map<Vehicle::Type, VehicleData> table = InitializeVehicleData();

	Vehicle::Vehicle(Type type) : Entity(1), _type(type), _sprite(TextureHolder::getInstance().get(TextureID::Atlas)), _speed(0)
	{

		_sprite.setTextureRect(table.at(type).textureRect);
		setVelocity(table.at(type).speed, 0);
		centerOrigin(_sprite);

	}
	unsigned int Vehicle::getCategory() const
	{
		return Category::Car;
	}
	
	void Vehicle::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}
	void Vehicle::updateCurrent(sf::Time dt, CommandQueue & commands)
	{
		sf::Vector2f velo = getVelocity();
		if (velo.x != 0.f && velo.y != 0.f)
			setVelocity(velo / std::sqrt(2.f));

		
		Entity::updateCurrent(dt, commands);
	}

	float Vehicle::getMaxSpeed() const
	{
		return 40.0f;
	}

	sf::FloatRect Vehicle::getBoundingRect() const
	{
		return getWorldTrandform().transformRect(_sprite.getGlobalBounds());
	}
	
}
