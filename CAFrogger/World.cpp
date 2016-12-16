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
#include "TextureHolder.h"
#include "TextNode.h"
#include "Frog.h"
#include "Turtle.h"
#include "SpriteNode.h"
#include "Log.h"
#include "Vehicle.h"
namespace GEX {

	bool matchesCategories(SceneNode::pair& colliders, Category::type type1, Category::type type2);
	World::World(sf::RenderWindow& window) :
		_window(window),
		_worldView(window.getDefaultView()),
		_sceneGraph(),
		_sceneLayers(),
		_worldBounds(-250.f, 0.f, _worldView.getSize().x + 500, _worldView.getSize().y),
		_spawnPosition(_worldView.getSize().x / 2.f, _worldBounds.height - 20),
		_queue(),
		
		_playerFrog(nullptr),
		_vehicles(),
		_score(nullptr),
		_points(0),
		_highestPos(_worldBounds.height),
		_lane1(_worldView.getSize().x + 60, _worldBounds.height - 60),
		_lane2(_worldBounds.left, _worldBounds.height - 100),
		_lane3(_worldView.getSize().x + 60, _worldBounds.height - 140),
		_lane4(_worldBounds.left, _worldBounds.height - 180),
		_lane5(_worldView.getSize().x + 60, _worldBounds.height - 220),
		_river1(_worldView.getSize().x + 60, _worldBounds.height - 300),
		_river2(_worldBounds.left, _worldBounds.height - 340),
		_river3(_worldBounds.left, _worldBounds.height - 380),
		_river4(_worldView.getSize().x + 60, _worldBounds.height - 420),
		_river5(_worldBounds.left, _worldBounds.height - 460)
	{

		buildScene();
		_score->setPosition(220.f, 5.f);

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
		updateScore();
		checkHighestPos();

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


		std::unique_ptr<TextNode> text(new TextNode("Score: "));
		_score = text.get();
		_sceneLayers[Background]->attatchChild(std::move(text));

		//frog



		createCars();
		createLogs();
		createTurtles();


		std::unique_ptr<Frog> frog(new Frog());
		frog->setPosition(_spawnPosition);



		_playerFrog = frog.get();
		_sceneLayers[Air]->attatchChild(std::move(frog));
	}
	bool World::playerHasLives()
	{
		if (_playerFrog->getLives() == 0)
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
			if (matchesCategories(pair, Category::Frog, Category::Turtle))//if the player collides with a turtle so he travels with it
			{
				auto& player = static_cast<Frog&>(*pair.first);
				auto& turtle = static_cast<Turtle&>(*pair.second);

				player.setVelocity(turtle.getVelocity());
				isInRiver = false;
			}

		}



		if (_playerFrog->getPosition().y < StartofRiver && isInRiver == true)//if you go into the river and are not on a log/tutle
		{
			//triggers the lives to redraw themselves with 1 less life
			_playerFrog->die();
			_playerFrog->setPosition(_spawnPosition);
			_playerFrog->setVelocity(0, 0);//removes the travel speed he gets from the log/turtle
		}
		if (_playerFrog->getPosition().y > StartofRiver)//resets his velocity if he goes back onto land
			_playerFrog->setVelocity(0, 0);

	}
	
	void World::adaptPlayerPosition()
	{
		// Keep player's position inside the screen bounds, at least borderDistance units from the border
		sf::FloatRect viewBounds = getViewBounds();
		const float borderDistance = 20.f;

		sf::Vector2f position = _playerFrog->getPosition();
		position.x = std::max(position.x, viewBounds.left + borderDistance);
		position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
		position.y = std::max(position.y, viewBounds.top + borderDistance);
		position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
		_playerFrog->setPosition(position);
	}
	void World::createFrog()
	{
		_playerFrog->distroy();
		std::unique_ptr<Frog> frog(new Frog());
		frog->setPosition(_spawnPosition);

		_playerFrog = frog.get();
		_playerFrog->setVelocity(0, 0); //removes the travel speed he gets from the log/turtle
		_sceneLayers[Air]->attatchChild(std::move(frog));
	}
	void World::createCars()
	{
		std::unique_ptr<Vehicle> carr(new Vehicle(Vehicle::Type::CarR));
		carr->setPosition(_lane1);
		carr->setSpawn(_lane1);
		_sceneLayers[Air]->attatchChild(std::move(carr));

		std::unique_ptr<Vehicle> carr2(new Vehicle(Vehicle::Type::CarR));
		carr2->setPosition(_lane1.x + 75, _lane1.y);
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
	void World::updateScore()
	{
		if (_playerFrog->getPosition().y < _highestPos)
		{

			_score->setText("SCORE: " + std::to_string(_points));
			_points = _points + 20;
		}


	}
	float World::checkHighestPos()
	{
		if (_playerFrog->getPosition().y < _highestPos)
			_highestPos = _playerFrog->getPosition().y;

		return _highestPos;
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