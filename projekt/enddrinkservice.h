#pragma once
#include "waiter.h"
#include "restaurant.h"

class EndDrinkService: public Event
{
public:
	EndDrinkService(Restaurant* restaurant, Client* client, Waiter* waiter, Table* table, double time);
	void execute() override;
private:
	Restaurant* restaurant_;
	Waiter* waiter_;
	Table* table_;
	Client* client_;
};