
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
#include <SFML\Graphics.hpp>
#include "SceneNode.h"
#include "CommandQueue.h"
#include <vector>
#include <algorithm>
#include <array>
#include "Plane.h"
#include "SoundPlayer.h"
namespace GEX {

	class Frog;
	
	class World
	{
	public:

		explicit		World(sf::RenderWindow& window, SoundPlayer& soundPlayer);
						~World();
		void			update(sf::Time deltaTime);
		void			draw();
		//Plane*			getPlayerAircraft() { return _playerAircraft; }
		CommandQueue&	getCommandQueue();

		void			buildScene();
		

		bool			hasAlivePlayer() const;
		bool			hasReachedFinish() const;

	private:

		sf::FloatRect getViewBounds() const;
		sf::FloatRect getBattleFieldBounds() const;

		void updateSounds();
		void spawnEnemies();
		void addEnemies();
		void addEnemy(Plane::Type type, float relx, float rely);
		void guideMissiles();
		void handleCollisions();
		void destroyEntitiesOutsideWorldView();
		void adaptPlayerPosition();
		void drawLives();
		enum _Layers
		{
			Background,
			Air,
			LayerCount
		};
		struct SpawnPoint{
			SpawnPoint(Plane::Type _type, float _x, float _y) : type(_type), x(_x), y(_y) {}
			Plane::Type		type;
			float			x;
			float			y;

		};
		void addEnemy(SpawnPoint point);
		

	private:
		sf::RenderWindow&					_window;
		sf::View							_worldView;
		SceneNode							_sceneGraph;
		SoundPlayer&						_soundPlayer;
		std::array<SceneNode*, LayerCount>	_sceneLayers;
		CommandQueue						_queue;
		sf::FloatRect						_worldBounds;
		sf::Vector2f						_spawnPosition;
		float								_scrollSpeed;
		Frog*								_playerAircraft;
		std::vector<SpawnPoint>				_enemySpawnPoints;
		std::vector<Plane*>					_activeEnemies;

		int									_lives;
		bool								_validLives;

	};
}
