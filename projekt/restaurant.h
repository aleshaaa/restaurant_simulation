#pragma once
#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "buffet.h"
#include "cashier.h"
#include "manager.h"
#include "table.h"
#include "waiter.h"
#include <vector>
#include "event.h"
#include <fstream>

class Restaurant
{
public:
	Restaurant();
	~Restaurant();
	void AddDataToWaitingTimeForTables(double data);
	void AddDataToWaitingTimeForService(double data);
	void AddSampleToAverageQueueLengthToTable(int sample, double time);
	void AddSampleToAverageQueueLengthToCashier(int sample, double time);
	void AddClientsToQueueToTables(Client *client);
	void AddClientsToQueueToBuffet(Client *client);
	void AddClientsToQueueToCashier(Client *client);
	void AddClientToManager(Client* client, double time);
	void AddClientsToBuffet(Client *client, double time);
	void AddClientsToCashier(Client *client, double time);
	void DeleteClientsFromBuffet(Client* client);
	void NewEvent(Event* event);
	void GetData();
	int GetTimeToTable() const;
	int GetNumberOfGroups();
	void SetNumberOfGroups(int number);
	int GetEventListEmpty();
	std::vector<Event*>::iterator GetEventListBegin();
	std::vector<Event*>::iterator GetEventListEnd();

	bool FreeChairsInBuffet();
	bool QueueToTablesEmpty();
	bool QueueToBuffetEmpty();
	bool QueueToCashierEmpty();

	int GetSizeOfQueueToTables();
	int GetSizeOfQueueToCashier();
	void CheckClientExitInCashier(Client* client); //sprawdzenie czy grupa ktora zosta³a obsluzona przez kasjera byla dodana do wektora z klientami do wyjscia podczas alarmu
	bool CheckTimeOfLastService(double time);
	
	//funkcje uzywane do alarmu
	void AddClientsToExit(Client* client);
	void ClientsExit();
	int GetNumberOfClientExit();
	void CleanQueueOfEvents();
	void CleanQueueToTables();
	void CleanQueueToBuffet();
	void CleanQueueToCashier();
	void CleanManager();
	void CleanWaiters();
	void CleanCashiers();
	void CleanBuffet();
	Table* CleanTables();

	Event* GetEvent();
	Table* FindTable();
	Table* GetMatchTable(int chairs);
	Table* GetTableToService();
	Waiter* GetAvailableWaiter();
	Cashier* GetAvailableCashier();
	Client* GetCurrentGroupManager();
	void SetCurrentGroupManager(Client* client);
	Client* CheckCurrentGroupManager();
	Client* GetFirstClientFromQueueToTable(int number_of_clients);
	Client* GetFirstClientFromQueueToBuffet();
	Client* GetFirstClientFromQueueToCashier();

private:
	const int number_of_waiters_ = 11;	//liczba kelnerów
	const int number_of_cashiers_ = 5;	//liczba kasjerów
	const int number_of_tables2_ = 5;	//liczba stolików 2-os
	const int number_of_tables3_ = 12;	//liczba stolików 3-os
	const int number_of_tables4_ = 6;	//liczba stolików 4-os
	const int number_of_buffets_ = 18;	//liczba miejsc przy bufecie
	int number_of_groups_;				//liczba grup w systemie
	std::vector<Client*> vector_clients_exit_;			//wektor klientow ktorzy wyjda podczas alarmu
	std::vector<Waiter*> vector_waiter_;				//wektor kelnerów
	std::vector<Cashier*> vector_cashier_;				//wektor kasjerów
	std::vector<Table*> vector_table_;					//wektor stolików
	std::vector<Client*> queue_to_buffet_;				//kolejka do buffetu
	std::vector<Client*> queue_to_cashier_;				//kolejka do kajsera
	std::vector<Client*> queue_to_tables_;				//kolejka do stolików
	std::vector<Event*> event_list_;					//lista zdarzeñ
	Manager *manager_;							//wskaŸnik na kierownika
	Buffet *buffet_;							//wskaŸnik na bufet

	//STATYSTYKI
	std::ofstream data1_, data2_, data3_, data4_;		//zapis
	std::ofstream table_, cashier_;					//zapis
	double waiting_time_for_tables_ = 0;				//czas oczekiwania na stolik
	double waiting_time_for_service_ = 0;				//czas oczekiwania na obsluge przez kelnera

	double average_waiting_time_for_tables_ = 0;		//œredni czas oczekiwania na stolik
	double average_waiting_time_for_service_ = 0;		//œredni czas oczekiwania na obsluge przez kelnera
	double average_length_of_queue_to_tables_ = 0;		//œrednia d³ugoœæ kolejki do stolików
	double average_length_of_queue_to_cashiers_ = 0;	//œrednia d³ugoœæ kolejki do kasjerów
	double all_queues_to_tables_;						//ilosc kolejek do stolikow
	double all_queues_to_cashiers_;						//ilosc kolejek do kasjerow

	double all_groups_table_ = 0;						//iloœæ grup które wybra³y stoliki
	double all_groups_waiter_ = 0;						//iloœæ grup czekajacych na kelnera
	double time_of_last_change_in_queue_table_;			//czas kiedy nast¹pi³a zmiana w kolejce (dodano lub usuniêto grupê z kolejki)
	double sum_of_intervals_in_queue_table_;
	double time_of_last_change_in_queue_to_cashier_;	//czas kiedy nast¹pi³a zmiana w kolejce (dodano lub usuniêto grupê z kolejki)
	double sum_of_intervals_in_queue_to_cashier_;
};
#endif 
