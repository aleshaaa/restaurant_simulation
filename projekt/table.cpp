#include "pch.h"
#include "table.h"
#include <iostream>

Table::Table(const int chairs): now_serviced_(false), current_group_(nullptr)
{
	number_of_chairs_ = chairs;
	std::cout << "Utworzono stolik" << std::endl;
}

Table::~Table()
{
	std::cout << "Usunieto stolik" << std::endl;
	delete current_group_;
}

void Table::SetCurrentGroup(Client* client) 
{
	current_group_ = client;
}

Client* Table::GetCurrentGroup() const
{
	return current_group_;
}

int Table::GetNumberOfChairs()
{
	return number_of_chairs_;
}

bool Table::GetNowServiced()
{
	return  now_serviced_;
}

void Table::SetNowServiced(bool now_serviced)
{
	now_serviced_ = now_serviced;
}

void Table::SetTimeOfLastService(double time)
{
	time_of_last_service_ = time;
}

double Table::GetTimeOfLastService()
{
	return time_of_last_service_;
}


