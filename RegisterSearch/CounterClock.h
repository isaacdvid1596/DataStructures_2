#pragma once
#include <chrono>
#include <iostream>

using namespace std::chrono;

class CounterClock
{
public:
	CounterClock();
	~CounterClock();
	void startCounter();
	void endCounter();
	void resetCounter();
	double printTimeCounter();
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<double> sLength;
};

