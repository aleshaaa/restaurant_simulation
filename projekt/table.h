#pragma once

#include "client.h"
#ifndef TABLES_H
#define TABLES_H

class Table
{
public:
	explicit Table(int chairs);
	~Table();
	void SetCurrentGroup(Client* client);
	Client *GetCurrentGroup() const;
	int GetNumberOfChairs();
	bool GetNowServiced();
	void SetNowServiced(bool now_serviced);
	void SetTimeOfLastService(double time);
	double GetTimeOfLastService();

private:
	int number_of_chairs_;
	bool now_serviced_;
	double time_of_last_service_ = 0;
	Client* current_group_;
};
#endif

