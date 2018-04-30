#include "interval.h"
#include "timestamp.h"
#include <iostream>
using namespace std;

#ifndef PROF_TEST

void test() {
	Interval i1(62, 0, 0, true);
	Interval i3(0, 1, 0, false);
	
	Timestamp t1(2016, 2, 28, 11, 30, &i3);
	Timestamp t2(2016, 2, 6, 11, 15, &i3);
	print(t1.subtract(t2));
	cout << endl;
	Timestamp t = t1.add(i1);
	print(t1);
	print(i1);
	print(t);
	print(i3.subtract(i1));
	if (i1.greaterThan(i3))
		cout << "Veci je." << endl;
	else if (i1.greaterThan(i3))
		cout << "Manji je." << endl;
	else
		cout << "Jednaki su." << endl;



}
#endif

