#pragma once
#include "restaurant.h"

class EndBuffetService: public Event
{
public:
	EndBuffetService(Restaurant* restaurant, Client* client, double time);
	void execute() override;

private:
	Restaurant* restaurant_;
	Client* client_;
};

