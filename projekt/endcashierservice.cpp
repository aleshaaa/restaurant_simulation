#include "pch.h"
#include "endcashierservice.h"
#include <iostream>

EndCashierService::EndCashierService(Restaurant* restaurant, Client* client, Cashier* cashier, double time):
	cashier_(cashier), restaurant_(restaurant), client_(client)
{
	SetTime(time + client->GetTimeCashier());
	SetExit(client->GetClientExit());
}

void EndCashierService::execute()
{
	std::cout << "-------------------->Zakonczenie obslugi przez kasjera." << std::endl;

	restaurant_->CheckClientExitInCashier(cashier_->GetCurrentGroup());		//usuniecie z wektora klientow podatnych na alarm grup, ktore zakonczyly wizyte w restauracji
	cashier_->DeleteCurrentGroup();
	cashier_->SetCurrentGroup(nullptr);
	restaurant_->SetNumberOfGroups(restaurant_->GetNumberOfGroups() - 1);
	restaurant_->AddSampleToAverageQueueLengthToCashier(restaurant_->GetSizeOfQueueToCashier(), GetTime());

	/*
	std::ofstream data;
	data.open("dane.txt", std::ios_base::app);
	data << restaurant_->number_of_groups_ << std::endl;
	data.close();
	*/
	if (!restaurant_->QueueToCashierEmpty())
	{
		client_ = restaurant_->GetFirstClientFromQueueToCashier();
		cashier_->SetCurrentGroup(client_);
		restaurant_->NewEvent(new EndCashierService(restaurant_, client_, cashier_, GetTime()));
	}
}
