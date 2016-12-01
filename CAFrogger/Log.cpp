#include "Log.h"
#include "TextureHolder.h"
#include "Utility.h"
#include "DataTables.h"


namespace GEX {


	const 	std::map<Log::Type, LogData> table = InitializeLogData();

	Log::Log(Type type) : Entity(1), _type(type), _sprite(TextureHolder::getInstance().get(TextureID::Atlas)), _speed(0)
	{

		_sprite.setTextureRect(table.at(type).textureRect);
		setVelocity(table.at(type).speed, 0);
		centerOrigin(_sprite);

	}
	unsigned int Log::getCategory() const
	{
		return Category::Log;
	}

	void Log::drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const
	{
		target.draw(_sprite, state);
	}
	void Log::updateCurrent(sf::Time dt, CommandQueue & commands)
	{
		sf::Vector2f velo = getVelocity();
		if (velo.x != 0.f && velo.y != 0.f)
			setVelocity(velo / std::sqrt(2.f));


		Entity::updateCurrent(dt, commands);
	}

	float Log::getMaxSpeed() const
	{
		return 40.0f;
	}

	sf::FloatRect Log::getBoundingRect() const
	{
		return getWorldTrandform().transformRect(_sprite.getGlobalBounds());
	}


}