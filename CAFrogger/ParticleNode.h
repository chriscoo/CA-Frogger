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

#include "Particle.h"
#include "SceneNode.h"
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\View.hpp>
#include <deque>
namespace GEX {
	class ParticleNode : public SceneNode
	{
	public:
		explicit ParticleNode(Particle::Type type);

		void addParticle(sf::Vector2f position);
		Particle::Type getParticleType() const;

		unsigned int getCategory() const override;

	private:
		void updateCurrent(sf::Time dt, CommandQueue& commands) override;
		void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

		void addVertex(float worldX, float WorldY, float textureU, float textureV, const sf::Color& color) const;
		void computeVertices() const;

	private:
		std::deque<Particle>	 _particles;
		const sf::Texture&		 _texture;
		Particle::Type			 _type;

		mutable sf::VertexArray	_vertexArray;
		mutable bool _needsVertexUpdate;


	};

}