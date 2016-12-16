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

#include "EmitterNode.h"



namespace GEX {
	EmitterNode::EmitterNode(Particle::Type type) : _acumilatedTime(sf::Time::Zero), _type(type), _particleSystem(nullptr)
	{
	}
	void EmitterNode::updateCurrent(sf::Time dt, CommandQueue & commands)
	{
		//if (_particleSystem)
		//	emitParticles(dt);
		//else 
		//{
		//	auto finder = [this](ParticleNode& node, sf::Time) 
		//	{  
		//		if (node.getParticleType() == _type)
		//			_particleSystem = &node;
		//	};
		//
		//	Command command;
		//	command.category = Category::ParticleSystem;
		//	command.action = derivedAction<ParticleNode>(finder);
		//
		//	commands.push(command);
		//}
		
	}
	void EmitterNode::emitParticles(sf::Time dt)
	{
		const float emissionRate = 300.f;
		const sf::Time interval = sf::seconds(1) / emissionRate;
		_acumilatedTime += dt;
		while (_acumilatedTime > interval)
		{
			_acumilatedTime -= interval;
			_particleSystem->addParticle(getWorldPosition());
		}
	}
}