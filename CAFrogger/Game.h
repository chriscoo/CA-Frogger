#pragma once
#include <SFML\Graphics.hpp>
#include "TextureHolder.h"
#include "World.h"
#include "PlayerControl.h"
namespace GEX
{
	class Game
	{
	public:
		Game();
		void run();

	private:
	
		void processInputs(); //real time events(movement)
		void update(sf::Time dt);
		void render();
		void updateStats(sf::Time dt);
		
		
		//sf::RectangleShape getDrawableBounds();
	private:

		sf::RenderWindow	_window;

		World				_world;
		PlayerControl		_player;

		sf::Font _font;
		sf::Text _statText;
		

		
	};
}

