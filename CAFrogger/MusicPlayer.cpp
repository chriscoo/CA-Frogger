#include "MusicPlayer.h"

namespace GEX {

	MusicPlayer::MusicPlayer() : _music(), _fileName(), _volume(100.f)
	{
		_fileName[MusicID::MenuTheme] = "Media/Music/MenuTheme.ogg";
		_fileName[MusicID::Missiontheme] = "Media/Music/MissionTheme.ogg";
	}

	void MusicPlayer::play(MusicID theme)
	{
		std::string filename = _fileName[theme];

		if (!_music.openFromFile(filename))
			throw std::runtime_error(filename + " Could not be loaded");

		_music.setVolume(_volume);
		_music.setLoop(true);
		_music.play();
	}

	void MusicPlayer::stop()
	{
		_music.stop();
	}

	void MusicPlayer::setPaused(bool paused)
	{
		if (paused)
			_music.pause();
		else
			_music.play();
	}

	void MusicPlayer::setVolume(float volume)
	{
		_volume = volume;
	}


}