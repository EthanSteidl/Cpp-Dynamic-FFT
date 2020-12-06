#include "Index_power.h"

Index_power::Index_power(int x, long double y)
{
	index = x;
	power = y;
}

ostream& operator<<(ostream& os, const Index_power& ip)
{
	
	os << left << setw(11) << setfill(' ') << ip.index;
	os << "(" << ip.value.real() << ", " << ip.value.imag() << ")";
	return os;
}