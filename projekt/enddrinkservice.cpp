#include "pch.h"
#include "enddrinkservice.h"
#include <iostream>
#include "endfoodservice.h"

EndDrinkService::EndDrinkService(Restaurant* restaurant, Client* client, Waiter* waiter, Table* table, double time):
	restaurant_(restaurant), waiter_(waiter), table_(table), client_(client)
{
	SetTime(time + client->GetTimeDrink());
	SetExit(client->GetClientExit());
}

void EndDrinkService::execute()
{
	std::cout << "-------------------->Zakonczenie obslugi przez kelnera(podanie napoju)" << std::endl;
	waiter_->GetCurrentGroup()->SetState(kDrink);
	waiter_->SetCurrentGroup(nullptr);
	table_->SetNowServiced(false);
	table_->SetTimeOfLastService(GetTime());
	table_ = restaurant_->GetTableToService();

	if(table_ != nullptr)
	{
		client_ = table_->GetCurrentGroup();
		waiter_->SetCurrentGroup(client_);
		table_->SetNowServiced(true);

		if(client_->GetState() == kDrink)
		{
			restaurant_->NewEvent(new EndFoodService(restaurant_, client_, waiter_, table_, GetTime()));
			std::cout << "Grupa klientow o ID: " << client_->GetId() << "jest obslugiwana przez kelnera (podanie dania glownego)." << std::endl;
		}
		else
		{
			restaurant_->NewEvent(new EndDrinkService(restaurant_, client_, waiter_, table_, GetTime()));
			std::cout << "Grupa klientow o ID: " << client_->GetId() << "jest obslugiwana przez kelnera (podanie napoju)." << std::endl;

			//ŒREDNI CZAS OCZEKIWANIA NA OBS£UGE PRZEZ KELNERA
			restaurant_->AddDataToWaitingTimeForService(GetTime() - client_->GetTimeTable());
		}
	}
}
