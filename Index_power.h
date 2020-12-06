#pragma once
#include <complex>
#include <iostream>
#include <iomanip>

using namespace std;

class Index_power
{
public:

	int index;
	long double power;
	complex<long double> value;

	Index_power(int, long double);
	friend ostream& operator<<(ostream& os, const Index_power& ip);
};
