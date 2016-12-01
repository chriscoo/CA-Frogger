/**
@file Category.h
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/
#pragma once
namespace GEX {

	namespace Category {
		enum type {
			none = 0,
			SceneAirLayer = 1 << 0,
			Frog = 1 << 1,
			Log = 1 << 2,
			Turtle = 1 << 3,
			Car = 1 << 4,
			LandingZone = 1 << 5,
			ParticleSystem = 1 << 6,
			SoundEffect = 1 << 7,
			

			ThingsPlayerCollidesWith = Log | Turtle | LandingZone | Car,
			ThingsEnemyCollidesWith = Frog
		};

	}


}