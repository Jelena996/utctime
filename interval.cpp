#include "interval.h"
#include <string>
#include <iostream>
#include <iomanip>		
using namespace std;

Interval* Interval::ZERO = new Interval(0,0,0,0);

void errorDetected(const string& msg) {
	cout << msg << endl;
	exit(true);
}

Interval Interval::add1(Interval& other) {

	int d = days + other.days; int h = hours + other.hours;
	int m = minutes + other.minutes;
	if (m > 59) { m -= 60; h += 1; }
	if (h > 23) { h -= 24; d += 1; }
	return Interval(d, h, m, sign);

}

Interval Interval::subtract1(Interval& other) {

	int m, h = hours, d = days;
	bool sign1;
	if (minutes < other.minutes) { m = minutes + 60 - other.minutes; h -= 1; }
	else m = minutes - other.minutes;
	if (h < other.hours) { h += 24 - other.hours; d -= 1; }
	else h -= other.hours;
	d -= other.days;
	if (d < 0) { sign1 = false; d = 0 - d; }
	else sign1 = true;
	return Interval(d, h, m, sign1);

}

Interval::Interval(int dd, int hh, int mm, bool sign1) { 
	if ((dd >= 0) && (hh<24  && hh>=0) && (mm<60 && mm>=0) ) {
		days = dd; hours = hh; minutes = mm; sign = sign1;
	}
		
	else errorDetected("Uneseni parametri nisu realni!");
}	

Interval Interval::add(Interval& other) {
	if (sign == other.sign) return add1(other);
	else return subtract1(other);
}

Interval Interval::subtract(Interval& other) {
	if (sign == other.sign) return subtract1(other);
	else return add1(other);
}

bool Interval::equals(Interval& other) {
	if (sign != other.sign) return false;
	else if (days != other.days) return false;
	else if (hours != other.hours) return false;
	else if (minutes != other.minutes) return false;
	else return true;
}

bool Interval::lessThan(Interval& other) {
	if (sign< other.sign) return true;
	else if (days < other.days)return true;
	else if (hours < other.hours)return true;
	else if (minutes < other.minutes)return true;
	else return false;
}

bool Interval::greaterThan(Interval& other) {

	if (!equals(other)) return other.lessThan(*this);
	else return false;
}

void print(Interval& interval) {
	if (!interval.sign) {
		if (interval.days != 0)
			cout << "- " << interval.days << "." << setw(2) << setfill('0') << interval.hours << ":" <<		
			setw(2) << setfill('0') << interval.minutes << endl;
		else
			cout << "- " << setw(2) << setfill('0') << interval.hours << ":" <<
			setw(2) << setfill('0') << interval.minutes << endl;		
	}
	else {
		if (interval.days != 0)
			cout << "+ " << interval.days << "." << setw(2) << setfill('0') << interval.hours << ":" <<
			setw(2) << setfill('0') << interval.minutes << endl;
		else
			cout << "+ " << setw(2) << setfill('0') << interval.hours << ":" <<
			setw(2) << setfill('0') << interval.minutes << endl;		
	}
}

