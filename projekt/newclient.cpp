#include "pch.h"
#include "newclient.h"
#include <iostream>
#include "alarm.h"
#include "endmanagerservice.h"


NewClient::NewClient(Restaurant* restaurant, Client *client, const double time): restaurant_(restaurant), client_(client)
{
	SetTime(time + client->GetNewGroupTime());
	SetExit(client->GetClientExit());
}

void NewClient::execute()
{
	std::cout << "-------------------->Pojawienie sie nowej grupy klientow." << std::endl;
	restaurant_->NewEvent(new NewClient(restaurant_, client_, GetTime()));
	Client* client = new Client();
	
	//ALARM
	if (client->GetProbabilityExit() <= 30)
	{
		client->SetClientExit(true);
		restaurant_->AddClientsToExit(client);
	}
	else client->SetClientExit(false);

	restaurant_->SetNumberOfGroups(restaurant_->GetNumberOfGroups() + 1);
	restaurant_->AddSampleToAverageQueueLengthToTable(restaurant_->GetSizeOfQueueToTables(), GetTime());

	/*
	std::ofstream data;
	data.open("dane.txt", std::ios_base::app);
	data << restaurant_->number_of_groups_ << std::endl;
	data.close();
	*/

	if (client->GetChoice() == 1)
	{
		client->SetTimeStart(GetTime());
		restaurant_->AddClientToManager(client, GetTime());
	}
	else
	{
		restaurant_->AddClientsToBuffet(client, GetTime());
	}
}


