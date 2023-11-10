#pragma once
#include "event.h"
#include "restaurant.h"

class EndEat: public Event
{
public:
	EndEat(Restaurant* restaurant, Client* client, Table* table, double time);
	void execute() override;

private:
	Restaurant* restaurant_;
	Table* table_;
	Client* client_;
};

