/**
@file ParticleNode
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "TextureHolder.h"
#include "ParticleNode.h"
#include "DataTables.h"
#include <map>


namespace GEX {
	namespace
	{
		const std::map<Particle::Type, ParticleData> table = InitializeParticleData();
	}

	ParticleNode::ParticleNode(Particle::Type type) : SceneNode(), _particles(), _texture(TextureHolder::getInstance().get(TextureID::PARTICLE)), _type(type), _vertexArray(sf::Quads), _needsVertexUpdate(true)
	{															  
	}															   

	void GEX::ParticleNode::addParticle(sf::Vector2f position)
	{
		Particle particle;
		particle.position = position;
		particle.color = table.at(_type).color;
		particle.lifeTime = table.at(_type).lifeTime;
		_particles.push_back(particle);

	}

	Particle::Type GEX::ParticleNode::getParticleType() const
	{
		return _type;
	}

	unsigned int GEX::ParticleNode::getCategory() const
	{
		return Category::ParticleSystem;
	}

	void GEX::ParticleNode::updateCurrent(sf::Time dt, CommandQueue & commands)
	{
		while (!_particles.empty() && _particles.front().lifeTime <= sf::Time::Zero) //removing dead paticles
		{
			_particles.pop_front();
		}

		for (auto& particle : _particles) //update the lifetime of all particles
			particle.lifeTime -= dt;

		//marks it as dirty(means needs to be updated)
		_needsVertexUpdate = true;
	}

	void GEX::ParticleNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
	{
		if (_needsVertexUpdate)
		{
			computeVertices();
			_needsVertexUpdate = false;

		}
		states.texture = &_texture;

		target.draw(_vertexArray, states);
	}

	void GEX::ParticleNode::addVertex(float worldX, float WorldY, float textureU, float textureV, const sf::Color & color) const
	{
		sf::Vertex vertex;
		vertex.position = sf::Vector2f(worldX, WorldY);
		vertex.texCoords = sf::Vector2f(textureU, textureV);
		vertex.color = color;

		_vertexArray.append(vertex);
	}

	void GEX::ParticleNode::computeVertices() const
	{
		sf::Vector2f size(_texture.getSize());
		sf::Vector2f half = size / 2.f;

		_vertexArray.clear();
		for (const Particle& particle : _particles)
		{
			sf::Vector2f pos = particle.position;
			sf::Color color = particle.color;
			
			float ratio = particle.lifeTime.asSeconds() / table.at(_type).lifeTime.asSeconds();
			color.a = static_cast<sf::Uint8>(255 * std::max(ratio, 0.f));

			addVertex(pos.x - half.x, pos.y - half.y, 0.f, 0.f, color);
			addVertex(pos.x + half.x, pos.y - half.y, size.x, 0.f, color);
			addVertex(pos.x + half.x, pos.y + half.y, size.x, size.y, color);
			addVertex(pos.x - half.x, pos.y + half.y, 0.f, size.y, color);
		}
	}
}