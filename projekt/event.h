#pragma once

class Event
{
public:
	double time_ = 0;
	virtual ~Event() = default;
	virtual void execute() = 0;
	double GetTime();
	void SetTime(double time);
	bool GetExit();
	void SetExit(bool exit);

private:
	bool exit_ = false;
};

