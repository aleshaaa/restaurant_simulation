#include "pch.h"
#include "cashier.h"
#include <iostream>


Cashier::Cashier(): current_group_(nullptr)
{
	std::cout << "Utworzono kasjera" << std::endl;
}


Cashier::~Cashier()
{
	delete current_group_;
	std::cout << "Usunieto kasjera" << std::endl;
}

void Cashier::SetCurrentGroup(Client* client)
{
	current_group_ = client;
}

Client* Cashier::GetCurrentGroup()
{
	return current_group_;
}

void Cashier::DeleteCurrentGroup()
{
	delete current_group_;
}
