/**
@file EmitterNode
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#pragma once
#include "SceneNode.h"
#include "Particle.h"
#include "ParticleNode.h"
namespace GEX {
	class EmitterNode : public SceneNode
	{
	public:
		explicit EmitterNode(Particle::Type type);

	private:
		void	updateCurrent(sf::Time dt, CommandQueue& commands) override;
		void	emitParticles(sf::Time dt);

	private:
		sf::Time	_acumilatedTime;
		Particle::Type _type;
		ParticleNode* _particleSystem;

	};

}