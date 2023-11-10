#pragma once
#ifndef WAITER_H
#define WAITER_H
#include "table.h"

class Waiter
{
public:
	Waiter();
	~Waiter();
	void SetCurrentGroup(Client *client);
	Client* GetCurrentGroup();

private:
	Client* current_group_;		//wskaünik na aktualnie ob≥ugiwana grupe
};
#endif
