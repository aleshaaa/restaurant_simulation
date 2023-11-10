#include "pch.h"
#include "client.h"
#include <cstdlib>
#include <iostream>

int Client::id_counter_ = 0;

Client::Client(): state_(kUnhandled)
{
	const auto probability = rand() % 100 + 1; //ustawienie prawdopodobienstwa dla liczby klientów

	if (probability >= 1 && probability < 11) number_of_clients_ = 1;
	else if (probability >= 11 && probability < 44) number_of_clients_ = 2;
	else if (probability >= 44 && probability < 77) number_of_clients_ = 3;
	else if (probability >= 77 && probability <= 100) number_of_clients_ = 4;

	//ALARM
	const auto probability2 = rand() % 100 + 1; //ustawienie prawdopodobieñstwa, ¿e dana grupa nie opuœci restauracji podczas alarmu
	probability_exit_ = probability2;
	if (probability_exit_ <= 30) exit_ = true; 
	else exit_ = false;

	id_group_ = id_counter_++;
	choice_ = rand() % 2;

	new_group_time_ = normal_dist_new_clients_group_(generator_); //okresla czas pojawienia sie nowego klienta
	time_buffet_ = normal_dist_buffet_(generator_);
	time_drink_ = abs(exponential_dist_drinks_(generator_));
	time_food_ = abs(exponential_dist_meals_(generator_));
	time_eat_ = abs(exponential_dist_consumption_(generator_));
	time_cashier_ = abs(exponential_dist_cashier_(generator_));

	std::cout << "Grupa " << number_of_clients_ << " klientow o ID: " << id_group_ << " utworzona." << std::endl;
}


Client::~Client()
{
	std::cout << "Grupa " << number_of_clients_ << " klientow o ID: " << id_group_ << " usunieta." << std::endl;
}

int Client::GetNumberOfClients() const
{
	return number_of_clients_;
}

int Client::GetChoice() const
{
	return choice_;
}

int Client::GetId() const
{
	return id_group_;
}

int Client::GetIdOfLastClient()
{
	return id_counter_;
}

void Client::ClearIdClients()
{
	id_counter_ = 0;
}

void Client::CheckService()
{
	state_ = State(int(state_) + 1);
}

void Client::SetState(State state)
{
	state_ = state;
}

State Client::GetState() const
{
	return state_;
}

int Client::GetProbabilityExit()
{
	return probability_exit_;
}

bool Client::GetClientExit()
{
	return  exit_;
}

void Client::SetClientExit(bool exit)
{
	exit_ = exit;
}

double Client::GetNewGroupTime()
{
	return new_group_time_;
}

double Client::GetTimeBuffet()
{
	return time_buffet_;
}

double Client::GetTimeDrink()
{
	return time_drink_;
}

double Client::GetTimeFood()
{
	return time_food_;
}

double Client::GetTimeEat()
{
	return time_eat_;
}

double Client::GetTimeCashier()
{
	return time_cashier_;
}

double Client::GetTimeStart()
{
	return time_start_;
}

void Client::SetTimeStart(double time)
{
	time_start_ = time;
}

double Client::GetTimeTable()
{
	return time_table_;
}

void Client::SetTimeTable(double time)
{
	time_table_ = time;
}
