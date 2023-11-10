#include "pch.h"
#include "event.h"

void Event::execute()
{
}

double Event::GetTime() 
{
	return time_;
}

void Event::SetTime(double time)
{
	time_ = time;
}

bool Event::GetExit()
{
	return exit_;
}

void Event::SetExit(bool exit)
{
	exit_ = exit;
}


