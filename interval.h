#ifndef __INTERVAL__H__
#define __INTERVAL__H__

class Interval {
    int days, hours, minutes;
	bool sign; 
	Interval add1(Interval& other);
	Interval subtract1(Interval& other);
public:
	static Interval* ZERO;
	Interval(int dd, int hh = 0, int mm = 0, bool sign1 = true);  		
	Interval add(Interval& other);
	Interval subtract(Interval& other); 
	bool equals(Interval& other);
	bool lessThan(Interval& other);	
	bool greaterThan(Interval &other);
	friend void print( Interval& interval);
	friend class Timestamp;
	friend void test();

};

#endif