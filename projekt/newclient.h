#pragma once
#include "event.h"
#include "restaurant.h"

class NewClient : public Event
{
public:
	NewClient(Restaurant* restaurant, Client* client, double time);
	void execute() override;

private:
	Restaurant *restaurant_;
	Client* client_;
};

