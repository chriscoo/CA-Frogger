/**
@file CommandQueue
@author  Chris Arsenault Chris.arsenault06@gmail.com
@version 1.0

@section LICENSE

This software is based on the material accompanying the book "SFML Game Development" see License.txt

Additions and modifications are my sole work for prog 1266

@section DESCRIPTION

<your description of the purpose of this file here>

*/

#include "CommandQueue.h"
namespace GEX {



	void CommandQueue::push(const Command & command)
	{
		_queue.push(command);
	}

	Command CommandQueue::pop()
	{
		auto result = _queue.front();
		_queue.pop();
		return result;
	}

	bool CommandQueue::isEmpty() const
	{
		return _queue.empty();
	}

}


