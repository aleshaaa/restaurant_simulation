#include "pch.h"
#include "endbuffetservice.h"
#include <iostream>

EndBuffetService::EndBuffetService(Restaurant* restaurant, Client* client, double time): restaurant_(restaurant),
                                                                                     client_(client)
{
	SetTime( time + client->GetTimeBuffet());
	SetExit(client->GetClientExit());
}

void EndBuffetService::execute()
{
	std::cout << "-------------------->Zakonczenie obslugi przy bufecie." << std::endl;

	restaurant_->DeleteClientsFromBuffet(client_);
	restaurant_->AddClientsToCashier(client_, GetTime());
	restaurant_->AddSampleToAverageQueueLengthToCashier(restaurant_->GetSizeOfQueueToCashier(), GetTime());

	while(!restaurant_->QueueToBuffetEmpty() && restaurant_->FreeChairsInBuffet())
	{
		Client* client = restaurant_->GetFirstClientFromQueueToBuffet();
		restaurant_->AddClientsToBuffet(client, GetTime());
	}
}
