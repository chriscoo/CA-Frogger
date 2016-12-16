
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
#pragma once
#include <SFML/Graphics.hpp>
#include "SceneNode.h"
#include "CommandQueue.h"
#include <vector>
#include <algorithm>
#include <array>

#include "Vehicle.h"

#include "SpriteNode.h"
namespace GEX {

	class Frog;
	class TextNode;
	class World
	{
	public:

		explicit		World(sf::RenderWindow& window);
						~World();
		void			update(sf::Time deltaTime);
		void			draw();
		//Plane*			getPlayerAircraft() { return _playerAircraft; }
		CommandQueue&	getCommandQueue();

		void			buildScene();
		
		bool			playerHasLives();
		bool			hasAlivePlayer() const;
		bool			hasReachedFinish() const;

	private:

		sf::FloatRect getViewBounds() const;
		sf::FloatRect getBattleFieldBounds() const;

		
		
		
		
		
		void handleCollisions();
	
		void adaptPlayerPosition();
		enum _Layers
		{
			Background,
			Air,
			LayerCount
		};
		
		
		void createFrog();
		void createCars();
		void createLogs();
		void createTurtles();
		void resetNPC();
		void updateScore();
		float checkHighestPos();
	private:
		sf::RenderWindow&					_window;
		sf::View							_worldView;
		SceneNode							_sceneGraph;
		std::array<SceneNode*, LayerCount>	_sceneLayers;
		CommandQueue						_queue;
		sf::FloatRect						_worldBounds;
		sf::Vector2f						_spawnPosition;
		Frog*								_playerFrog;
		TextNode*							_score;
		

		std::vector<Vehicle*>				_vehicles;
		float								_highestPos;
		
		int									_points;
		sf::Vector2f 						_lane1;
		sf::Vector2f 						_lane2;
		sf::Vector2f 						_lane3;
		sf::Vector2f 						_lane4;
		sf::Vector2f 						_lane5;
		const int StartofRiver = 320; //where the middle section of grass ends and the river begins 
		sf::Vector2f						_river1;
		sf::Vector2f						_river2;
		sf::Vector2f						_river3;
		sf::Vector2f						_river4;
		sf::Vector2f						_river5;
							
	};
}
