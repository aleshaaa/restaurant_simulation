#include "pch.h"
#include "endmanagerservice.h"
#include <iostream>
#include "enddrinkservice.h"

EndManagerService::EndManagerService(Restaurant* restaurant, Client* client, Table* table, double time):
	restaurant_(restaurant), table_(table),
	client_(client)
{
	SetTime(time + restaurant_->GetTimeToTable());
	SetExit(client->GetClientExit());
}

void EndManagerService::execute()
{
	std::cout << "-------------------->Zakonczenie umieszczania grupy przy stole przez kierownika sali."<<std::endl;
	//////OBLICZENIA
	restaurant_->AddDataToWaitingTimeForTables(GetTime() - client_->GetTimeStart());
	restaurant_->AddSampleToAverageQueueLengthToTable(restaurant_->GetSizeOfQueueToTables(), GetTime());

	client_->SetTimeTable(GetTime()); 
	table_->SetCurrentGroup(client_);
	table_->SetTimeOfLastService(GetTime());
	std::cout << "Grupa klientow o ID: " << client_->GetId() << " podchodzi do stolika " << table_->GetNumberOfChairs() << " -osobowego." << std::endl;
	restaurant_->SetCurrentGroupManager(nullptr);
	Waiter* waiter = restaurant_->GetAvailableWaiter();


	if(waiter!=nullptr)
	{
		waiter->SetCurrentGroup(client_);
		table_->SetNowServiced(true);
		restaurant_->NewEvent(new EndDrinkService(restaurant_, client_, waiter, table_, GetTime()));
		std::cout << "Grupa klientow o ID: " << client_->GetId() << " jest obslugiwana przez kelnera (napoj)." << std::endl;
	}
	else std::cout << "Grupa klientow o ID: " << client_->GetId() << " czeka na obsluge przez kelnera." << std::endl;

	
	if(!restaurant_->QueueToTablesEmpty() && restaurant_->GetCurrentGroupManager() == nullptr)
	{
		table_ = restaurant_->FindTable();
		if(table_ != nullptr)
		{
			
			client_ = restaurant_->GetFirstClientFromQueueToTable(table_->GetNumberOfChairs());
			if(client_ !=nullptr)
			{
				restaurant_->SetCurrentGroupManager(client_);
				restaurant_->NewEvent(new EndManagerService(restaurant_, client_, table_, GetTime()));
				std::cout << "Grupa klientow o ID: " << client_->GetId() << " jest prowadzona przez kierownika sali do stolika "
					<< table_->GetNumberOfChairs() << "-sobowego." << std::endl;
			}
		}
	}
}
