#pragma once
#include "event.h"
#include "restaurant.h"

class EndCashierService final : public Event
{
public:
	EndCashierService(Restaurant *restaurant, Client* client, Cashier* cashier, double time);
	void execute() override;

private:
	Cashier* cashier_;
	Restaurant* restaurant_;
	Client* client_;
};

