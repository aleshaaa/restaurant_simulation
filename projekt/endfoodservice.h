#pragma once
#include "event.h"
#include "restaurant.h"

class EndFoodService: public Event
{
public:
	EndFoodService(Restaurant* restaurant, Client * client, Waiter* waiter,Table* table, double time);
	void execute() override;

private:
	Waiter* waiter_;
	Table* table_;
	Restaurant *restaurant_;
	Client* client_;
};

