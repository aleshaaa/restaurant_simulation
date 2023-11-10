#include "pch.h"
#include "restaurant.h"
#include <iostream>
#include "endmanagerservice.h"
#include "endcashierservice.h"
#include "endbuffetservice.h"


Restaurant::Restaurant(): number_of_groups_(0), all_queues_to_tables_(0),
                          all_queues_to_cashiers_(0), time_of_last_change_in_queue_table_(0),
                          sum_of_intervals_in_queue_table_(0),
                          time_of_last_change_in_queue_to_cashier_(0),
                          sum_of_intervals_in_queue_to_cashier_(0)
{
	std::cout << "Utworzono restauracje!" << std::endl;
	manager_ = new Manager();
	buffet_ = new Buffet(number_of_buffets_);
	for (auto i = 0; i < number_of_waiters_; i++) vector_waiter_.push_back(new Waiter());
	for (auto i = 0; i < number_of_tables2_; i++) vector_table_.push_back(new Table(2));
	for (auto i = 0; i < number_of_tables3_; i++) vector_table_.push_back(new Table(3));
	for (auto i = 0; i < number_of_tables4_; i++) vector_table_.push_back(new Table(4));
	for (auto i = 0; i < number_of_cashiers_; i++) vector_cashier_.push_back(new Cashier());


	all_groups_table_ = 0;
	all_groups_waiter_ = 0;
	waiting_time_for_service_ = 0;
	waiting_time_for_tables_ = 0;
	average_length_of_queue_to_cashiers_ = 0;
	average_length_of_queue_to_tables_ = 0;
	average_waiting_time_for_service_ = 0;
	average_waiting_time_for_tables_ = 0;
}


Restaurant::~Restaurant()
{
	delete manager_;
	delete buffet_;

	for (auto i : vector_waiter_) delete i;
	for (auto i : vector_cashier_) delete i;
	for (auto i : vector_table_) delete i;
	for (auto i : queue_to_tables_) delete i;
	for (auto i : queue_to_buffet_) delete i;
	for (auto i : queue_to_cashier_) delete i;
	for (auto i : event_list_) delete i;

	std::cout << "Usunieto restauracje." << std::endl;
}

void Restaurant::AddClientsToQueueToTables(Client* client)
{
	queue_to_tables_.push_back(client);
	//length_of_queue_to_tables_ += queue_to_tables_.size();
	//all_queues_to_tables_++;
}

void Restaurant::AddClientsToQueueToBuffet(Client* client)
{
	queue_to_buffet_.push_back(client);
}

void Restaurant::AddClientsToQueueToCashier(Client* client)
{
	queue_to_cashier_.push_back(client);
	//length_of_queue_to_cashiers_ += queue_to_cashier_.size();
	//all_queues_to_cashiers_++;
}
void Restaurant::AddClientToManager(Client* client, double time)
{
	Table *table = nullptr;
	for (Table *x : vector_table_)
	{
		if (x->GetCurrentGroup() == nullptr && client->GetNumberOfClients() <= x->GetNumberOfChairs())
		{
			table = x;
			break;
		}
	}
	if (manager_->GetCurrentGroup() == nullptr && table != nullptr)
	{
		SetCurrentGroupManager(client);
		NewEvent(new EndManagerService(this, client, table, time));
		std::cout << "Grupa klientow o ID: " << client->GetId() << " jest prowadzona przez kierownika sali do stolika "
			<< table->GetNumberOfChairs() << "-sobowego." << std::endl;
	}
	else
	{
		AddClientsToQueueToTables(client);
		std::cout << "Grupa klientow o ID: " << client->GetId() << " dodana do kolejki do stolikow." << std::endl;
	}
}
void Restaurant::AddClientsToBuffet(Client* client, double time)
{
	if(buffet_->BuffetBusy(client->GetNumberOfClients()))
	{
		buffet_->AddCurrentGroupToBuffet(client);
		//buffet_->number_of_buffets_busy_ += client->GetNumberOfClients();
		NewEvent(new EndBuffetService(this, client, time));
		std::cout << "Grupa klientow o ID: " << client->GetId() << " idzie do buffetu." << std::endl;
	}
	else
	{
		AddClientsToQueueToBuffet(client);
		std::cout << "Grupa klientow o ID: " << client->GetId() << " zostala dodana do kolejki do buffetu." << std::endl;
	}
}

void Restaurant::AddClientsToCashier(Client* client, double time)
{
	Cashier* cashier = GetAvailableCashier();
	if(cashier != nullptr)
	{
		cashier->SetCurrentGroup(client);
		NewEvent(new EndCashierService(this, client, cashier, time));
		std::cout << "Grupa klientow o ID: " << client->GetId() << " idzie do kasjera." << std::endl;
	}

	else
	{
		AddClientsToQueueToCashier(client);
		std::cout << "Grupa klientow o ID: " << client->GetId() << " zostala dodana do kolejki do kasjerow." << std::endl;
	}
}

void Restaurant::DeleteClientsFromBuffet(Client* client)
{
	buffet_->DeleteCurrentGroupToBuffet(client);
}

void Restaurant::NewEvent(Event* event)
{
	event_list_.push_back(event);
}

void Restaurant::GetData()
{
	int i = 0;
	std::cout << "Zdarzenia w kolejce: " << event_list_.size() << std::endl;
	for (Waiter* x : vector_waiter_) if (x->GetCurrentGroup() == nullptr) i++;
	std::cout << "Wolni kelnerzy:  " << i << std::endl;
	std::cout << "Dlugosc kolejki do stolikow:  " << queue_to_tables_.size() << std::endl;
	for (Client* x : queue_to_tables_)std::cout << "ID klientow czekajacych w kolejce do stolikow: " << x->GetId() << std::endl << "Liczba klientów: " 
		<< x->GetNumberOfClients() << std::endl;
	std::cout << "Stoliki:" << std::endl;
	for (i = 0; i < static_cast<int>(vector_table_.size()); i++)
	{
		std::cout << i << " stolik " << vector_table_[i]->GetNumberOfChairs() <<" -osobowy ";
		if (vector_table_[i]->GetCurrentGroup() != nullptr) std::cout << "zajety przez grupe o ID: " << vector_table_[i]->GetCurrentGroup()->GetId() <<
			" ilosc klientow przy stoliku: " << vector_table_[i]->GetCurrentGroup()->GetNumberOfClients() << std::endl;
		else std::cout << " jest pusty." << std::endl;
	}
	std::cout << "Dlugosc kolejki do buffetu: " << queue_to_buffet_.size() << std::endl;
	std::cout << "Zajete miejsca przy buffecie: " << buffet_->GetNumberOfBuffetBusy() << std::endl;
	std::cout << "Dlugosc kolejki do kasy: " << queue_to_cashier_.size() << std::endl;
}

int Restaurant::GetTimeToTable() const
{
	return manager_->GetTimeToTable();
}

int Restaurant::GetNumberOfGroups()
{
	return number_of_groups_;
}

void Restaurant::SetNumberOfGroups(int number)
{
	number_of_groups_ = number;
}

int Restaurant::GetEventListEmpty()
{
	return event_list_.empty();
}

std::vector<Event*>::iterator Restaurant::GetEventListBegin()
{
	return event_list_.begin();
}

std::vector<Event*>::iterator Restaurant::GetEventListEnd()
{
	return event_list_.end();
}

bool Restaurant::FreeChairsInBuffet()
{
	return buffet_->BuffetBusy(queue_to_buffet_.front()->GetNumberOfClients());
}

bool Restaurant::QueueToTablesEmpty()
{
	return queue_to_tables_.empty();
}

bool Restaurant::QueueToBuffetEmpty()
{
	return queue_to_buffet_.empty();
}

bool Restaurant::QueueToCashierEmpty()
{
	return queue_to_cashier_.empty();
}

int Restaurant::GetSizeOfQueueToTables()
{
	return static_cast<int>(queue_to_tables_.size());
}

int Restaurant::GetSizeOfQueueToCashier()
{
	return static_cast<int>(queue_to_cashier_.size());
}

void Restaurant::CheckClientExitInCashier(Client* client)
{
	for(int i =0; i<GetNumberOfClientExit(); i++)
	{
		if(vector_clients_exit_[i] == client)
		{
			vector_clients_exit_.erase(vector_clients_exit_.begin() + i);
			i--;
		}
	}
}

bool Restaurant::CheckTimeOfLastService(double time)
{
	for(auto i =0; vector_table_.size()<i; i++)
	{
		if (time > vector_table_[i]->GetTimeOfLastService()) return true;
	}
	return false;
}

void Restaurant::AddClientsToExit(Client* client)
{
	vector_clients_exit_.push_back(client);
}

void Restaurant::ClientsExit()
{
	for(int i=0; i<GetNumberOfClientExit(); i++)
	{
		number_of_groups_--;
		delete vector_clients_exit_[i];
	}
	vector_clients_exit_.clear();
}

int Restaurant::GetNumberOfClientExit()
{
	return static_cast<int>(vector_clients_exit_.size());
}

void Restaurant::CleanQueueOfEvents() //usuwanie eventow dla klientow, ktorzy opuscili restauracje podczas alarmu
{
	for(int i = 0; i<event_list_.size(); i++)
	{
		if(event_list_[i]->GetExit())
		{
			event_list_.erase(event_list_.begin() + i);
			i--;
		}
	}
}

void Restaurant::CleanQueueToTables() //usuniecie z kolejki grup ktore wyszly z restauracji podczas alarmu
{
	for (int i = 0; i < GetSizeOfQueueToTables(); i++)
	{
		if (queue_to_tables_[i]->GetClientExit())
		{
			queue_to_tables_.erase(queue_to_tables_.begin() + i);
			i--;
		}
	}
}

void Restaurant::CleanQueueToBuffet() 
{
	for (int i = 0; i < queue_to_buffet_.size(); i++)
	{
		if (queue_to_buffet_[i]->GetClientExit())
		{
			queue_to_buffet_.erase(queue_to_buffet_.begin() + i);
			i--;
		}
	}
}

void Restaurant::CleanQueueToCashier() 
{
	for (int i = 0; i < GetSizeOfQueueToCashier(); i++)
	{
		if (queue_to_cashier_[i]->GetClientExit())
		{
			queue_to_cashier_.erase(queue_to_cashier_.begin() + i);
			i--;
		}
	}
}

void Restaurant::CleanManager()
{
	if (manager_->GetCurrentGroup())
	{
		if(manager_->GetCurrentGroup()->GetClientExit())
		{
			manager_->SetCurrentGroup(nullptr);
		}
	}

}

void Restaurant::CleanWaiters()
{
	for(int i =0; i<vector_waiter_.size(); i++)
	{
		if (vector_waiter_[i]->GetCurrentGroup())
		{
			if(vector_waiter_[i]->GetCurrentGroup()->GetClientExit())
			{
				vector_waiter_[i]->SetCurrentGroup(nullptr);
			}	
		}
	}
}

void Restaurant::CleanCashiers()
{
	for (int i = 0; i < vector_cashier_.size(); i++)
	{
		if (vector_cashier_[i]->GetCurrentGroup())
		{
			if(vector_cashier_[i]->GetCurrentGroup()->GetClientExit())
			{
				vector_cashier_[i]->SetCurrentGroup(nullptr);
			}
		}
	}
}

void Restaurant::CleanBuffet()
{
	for(int i =0; i < buffet_->vector_of_clients_.size(); i++)
	{
		if (buffet_->vector_of_clients_[i]->GetClientExit())
		{
			buffet_->SetNumberOfBuffetBusy(buffet_->vector_of_clients_[i]->GetNumberOfClients());
			buffet_->vector_of_clients_.erase(buffet_->vector_of_clients_.begin() + i);
			i--;
		}
	}
}

Table* Restaurant::CleanTables()
{
	for (int i = 0; i < vector_table_.size(); i++)
	{
		if (vector_table_[i]->GetCurrentGroup())
		{
			if (vector_table_[i]->GetCurrentGroup()->GetClientExit())
			{
				vector_table_[i]->SetCurrentGroup(nullptr);
			}
		}	
	}
	return nullptr;
}

Event* Restaurant::GetEvent()
{
	Event* event = event_list_.front();
	event_list_.erase(event_list_.begin());
	return event;
}

Table* Restaurant::FindTable()
{
	for(Table *table: vector_table_)
	{
		if (table->GetCurrentGroup() == nullptr) return table;
	}
	return nullptr;
}

Table* Restaurant::GetMatchTable(int chairs)
{
	for (Table *table: vector_table_)
	{
		if (table->GetNumberOfChairs() >= chairs && table->GetCurrentGroup()==nullptr) return table;
	}
	return nullptr;
}


Table* Restaurant::GetTableToService()
{
	Table *table = nullptr;
	for(Table *i: vector_table_)
	{
		if (table == nullptr && i->GetCurrentGroup() != nullptr && !i->GetNowServiced())
		{
			table = i;
		}
		else if (table !=nullptr && i->GetCurrentGroup() != nullptr && !i->GetNowServiced())
		{
			if (i->GetTimeOfLastService() < table->GetTimeOfLastService()) table = i;
		}
	}
	return table;
}

Waiter* Restaurant::GetAvailableWaiter()
{
	for(Waiter *waiter : vector_waiter_)
	{
		if (waiter->GetCurrentGroup() == nullptr) return waiter;
	}
	return nullptr;
}

Cashier* Restaurant::GetAvailableCashier()
{
	for(Cashier* cashier : vector_cashier_)
	{
		if (cashier->GetCurrentGroup() == nullptr) return cashier;
	}
	return nullptr;
}

Client* Restaurant::GetCurrentGroupManager()
{
	return manager_->GetCurrentGroup();
}

void Restaurant::SetCurrentGroupManager(Client* client)
{
	manager_->SetCurrentGroup(client);
	if(client!=nullptr)
	{
		for(int i = 0; i<queue_to_tables_.size(); i++)
		{
			if(queue_to_tables_[i] == client)
			{
				queue_to_tables_.erase(queue_to_tables_.begin() + i);
				break;
			}
		}
	}
}

Client* Restaurant::CheckCurrentGroupManager()
{
	return manager_->GetCurrentGroup();
}

Client* Restaurant::GetFirstClientFromQueueToTable(int number_of_clients)
{
	for(Client *client : queue_to_tables_)
	{
		if (client->GetNumberOfClients() <= number_of_clients) return client;
	}
	return nullptr;
}

Client* Restaurant::GetFirstClientFromQueueToBuffet()
{
	Client *client = queue_to_buffet_.front();
	queue_to_buffet_.erase(queue_to_buffet_.begin());
	return client;
}

Client* Restaurant::GetFirstClientFromQueueToCashier()
{
	Client *client = queue_to_cashier_.front();
	queue_to_cashier_.erase(queue_to_cashier_.begin());
	return client;
}


void Restaurant::AddDataToWaitingTimeForTables(double data)
{
	if (Client::GetIdOfLastClient() > 32) //faza poczatkowa
	{
		data1_.open("time_table.txt");
		waiting_time_for_tables_ += data;
		all_groups_table_++;
		if (all_groups_table_)
		{
			average_waiting_time_for_tables_ = waiting_time_for_tables_ / all_groups_table_;
			data1_ << average_waiting_time_for_tables_ << std::endl;
		}
		data1_.close();
	}
}

void Restaurant::AddDataToWaitingTimeForService(double data)
{
	if(Client::GetIdOfLastClient() > 32) //faza poczatkowa
	{
		data2_.open("time_waiter.txt");
		waiting_time_for_service_ += data;
		all_groups_waiter_++;
		if(all_groups_waiter_)
		{
			average_waiting_time_for_service_ = waiting_time_for_service_ / all_groups_waiter_;
			data2_ << average_waiting_time_for_service_ << std::endl;
		}
		data2_.close();
	}
}

void Restaurant::AddSampleToAverageQueueLengthToTable(int sample, double time)
{
	if (Client::GetIdOfLastClient() > 32) //faza poczatkowa
	{
		table_.open("table.txt");
		if (time_of_last_change_in_queue_table_ != 0)
		{
			const double interval = time - time_of_last_change_in_queue_table_;
			sum_of_intervals_in_queue_table_ += interval;
			all_queues_to_tables_ += sample * interval;
			average_length_of_queue_to_tables_ = double(all_queues_to_tables_ ) / double(sum_of_intervals_in_queue_table_);
			table_ << average_length_of_queue_to_tables_ << std::endl;
		}
		time_of_last_change_in_queue_table_ = time;
		table_.close();
	}
}

void Restaurant::AddSampleToAverageQueueLengthToCashier(int sample, double time)
{
	if (Client::GetIdOfLastClient() > 32) //faza poczatkowa
	{
		cashier_.open("cashier.txt");
		if (time_of_last_change_in_queue_to_cashier_ != 0)
		{
			const double interval = time - time_of_last_change_in_queue_to_cashier_;
			all_queues_to_cashiers_ += sample * interval;
			sum_of_intervals_in_queue_to_cashier_ += interval;
			average_length_of_queue_to_cashiers_ = double(all_queues_to_cashiers_ ) / double(sum_of_intervals_in_queue_to_cashier_);
			cashier_ << average_length_of_queue_to_cashiers_ << std::endl;
		}
		time_of_last_change_in_queue_to_cashier_ = time;
		cashier_.close();
	}
}