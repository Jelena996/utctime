#ifndef __TIMESTAMP__H__
#define __TIMESTAMP__H__

#include "interval.h"

class Timestamp {

	int year, month, day, hours, minutes;
    Interval* zoneOffSet;
	bool condition(int yy, int mm, int dd);
	bool leap(int yy);
	int conversion();
	Timestamp add1(Interval& interval);
	Timestamp subract1(Interval& interval);
   	Interval conversionToInterval();
public:
	Timestamp(int year, int month, int dayInMonth, int hours, int minutes, Interval* zoneOffSet);
	Timestamp(int yy, int mm, int dd, Interval* zoneOffSet);
	Timestamp(const Timestamp& original);

	Timestamp add(Interval& interval);
	Timestamp subtract(Interval& interval);
	Interval subtract(Timestamp& right);
	bool equals(Timestamp& time);
	bool lessThan(Timestamp& time);
	bool greaterThan(Timestamp& time);
	friend void print(Timestamp& time);
	friend void test();
	~Timestamp();
};

#endif