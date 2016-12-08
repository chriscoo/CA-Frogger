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
#include "Turtle.h"
#include "ParticleNode.h"
#include "SpriteNode.h"
#include "SoundPlayer.h"
#include "SoundNode.h"
#include "Log.h"
#include "Vehicle.h"
namespace GEX {

	bool matchesCategories(SceneNode::pair& colliders, Category::type type1, Category::type type2);
	World::World(sf::RenderWindow& window, SoundPlayer& soundPlayer) :
		_window(window),
		_worldView(window.getDefaultView()),
		_sceneGraph(),
		_sceneLayers(),
		_worldBounds(-250.f, 0.f, _worldView.getSize().x + 500, _worldView.getSize().y),
		_spawnPosition(_worldView.getSize().x / 2.f, _worldBounds.height - 20),
		_scrollSpeed(0),
		_queue(),
		_soundPlayer(soundPlayer),
		_playerAircraft(nullptr),
		_vehicles(),
		_lane1(_worldView.getSize().x+60, _worldBounds.height - 60),
		_lane2(_worldBounds.left, _worldBounds.height - 100),
		_lane3(_worldView.getSize().x+60, _worldBounds.height - 140),
		_lane4(_worldBounds.left, _worldBounds.height - 180),
		_lane5(_worldView.getSize().x+60, _worldBounds.height - 220),
		_river1(_worldView.getSize().x + 60, _worldBounds.height - 300),
		_river2(_worldBounds.left, _worldBounds.height - 340),
		_river3(_worldBounds.left, _worldBounds.height - 380),
		_river4(_worldView.getSize().x + 60, _worldBounds.height - 420),
		_river5(_worldBounds.left, _worldBounds.height - 460)
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

		handleCollisions();
		resetNPC();

		_sceneGraph.removeWrecks();
		
		_sceneGraph.update(deltaTime, getCommandQueue());
		adaptPlayerPosition();
		
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
		sf::Texture& texture = TextureHolder::getInstance().get(TextureID::Background);
		sf::IntRect textureRect(0, 0, 480, 600);
		
		//add background to sceneGraph
		std::unique_ptr<SpriteNode> background(new SpriteNode(texture, textureRect));
		background->setPosition(_worldView.getViewport().left, _worldView.getViewport().top);
		_sceneLayers[Background]->attatchChild(std::move(background));


		

		std::unique_ptr<SoundNode> soundeffectNode(new SoundNode(_soundPlayer));
		_sceneLayers[Air]->attatchChild(std::move(soundeffectNode));

		//frog
		std::unique_ptr<Frog> frog(new Frog());
		frog->setPosition(_spawnPosition);

		
		createCars();
		createLogs();
		createTurtles();
		

		_playerAircraft = frog.get();
		_sceneLayers[Air]->attatchChild(std::move(frog));
	}
	bool World::playerHasLives()
	{
		if (_playerAircraft->getLives() == 0)
			return false;
		else
			return true;
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
		sf::Vector2f rect(0, 0);
		return sf::FloatRect(rect, _worldView.getSize());
	}
	sf::FloatRect World::getBattleFieldBounds() const //gets the windows size plus some extra so we can spawn objects offscreen
	{
		return _worldBounds;
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
		std::set<SceneNode::pair> collisionPairs;
		_sceneGraph.checkSceneCollision(_sceneGraph, collisionPairs);
		bool isInRiver = true;//to tell if the player is on a log/turtle or if he is in the river
		for (SceneNode::pair pair : collisionPairs)
		{



			if (matchesCategories(pair, Category::Frog, Category::Car))//if the player collides with a car
			{
				auto& player = static_cast<Frog&>(*pair.first);
				auto& enemy = static_cast<Vehicle&>(*pair.second);
				//triggers the lives to redraw themselves with 1 less life
				
				//destrays then respawns the frog at the spawn point
				player.die();
				player.setPosition(_spawnPosition);
				player.setVelocity(0, 0);//removes the travel speed he gets from the log/turtle
				

			}
		
				if (matchesCategories(pair, Category::Frog, Category::Log))//if the player collides with a log so he travels with it
					{
						auto& player = static_cast<Frog&>(*pair.first);
						auto& log = static_cast<Log&>(*pair.second);
					
						player.setVelocity(log.getVelocity());
						isInRiver = false;
					}
				else if (matchesCategories(pair, Category::Frog, Category::Turtle))//if the player collides with a turtle so he travels with it
				{
					auto& player = static_cast<Frog&>(*pair.first);
					auto& turtle = static_cast<Turtle&>(*pair.second);
				
					player.setVelocity(turtle.getVelocity());
					isInRiver = false;
				}
		
	}
		
		
		
		if (_playerAircraft->getPosition().y < StartofRiver && isInRiver == true)//if you go into the river and are not on a log/tutle
		{
			//triggers the lives to redraw themselves with 1 less life
			_playerAircraft->die();
		}
		if (_playerAircraft->getPosition().y > StartofRiver)//resets his velocity if he goes back onto land
			_playerAircraft->setVelocity(0, 0);
		
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
		const float borderDistance = 20.f;

		sf::Vector2f position = _playerAircraft->getPosition();
		position.x = std::max(position.x, viewBounds.left + borderDistance);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
		position.y = std::max(position.y, viewBounds.top + borderDistance);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
		_playerAircraft->setPosition(position);
	}
	void World::addEnemy(SpawnPoint point) //puts the planes onto the vetor
{
	point.x = _spawnPosition.x + point.x;
	point.y = _spawnPosition.y - point.y;
	_enemySpawnPoints.push_back(point);
}
	void World::createFrog()
	{
		_playerAircraft->distroy();
		std::unique_ptr<Frog> frog(new Frog());
		frog->setPosition(_spawnPosition);

		_playerAircraft = frog.get();
		_playerAircraft->setVelocity(0, 0); //removes the travel speed he gets from the log/turtle
		_sceneLayers[Air]->attatchChild(std::move(frog));
	}
	void World::createCars()
{
	std::unique_ptr<Vehicle> carr(new Vehicle(Vehicle::Type::CarR));
	carr->setPosition(_lane1);
	carr->setSpawn(_lane1);
	_sceneLayers[Air]->attatchChild(std::move(carr));

	std::unique_ptr<Vehicle> carr2(new Vehicle(Vehicle::Type::CarR));
	carr2->setPosition(_lane1.x+75, _lane1.y);
	carr2->setSpawn(carr2->getPosition());
	_sceneLayers[Air]->attatchChild(std::move(carr2));

	std::unique_ptr<Vehicle> carl(new Vehicle(Vehicle::Type::CarL));
	carl->setPosition(_lane2);
	carl->setSpawn(_lane2);
	_sceneLayers[Air]->attatchChild(std::move(carl));

	std::unique_ptr<Vehicle> carl2(new Vehicle(Vehicle::Type::CarL));
	carl2->setPosition(_lane2.x + 100, _lane2.y);
	carl2->setSpawn(carl2->getPosition());
	_sceneLayers[Air]->attatchChild(std::move(carl2));

	std::unique_ptr<Vehicle> rc(new Vehicle(Vehicle::Type::RaceCar));
	rc->setPosition(_lane3);
	rc->setSpawn(_lane3);
	_sceneLayers[Air]->attatchChild(std::move(rc));

	std::unique_ptr<Vehicle> rc2(new Vehicle(Vehicle::Type::RaceCar));
	rc2->setPosition(_lane3.x + 80, _lane3.y);
	rc2->setSpawn(rc2->getPosition());
	_sceneLayers[Air]->attatchChild(std::move(rc2));

	std::unique_ptr<Vehicle> trac(new Vehicle(Vehicle::Type::Tractor));
	trac->setPosition(_lane4);
	trac->setSpawn(_lane4);
	_sceneLayers[Air]->attatchChild(std::move(trac));

	std::unique_ptr<Vehicle> trac2(new Vehicle(Vehicle::Type::Tractor));
	trac2->setPosition(_lane4.x + 130, _lane4.y);
	trac2->setSpawn(trac2->getPosition());
	_sceneLayers[Air]->attatchChild(std::move(trac2));

	std::unique_ptr<Vehicle> truck(new Vehicle(Vehicle::Type::Truck));
	truck->setPosition(_lane5);
	truck->setSpawn(_lane5);
	_sceneLayers[Air]->attatchChild(std::move(truck));

	std::unique_ptr<Vehicle> truck2(new Vehicle(Vehicle::Type::Truck));
	truck2->setPosition(_lane5.x + 130, _lane5.y);
	truck2->setSpawn(truck2->getPosition());
	_sceneLayers[Air]->attatchChild(std::move(truck2));
}
	void World::createLogs()
	{

		std::unique_ptr<Log> logS(new Log(Log::Type::Short));
		logS->setPosition(_river2);
		logS->setSpawn(_river2);
		_sceneLayers[Air]->attatchChild(std::move(logS));
		
		std::unique_ptr<Log> logL(new Log(Log::Type::Long));
		logL->setPosition(_river3);
		logL->setSpawn(_river3);
		_sceneLayers[Air]->attatchChild(std::move(logL));
		
		std::unique_ptr<Log> logS2(new Log(Log::Type::Short));
		logS2->setPosition(_river5);
		logS2->setSpawn(_river5);
		_sceneLayers[Air]->attatchChild(std::move(logS2));
	}
	void World::createTurtles()
	{
		std::unique_ptr<Turtle> turtleS(new Turtle(Turtle::Type::Turtle2));
		turtleS->setPosition(_river1);
		turtleS->setSpawn(_river1);
		_sceneLayers[Air]->attatchChild(std::move(turtleS));

		std::unique_ptr<Turtle> turtleL(new Turtle(Turtle::Type::Turtle3));
		turtleL->setPosition(_river4);
		turtleL->setSpawn(_river4);
		_sceneLayers[Air]->attatchChild(std::move(turtleL));


	}
	void World::resetNPC()
	{
		Command command;
		command.category = Category::Car | Category::Log | Category::Turtle;
		command.action = derivedAction<Entity>([this](Entity& e, sf::Time)
		{
			if (!getBattleFieldBounds().intersects(e.getBoundingRect()))
				e.setPosition(e.getSpawn());
			
		});

		_queue.push(command);
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