#include "pch.h"
#include "endeat.h"
#include <iostream>
#include "endmanagerservice.h"

EndEat::EndEat(Restaurant* restaurant, Client* client, Table* table, double time): restaurant_(restaurant), table_(table),
                                                                                client_(client)
{
	SetTime(time + client->GetTimeEat());
	SetExit(client->GetClientExit());
}

void EndEat::execute()
{
	std::cout << "-------------------->Zakonczenie konsumpcji przy stoliku." << std::endl;
	client_ = table_->GetCurrentGroup();
	table_->SetNowServiced(false);
	table_->SetCurrentGroup(nullptr);
	restaurant_->AddClientsToCashier(client_, GetTime());
	restaurant_->AddSampleToAverageQueueLengthToTable(restaurant_->GetSizeOfQueueToTables(), GetTime());
	restaurant_->AddSampleToAverageQueueLengthToCashier(restaurant_->GetSizeOfQueueToCashier(), GetTime());

	if(!restaurant_->QueueToTablesEmpty() && restaurant_->GetCurrentGroupManager() == nullptr)
	{
		if(table_ != nullptr)
		{
			client_ = restaurant_->GetFirstClientFromQueueToTable(table_->GetNumberOfChairs());
			if(client_ !=nullptr)
			{
				restaurant_->SetCurrentGroupManager(client_);
				restaurant_->NewEvent(new EndManagerService(restaurant_, client_, table_, GetTime()));
				std::cout << "Grupa klientow o ID: " << client_->GetId() << " udaje siê do managera." << std::endl;
			}
		}
	}
}
