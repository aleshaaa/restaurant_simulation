#pragma once
#include "client.h"
#include "table.h"
#include "restaurant.h"

class EndManagerService: public Event
{
public:
	EndManagerService(Restaurant* restaurant, Client* client, Table* table, double time);
	void execute() override;

private:
	Restaurant* restaurant_;
	Table* table_;
	Client* client_;
};

