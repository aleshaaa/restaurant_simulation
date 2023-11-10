#include "pch.h"
#include "waiter.h"
#include <iostream>


Waiter::Waiter(): current_group_(nullptr)
{
	std::cout << "Utworzono kelnera" << std::endl;
}

Waiter::~Waiter()
{
	std::cout << "Usunieto kelnera" << std::endl;
}

void Waiter::SetCurrentGroup(Client* client)
{
	current_group_ = client;
}

Client* Waiter::GetCurrentGroup()
{
	if (current_group_ != nullptr) return current_group_;
	return nullptr;
}
