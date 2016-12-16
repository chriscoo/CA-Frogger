/**
@file DataTables
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "DataTables.h"


namespace GEX {
	std::map<Vehicle::Type, VehicleData> InitializeVehicleData()
	{
		std::map<Vehicle::Type, VehicleData> data;

		data[Vehicle::Type::CarL].speed = 50.f;
		data[Vehicle::Type::CarL].textureRect = sf::IntRect(69, 100, 37, 37);

		data[Vehicle::Type::CarR].speed = -50.f;
		data[Vehicle::Type::CarR].textureRect = sf::IntRect(139, 100, 38, 39);

		data[Vehicle::Type::RaceCar].speed = -60.f;
		data[Vehicle::Type::RaceCar].textureRect = sf::IntRect(1, 62, 35, 29);

		data[Vehicle::Type::Tractor].speed = 35.f;
		data[Vehicle::Type::Tractor].textureRect = sf::IntRect(214, 62, 33, 33);

		data[Vehicle::Type::Truck].speed = -35.f;
		data[Vehicle::Type::Truck].textureRect = sf::IntRect(293, 1, 61, 28);


		return data;
	}

	std::map<Turtle::Type, TurtleData> InitializeTurtleData()
	{
		std::map<Turtle::Type, TurtleData> data;

		data[Turtle::Type::Turtle2].speed = -60.f;
		data[Turtle::Type::Turtle2].textureRect = sf::IntRect(125, 1, 65, 26);

		data[Turtle::Type::Turtle3].speed = -60.f;
		data[Turtle::Type::Turtle3].textureRect = sf::IntRect(192, 1, 99, 26);


		return data;
	}

	std::map<Log::Type, LogData> InitializeLogData()
	{
		std::map<Log::Type, LogData> data;

		data[Log::Type::Short].speed = 60.f;
		data[Log::Type::Short].textureRect = sf::IntRect(198, 31, 93, 29);

		data[Log::Type::Long].speed = 90.f;
		data[Log::Type::Long].textureRect = sf::IntRect(1, 31, 195, 28);


		return data;
	}

}