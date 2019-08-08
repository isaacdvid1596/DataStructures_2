#include "CounterClock.h"



CounterClock::CounterClock()
{

}


CounterClock::~CounterClock()
{

}

void CounterClock::startCounter()
{
	 start = std::chrono::system_clock::now();
}
void CounterClock::endCounter()
{
	 end = std::chrono::system_clock::now();
}
void CounterClock::resetCounter()
{
	start = end = {};
	sLength = std::chrono::seconds::zero();
}
double CounterClock::printTimeCounter()
{
	sLength = start - end;
	return sLength.count();
}
