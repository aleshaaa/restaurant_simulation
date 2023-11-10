#include "pch.h"
#include "manager.h"
#include <iostream>


Manager::Manager(): current_group_(nullptr)
{
	std::cout << "Utworzono managera" << std::endl;
}

Manager::~Manager()
{
	std::cout << "Usunieto managera" << std::endl;
	delete current_group_;
}

Client* Manager::GetCurrentGroup() const
{
	return current_group_;
}

void Manager::SetCurrentGroup(Client *client)
{
	current_group_ = client;
}

int Manager::GetTimeToTable()
{
	return time_to_table_;
}


