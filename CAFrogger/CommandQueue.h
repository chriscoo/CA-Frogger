/**
@file CommandQueue.h
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#pragma once
#include <queue>
#include "Command.h"
namespace GEX {
	class CommandQueue
	{
	public:
		void				push(const Command& command);
		Command				pop();
		bool				isEmpty() const;

	private:
		std::queue<Command> _queue;
	};
}

