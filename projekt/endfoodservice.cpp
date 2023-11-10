#include "pch.h"
#include "endfoodservice.h"
#include <iostream>
#include "endeat.h"
#include "enddrinkservice.h"

EndFoodService::EndFoodService(Restaurant* restaurant, Client* client, Waiter* waiter, Table* table, double time):
	waiter_(waiter), table_(table), restaurant_(restaurant), client_(client)
{
	SetTime(time + client->GetTimeFood());
	SetExit(client->GetClientExit());
}


void EndFoodService::execute()
{
	std::cout << "-------------------->Zakonczenie obslugi przez kelnera(podanie dania glownego)." << std::endl;

	waiter_->GetCurrentGroup()->SetState(kServiced);
	waiter_->SetCurrentGroup(nullptr);
	restaurant_->NewEvent(new EndEat(restaurant_, client_, table_, GetTime()));
	std::cout<<"Grupa klientow o ID: "<<table_->GetCurrentGroup()->GetId()<<" otrzymala danie glowne." << std::endl;

	table_ = restaurant_->GetTableToService();
	if(table_ != nullptr)
	{
		client_ = table_->GetCurrentGroup();
		waiter_->SetCurrentGroup(client_);
		table_->SetNowServiced(true);
		if(client_->GetState() == kDrink)
		{
			restaurant_->NewEvent(new EndFoodService(restaurant_, client_, waiter_, table_, GetTime()));
			std::cout << "Grupa klientow o ID: " << client_->GetId() << "jest obslugiwana przez kelnera(podanie dania glownego)." << std::endl;
		}
		else
		{
			restaurant_->NewEvent(new EndDrinkService(restaurant_, client_, waiter_, table_, GetTime()));
			std::cout << "Grupa klientow o ID: " << client_->GetId() << "jest obslugiwana przez kelnera(podanie dania glownego)." << std::endl;
			////////STATYSTYKI
			restaurant_->AddDataToWaitingTimeForService(GetTime() - client_->GetTimeTable());
		}
	}
}
