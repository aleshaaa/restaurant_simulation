#include "pch.h"
#include "buffet.h"
#include  <iostream>


Buffet::Buffet(const int chairs): number_of_buffets_(chairs)
{
	std::cout << "Utworzono buffet" << std::endl;
}

Buffet::~Buffet()
{
	for (auto i : vector_of_clients_) delete i;
	std::cout << "Usunieto buffet" << std::endl;

}

void Buffet::AddCurrentGroupToBuffet(Client* client)
{
	number_of_buffets_busy_ += client->GetNumberOfClients();
	vector_of_clients_.push_back(client);
}

void Buffet::DeleteCurrentGroupToBuffet(Client* client)
{
	for (int i=0; i < vector_of_clients_.size(); i++)
	{
		if(vector_of_clients_[i] == client)
		{
			number_of_buffets_busy_ -= client->GetNumberOfClients();
			vector_of_clients_.erase(vector_of_clients_.begin() + i);
			break;
		}
	}
}


bool Buffet::BuffetBusy(int number_of_clients)
{
	return number_of_clients <= number_of_buffets_ - number_of_buffets_busy_;
}

int Buffet::GetNumberOfBuffetBusy()
{
	return number_of_buffets_busy_;
}

void Buffet::SetNumberOfBuffetBusy(int number)
{
	number_of_buffets_busy_ -= number;
}
