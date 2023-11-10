#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#include <random>

enum State { kUnhandled = 0, kDrink, kServiced };

class Client
{
public:
	
	Client();
	~Client();
	int GetNumberOfClients() const;
	int GetChoice() const;
	int GetId() const;
	static int GetIdOfLastClient();
	static void ClearIdClients();
	void CheckService();
	void SetState(State state);
	State GetState() const;

	int GetProbabilityExit();
	bool GetClientExit();
	void SetClientExit(bool exit);
	double GetNewGroupTime();
	double GetTimeBuffet();
	double GetTimeDrink();
	double GetTimeFood();
	double GetTimeEat();
	double GetTimeCashier();
	double GetTimeStart();
	void SetTimeStart(double time);
	double GetTimeTable();
	void SetTimeTable(double time);

private:
	int id_group_ = 0;				//id grupy klientów
	static int id_counter_;
	int number_of_clients_ = 0;		//liczebnoœæ grupy klientów
	int choice_;				//wybor miedzy stolikami a buffetem
	State state_;
	int probability_exit_;	//prawdopodobienstwo ze klient wyjdzie podzcas alarmu
	bool exit_;				//klient wyjdzie podczas alarmu
	double time_table_;
	double time_start_;
	double new_group_time_;
	double time_buffet_;
	double time_drink_;
	double time_food_;
	double time_eat_;
	double time_cashier_;

	//GENERATORY
	std::default_random_engine generator_ = std::default_random_engine(5000000);
	std::normal_distribution<double> normal_dist_new_clients_group_ = std::normal_distribution <double>(300.0, 50.0);
	std::normal_distribution<double> normal_dist_buffet_ = std::normal_distribution <double>(3700.0, 90.0);	/////nie zmieniac
	std::exponential_distribution<double> exponential_dist_drinks_ = std::exponential_distribution<double>(1 / 2000.0);
	std::exponential_distribution<double> exponential_dist_meals_ = std::exponential_distribution<double>(1 / 3200.0);
	std::exponential_distribution<double> exponential_dist_consumption_ = std::exponential_distribution<double>(1 / 2400.0); /////nie zmieniac
	std::exponential_distribution<double> exponential_dist_cashier_ = std::exponential_distribution<double>(1 / 9000.0);

};
#endif
