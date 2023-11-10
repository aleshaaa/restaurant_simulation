#include "pch.h"
#include "alarm.h"
#include <iostream>
#include "newclient.h"

Alarm::Alarm(Restaurant* restaurant, Client* client, double time): restaurant_(restaurant), client_(client)
{
	SetTime(time + normal_dist_alarm_(generator_));
}

void Alarm::execute()
{
	restaurant_->NewEvent(new Alarm(restaurant_, client_, GetTime()));
	std::cout << "--------------------------------------ALARM--------------------------------------" << std::endl;
	std::cout << "Restauracje opuscilo " << restaurant_->GetNumberOfClientExit() << " grup klientow." << std::endl;
	
	restaurant_->CleanQueueOfEvents();
	restaurant_->CleanQueueToTables();
	restaurant_->CleanQueueToBuffet();
	restaurant_->CleanQueueToCashier();
	restaurant_->CleanManager();
	restaurant_->CleanWaiters();
	restaurant_->CleanCashiers();
	restaurant_->CleanTables();
	restaurant_->CleanBuffet();
	restaurant_->ClientsExit();
	/*
	std::ofstream data;
	data.open("dane.txt", std::ios_base::app);
	data << restaurant_->number_of_groups_ << std::endl;
	data.close();
	*/
}
