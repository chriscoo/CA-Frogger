/**
@file DataTable.h
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/
#pragma once
#include "TextureHolder.h"
#include "Utility.h"
#include "Vehicle.h"
#include "Turtle.h"
#include "Log.h"
#include <map>
#include <vector>
namespace GEX {


	

	struct VehicleData {
		
		sf::IntRect					textureRect;
		float						speed;

	};

	struct LogData {
		sf::IntRect					textureRect;
		float						speed;

	};


	struct TurtleData {
		sf::IntRect					textureRect;
		float						speed;

	};
	std::map<Log::Type, LogData> InitializeLogData();
	std::map<Vehicle::Type, VehicleData> InitializeVehicleData();
	std::map<Turtle::Type, TurtleData> InitializeTurtleData();
}
