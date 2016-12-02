#pragma once
#include "Entity.h"
namespace GEX {
	class Turtle : public Entity
	{
	public:
		enum class  Type { Turtle2, Turtle3 };
	public:
		Turtle(Type type);
		virtual ~Turtle() {};
		unsigned int	getCategory() const override;

		void			drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const; //draws the current instance of plane
		void			updateCurrent(sf::Time dt, CommandQueue& commands);
		float			getMaxSpeed() const; //gets the planes speed from he datatable
		sf::FloatRect	getBoundingRect() const override; //gets the hitbox


	private:
		Type _type;
		sf::Sprite		_sprite; //the controllable plane the user uses
		float			_speed;
	};
}

