/**
@file Frog
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
#include "Animation.h"
#include "CommandQueue.h"
#include <memory>

#include "SoundBufferHolder.h"
namespace GEX {

	class Frog : public Entity
	{
	public:
		enum class State{Up, Down, Left, Right};
	public:
		Frog();
		virtual ~Frog() {};
		unsigned int	getCategory() const override;
		void			drawCurrent(sf::RenderTarget & target, sf::RenderStates state) const; //draws the current instance of plane
		void			updateCurrent(sf::Time dt, CommandQueue& commands);
		
		//void			playLocalSound(CommandQueue& commands, SoundEffectID effect);
		bool			isMarkedForRemoval() const override;
		float			getMaxSpeed() const; //gets the planes speed from he datatable
		sf::FloatRect	getBoundingRect() const override; //gets the hitbox

	private:
		State			_state;
		sf::Sprite		_player; //the controllable plane the user uses
		int				_directionIndex;
		float			_travelDistance;
		bool			_isMarkedForRemoval;
		bool			_playedMovementSound;
		bool			_playedDeathSound;
		
		std::vector<sf::IntRect> animation;
	};
}
