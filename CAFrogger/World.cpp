/**
@file World
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/
#include "World.h"
#include "Plane.h"
#include "Pickup.h"
#include "TextureHolder.h"
#include "Frog.h"
#include "ParticleNode.h"
#include "SpriteNode.h"
#include "SoundPlayer.h"
#include "SoundNode.h"
namespace GEX {

	bool matchesCategories(SceneNode::pair& colliders, Category::type type1, Category::type type2);
	World::World(sf::RenderWindow& window, SoundPlayer& soundPlayer) :
		_window(window),
		_worldView(window.getDefaultView()),
		_sceneGraph(),
		_sceneLayers(),
		_worldBounds(0.f, 0.f, _worldView.getSize().x, _worldView.getSize().y),
		_spawnPosition(_worldView.getSize().x / 2.f, _worldBounds.height-20),
		_scrollSpeed(0),
		_queue(),
		_soundPlayer(soundPlayer),
		_playerAircraft(nullptr),
		_lives(3)
	{

		buildScene();


		//sets the view to the bottom since we will scroll upwards
		//_worldView.setCenter(_spawnPosition);

	}


	World::~World()
	{
	}
	void World::update(sf::Time deltaTime)
	{
		
		while (!_queue.isEmpty())
		{
			_sceneGraph.onCommand(_queue.pop(), sf::Time::Zero);
		}

		//handleCollisions();

		drawLives();
		_sceneGraph.update(deltaTime, getCommandQueue());
	//	adaptPlayerPosition();

	}
	void World::draw() //creates the view 
	{
		_window.setView(_worldView);
		_window.draw(_sceneGraph);
	}
	CommandQueue & World::getCommandQueue()
	{
		return _queue;
	}

	void World::buildScene()
	{
		//LAYER NODES FOR SCENE GRAPH

		for (std::size_t i = 0; i < LayerCount; i++)
		{
			Category::type category = (i == Air) ? Category::SceneAirLayer : Category::none;
			SceneNode::ptr layer(new SceneNode(category));
			_sceneLayers[i] = layer.get();
			_sceneGraph.attatchChild(std::move(layer));
		}

		//background

		//
		//sf::Texture& texture = TextureHolder::getInstance().get(TextureID::DESERT);
		//sf::IntRect textureRect(_worldBounds);
		//texture.setRepeated(true);
		////background sprite
		//std::unique_ptr<SpriteNode> _background(new SpriteNode(texture, textureRect));
		//_background->setPosition(_worldBounds.left, _worldBounds.top);
		//_sceneLayers[Background]->attatchChild(std::move(_background));

		//background
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::Background);
		sf::IntRect textureRect(0, 0, 480, 600);
		//texture.setRepeated(true);
		//add background to sceneGraph
		std::unique_ptr<SpriteNode> background(new SpriteNode(texture, textureRect));
		background->setPosition(_worldBounds.left, _worldBounds.top);
		_sceneLayers[Background]->attatchChild(std::move(background));


		//finish line
		//sf::Texture& finish = TextureHolder::getInstance().get(TextureID::FinishLine);
		//sf::IntRect FinishRect(0, 0, 1024, 76);
		//std::unique_ptr<SpriteNode> finishLine(new SpriteNode(finish, FinishRect));
		//_sceneLayers[Background]->attatchChild(std::move(finishLine));
		////smoke behind missiles
		//std::unique_ptr<ParticleNode> smokeNode(new ParticleNode(Particle::Type::Smoke));
		//_sceneLayers[Air]->attatchChild(std::move(smokeNode));
		////fire behind missiles
		//std::unique_ptr<ParticleNode> fireNode(new ParticleNode(Particle::Type::Propellant));
		//_sceneLayers[Air]->attatchChild(std::move(fireNode));


		std::unique_ptr<SoundNode> soundeffectNode(new SoundNode(_soundPlayer));
		_sceneLayers[Air]->attatchChild(std::move(soundeffectNode));
		//player plane
		std::unique_ptr<Frog> plane(new Frog());
		plane->setPosition(_spawnPosition);
		//plane->setVelocity(40.f, _scrollSpeed);
		_playerAircraft = plane.get();
		_sceneLayers[Air]->attatchChild(std::move(plane));
		//
		//
		//
		//addEnemies();
	}
	bool World::hasAlivePlayer() const
	{
		
			return true;
		
	}
	bool World::hasReachedFinish() const
	{
		return false;
	}
	sf::FloatRect World::getViewBounds() const //gets the windows size
	{
		return sf::FloatRect(_worldView.getCenter() - _worldView.getSize() / 2.f, _worldView.getSize());
	}
	sf::FloatRect World::getBattleFieldBounds() const //gets the windows size plus some extra so we can spawn objects offscreen
	{
		sf::FloatRect bounds = getViewBounds();
		bounds.height += 100;
		bounds.top -= 100;
		return bounds;
	}
	void World::updateSounds()
	{
		_soundPlayer.setListenerPosition(_playerAircraft->getWorldPosition());
		_soundPlayer.removeStoppedSounds();
	}
	void World::spawnEnemies() //creates the enemy planes 
	{
		while (!_enemySpawnPoints.empty() && _enemySpawnPoints.back().y > getBattleFieldBounds().top)
		{
			auto spawn = _enemySpawnPoints.back();
			std::unique_ptr<Plane> enemy(new Plane(spawn.type));
			enemy->setPosition(spawn.x, spawn.y);
			enemy->setRotation(180.f);
			_sceneLayers[Air]->attatchChild(std::move(enemy));

			_enemySpawnPoints.pop_back();


		}
	}
	void World::addEnemies() //adds all the planes onto a vector and then sorts them from biggest to smallest so we just need to take it off the back instead of going through the vector to find the smallest
	{
		addEnemy(Plane::Type::RAPTOR, -250, 200);
		addEnemy(Plane::Type::RAPTOR, +250, 200);
		addEnemy(Plane::Type::RAPTOR, -150, 450);
		addEnemy(Plane::Type::RAPTOR, 0, 450);
		addEnemy(Plane::Type::RAPTOR, -250, 550);
		//addEnemy(Plane::Type::RAPTOR, -50, 700);
		//addEnemy(Plane::Type::RAPTOR, -150, 700);

		std::sort(_enemySpawnPoints.begin(), _enemySpawnPoints.end(), [](SpawnPoint lhs, SpawnPoint rhs) {return lhs.y < rhs.y; });

	}

	void World::addEnemy(Plane::Type type, float relx, float rely)
	{
		addEnemy(SpawnPoint(type, relx, rely));
	}
	void World::guideMissiles()
	{
	//	//sets up a list of all enemy planes
	//	Command enemyCollector;
	//	enemyCollector.category = Category::EnemyAircraft;
	//	enemyCollector.action = derivedAction<Plane>([this](Plane& enemy, sf::Time dt)
	//	{	
	//	if (!enemy.isDestroyed()) //checks if it is destroyed. if not then puts it into the list
	//	{
	//		this->_activeEnemies.push_back(&enemy);
	//	}
	//
	//	});
	//
	//	Command missileBuilder;
	//	missileBuilder.category = Category::AlliedProjectile;
	//	missileBuilder.action = derivedAction<Projectile>([this](Projectile& missile, sf::Time dt)
	//	{
	//		//ignore bullets
	//		if (!missile.isGuided())
	//			return;
	//
	//		float minDistance = std::numeric_limits<float>::max();
	//
	//		Plane* closestEnemy = nullptr;
	//		for (Plane* enemy : this->_activeEnemies)
	//		{
	//			float enemyDistance = distance(missile, *enemy);
	//
	//			if (enemyDistance < minDistance) {
	//				closestEnemy = enemy;
	//				minDistance = enemyDistance;
	//			}
	//		}
	//		if (closestEnemy)
	//		{
	//			missile.guideTowards(closestEnemy->getWorldPosition());
	//		}
	//
	//		
	//
	//
	//});
	//	//push the commands onto the queue
	//	_activeEnemies.clear();
	//	_queue.push(enemyCollector);
	//	_queue.push(missileBuilder);

}
	void World::handleCollisions()
	{
	//	std::set<SceneNode::pair> collisionPairs;
	//	_sceneGraph.checkSceneCollision(_sceneGraph, collisionPairs);
	//
	//	for (SceneNode::pair pair : collisionPairs)
	//	{
	//
	//		//if you and a plane collides
	//		if (matchesCategories(pair, Category::playerAircraft, Category::EnemyAircraft))
	//		{
	//			auto& player = static_cast<Plane&>(*pair.first);
	//			auto& enemy = static_cast<Plane&>(*pair.second);
	//
	//			player.damage(enemy.GetHitPoints());
	//			enemy.distroy();
	//		}
	//		//if you hit an enemy with a bullet/missile
	//		if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile) || (matchesCategories(pair, Category::playerAircraft, Category::EnemyProjectile)))
	//		{
	//			auto& aircraft = static_cast<Plane&>(*pair.first);
	//			auto& projectile = static_cast<Projectile&>(*pair.second);
	//
	//			aircraft.damage(projectile.GetHitPoints());
	//			projectile.distroy();
	//		}
	//		
	//		//if you hit a pick up
	//		if (matchesCategories(pair, Category::playerAircraft, Category::PickUp))
	//		{
	//			auto& player = static_cast<Plane&>(*pair.first);
	//			auto& pickup = static_cast<Pickup&>(*pair.second);
	//
	//			pickup.apply(player);
	//			pickup.distroy();
	//			player.playLocalSound(_queue, SoundEffectID::CollectPickup);
	//			
	//		}
	//
	//	}
	}
	void World::destroyEntitiesOutsideWorldView()
	{
	//	Command command;
	//	command.category = Category::Projectile | Category::EnemyAircraft;
	//	command.action = derivedAction<Entity>([this](Entity& e, sf::Time) 
	//	{
	//		if (!getBattleFieldBounds().intersects(e.getBoundingRect()))
	//			e.distroy();
	//	});
	//
	//	_queue.push(command);
	}
	void World::adaptPlayerPosition()
	{
		// Keep player's position inside the screen bounds, at least borderDistance units from the border
		sf::FloatRect viewBounds = getViewBounds();
		const float borderDistance = 40.f;

		sf::Vector2f position = _playerAircraft->getPosition();
		position.x = std::max(position.x, viewBounds.left + borderDistance);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
		position.y = std::max(position.y, viewBounds.top + borderDistance);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
		_playerAircraft->setPosition(position);
	}
	void World::drawLives()
	{


		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::Atlas);
		sf::IntRect textureRect(395,100, 39, 40);
		sf::Vector2f pos(_worldBounds.width, _worldBounds.top);
		for (int i = 1; i < _lives; i++)
		{
			std::unique_ptr<SpriteNode> frogLives(new SpriteNode(texture, textureRect));
			frogLives->setPosition(pos.x - 50, pos.y);
			_sceneLayers[Background]->attatchChild(std::move(frogLives));
			pos.x = pos.x - 50;
		}
	}
void World::addEnemy(SpawnPoint point) //puts the planes onto the vetor
{
	point.x = _spawnPosition.x + point.x;
	point.y = _spawnPosition.y - point.y;
	_enemySpawnPoints.push_back(point);
}
bool matchesCategories(SceneNode::pair& colliders, Category::type type1, Category::type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	if (type1 & category1 && type2 & category2)
		return true;

	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
		return false;
}
}