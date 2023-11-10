#pragma once
#include "restaurant.h"

class Alarm: public Event
{
public:
	Alarm(Restaurant* restaurant, Client* client, double time);
	void execute() override;

private:
	Restaurant* restaurant_;
	Client* client_;

	//GENERATOR DLA ALARMU
	std::default_random_engine generator_ = std::default_random_engine(5000000);
	std::normal_distribution<double> normal_dist_alarm_ = std::normal_distribution <double>(4200.0, 50.0);
};

