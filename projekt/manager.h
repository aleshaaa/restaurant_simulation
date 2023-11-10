#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include "client.h"

class Manager
{
public:
	Manager();
	~Manager();
	Client* GetCurrentGroup() const;
	void SetCurrentGroup(Client* client);
	int GetTimeToTable();

private:
	const int time_to_table_ = 30;		//czas prowadzenia do stolika
	Client* current_group_;				//aktualnie obs³ugiwana grupa klientów
};
#endif //MANAGER_H
