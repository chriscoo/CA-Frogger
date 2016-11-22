#include "SoundBufferHolder.h"
#include <cassert>
namespace GEX
{
	SoundBufferHolder* SoundBufferHolder::_instance = nullptr;
	SoundBufferHolder& SoundBufferHolder::getInstance()
	{
		if (!SoundBufferHolder::_instance)
			SoundBufferHolder::_instance = new SoundBufferHolder();
		return *SoundBufferHolder::_instance;
	}
	void SoundBufferHolder::load(SoundEffectID id, const std::string & path)
	{
		std::unique_ptr<sf::SoundBuffer> texture(new sf::SoundBuffer);
		if (!texture->loadFromFile(path))
			throw std::runtime_error("Load failed - " + path);
		auto rc = _soundEffects.insert(std::make_pair(id, std::move(texture)));
		if (!rc.second)
			assert(0); // big problems if insert fails
	}
	sf::SoundBuffer& SoundBufferHolder::get(SoundEffectID id) const
	{
		auto found = _soundEffects.find(id);
		assert(found != _soundEffects.end());  // find returns an iterator to pair in map
		return *found->second; // de-reference iterator and return pointer by reference
	}
}
