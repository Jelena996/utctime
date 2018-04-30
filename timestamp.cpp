#include "timestamp.h"
#include "interval.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
void errorDetected(const string& msg);

Timestamp Timestamp::add1(Interval& interval) {
	int y = year, mo = month, d = day + interval.days;
	int m = interval.minutes + minutes; int h = interval.hours + hours;
	if (m > 59) { m -= 60; h += 1; }
	if (h > 23) { h -= 24; d += 1; }

	while (!(condition(y, mo, d))) {

		if (((mo == 1) || (mo == 3) || (mo == 5) || (mo == 7) || (mo == 8) || (mo == 10)) && (d>31))
		{
			d -= 31; mo += 1; continue;
		}
		if (((mo == 4) || (mo == 6) || (mo == 9) || (mo == 11)) && (d>30))
		{
			d -= 30; mo += 1; continue;
		}
		if (mo == 2)
		{
			if (leap(y)) { if (d > 29) { d -= 29; mo += 1; continue; } }
			else if (d > 28) { d -= 28; mo += 1; continue; }
		}
		if (mo == 12) { d -= 31; mo = 1; y += 1; continue; }
	}
	Timestamp u(y, mo, d, h, m, zoneOffSet);
	return u;
}

Timestamp Timestamp::subract1(Interval& interval) {
	int y = year, mo = month, d = day - interval.days;
	int m, h = hours;
	if (minutes < interval.minutes)
	{
		m = minutes + 60 - interval.minutes; h -= 1;
	}
	else m = minutes - interval.minutes;
	if (h < interval.hours)
	{
		h += 24 - interval.hours; d -= 1;
	}
	else h -= interval.hours;
	while (!(condition(y, mo, d)))
	{
		if ((mo == 2) || (mo == 4) || (m == 6) || (mo == 8) || (mo == 9) || (mo == 11)) {
			d += 31; mo -= 1; continue;
		}
		if ((mo == 5) || (mo == 7) || (mo == 10) || (mo == 12)) {
			d += 30; mo -= 1; continue;
		}
		if (mo == 3) {
			if (leap(y)) {
				d += 29; mo -= 1; continue;
			}
			else { d += 28; mo -= 1; continue; }
		}


		if (mo == 1) {
			d += 31; mo = 12; y -= 1; continue;
		}
	}

	Timestamp u(y, mo, d, h, m, zoneOffSet);
	return u;
}

bool Timestamp::condition(int yy, int mm, int dd) {
	switch (mm) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		if (dd > 31 || dd < 1)
			return false;
		break;

	case 4: case 6: case 9: case 11:
		if (dd > 30 || dd < 1)
			return false;
		break;

	case 2:
		if (dd > (28 + leap(yy)) || dd < 1) 
			return false;
		break;
	}
	return true;
}

bool Timestamp::leap(int yy) {
	return ((!(yy % 4) && (yy % 100)) || !(yy% 400));
}


Timestamp::Timestamp(int year, int month, int dayInMonth, int hours, int minutes, Interval* zoneOffSet) {
	if (condition(year, month, dayInMonth)) {
		
		if (hours < 0 || hours>23 || minutes < 0 || minutes > 60) 
			errorDetected("Navedeni parametri za datum nisu ispravni!");
		else {
			this->hours = hours;
			this->minutes = minutes;
		}

		if (zoneOffSet->days == 0 && zoneOffSet->hours >= 0 && zoneOffSet->hours <= 12)
			this->zoneOffSet = new Interval(0, zoneOffSet->hours, zoneOffSet->minutes, zoneOffSet->sign);
		else
			errorDetected("Navedeni podaci za interval vremenskog trenutka nisu ispravni!");

		this->year = year;
		this->month = month;
		day = dayInMonth;
	}
	else errorDetected("Navedeni datum nije ispravan!");
	
}

Timestamp::Timestamp(int yy, int mm, int dd, Interval* zoneOffSet) : 
	Timestamp(yy, mm, dd, 0, 0, zoneOffSet) {}

Timestamp::Timestamp(const Timestamp& original) {
	year = original.year;
	month = original.month;
	day = original.day;
	hours = original.hours;
	minutes = original.minutes;
	zoneOffSet = new Interval(*original.zoneOffSet);
}


Timestamp Timestamp::add(Interval& interval)
{
	if (interval.sign) return add1(interval);
	else return subract1(interval);
}

Timestamp Timestamp::subtract(Interval& interval)
{
	if (!interval.sign) return add1(interval);
	else return subract1(interval);
}

int Timestamp::conversion() {
	int d = day;
	d += ((year - 1) * 365 + (year - 1) / 4);
	switch (month) {           
	case 12: d += 30;
	case 11: d += 31;
	case 10: d += 30;
	case 9:  d += 31;
	case 8:  d += 31;
	case 7:  d += 30;
	case 6:  d += 31;
	case 5:  d += 30;
	case 4:  d += 31;
	case 3:  if (leap(year)) d += 29; else d += 28;
	case 2:  d += 31;
	}
	return d;

}

Interval Timestamp::conversionToInterval() {
	Interval i1(conversion(), hours, minutes);
	Interval i2(0, zoneOffSet->hours, zoneOffSet->minutes, !zoneOffSet->sign);
	return i1.add(i2);
	
}

Interval Timestamp::subtract(Timestamp& right) {
	Interval i1(conversionToInterval());
	Interval i2(right.conversionToInterval());
	return i1.subtract(i2);
}

bool Timestamp::equals(Timestamp& time) {
	Interval i11 = conversionToInterval();
	Interval i22 = time.conversionToInterval();
	return i11.equals(i22);
}

bool Timestamp::lessThan(Timestamp& time) {
	Interval i11 = conversionToInterval();
	Interval i22 = time.conversionToInterval();
	return i11.lessThan(i22);
}

bool Timestamp::greaterThan(Timestamp& time) {
	Interval i11 = conversionToInterval();
	Interval i22 = time.conversionToInterval();
	return  i11.greaterThan(i22);
}

void print(Timestamp& time) {
	cout << time.year << '-' << setw(2) << setfill('0') << time.month << '-' << setw(2) << setfill('0') << time.day << " " << setw(2) << setfill('0') << time.hours << ":" << setw(2) << setfill('0') << time.minutes << "  UTC ";
	print(*time.zoneOffSet);
}

Timestamp::~Timestamp() {
	delete zoneOffSet; zoneOffSet = nullptr;
}