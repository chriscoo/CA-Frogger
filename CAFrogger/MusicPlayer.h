#pragma once
#include <map>
#include <cassert>
#include <SFML\Audio\Music.hpp>
namespace GEX {
	enum class MusicID {
		MenuTheme,
		Missiontheme
	};
	class MusicPlayer
	{
	public:
		MusicPlayer();
		MusicPlayer(const MusicPlayer&) = delete;
		MusicPlayer&	operator =(const MusicPlayer&) = delete;
		void play(MusicID theme);
		void stop();

		void setPaused(bool paused);
		void setVolume(float volume);

	private:
		sf::Music   _music;
		std::map<MusicID, std::string> _fileName;
			float _volume;

	};
}

