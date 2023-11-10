#pragma once
#ifndef CASHIER_H
#define CASHIER_H
#include "client.h"

class Cashier
{
public:
	Cashier();
	~Cashier();
	void SetCurrentGroup(Client *client);
	Client* GetCurrentGroup();
	void DeleteCurrentGroup();

private:
	Client* current_group_;
};
#endif 
