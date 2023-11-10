#pragma once
#ifndef BUFFET_H
#define BUFFET_H
#include "client.h"
#include <vector>

class Buffet
{
public:
	explicit Buffet(int chairs);
	~Buffet();
	void AddCurrentGroupToBuffet(Client *client);
	void DeleteCurrentGroupToBuffet(Client *client);
	bool BuffetBusy(int number_of_clients);
	int GetNumberOfBuffetBusy();
	void SetNumberOfBuffetBusy(int number);
	std::vector<Client*> vector_of_clients_;	//wektor z grupami klientów

private:
	const int number_of_buffets_;				//liczba miejsc przy buffecie
	int number_of_buffets_busy_ = 0;			//ilosc zajetych miejsc przy buffecie
};
#endif 
