#pragma once
#include <vector>
#include <complex>
#include <fstream>
#include <complex>
#include <iostream>
#include <iomanip>
#include "Index_power.h"


#define PI 3.14159265358979323846

using namespace std;




class FFT
{




private:
	int coefficient_count;		//count of coefficients
	char file[20];				//input file

	vector<complex<double>> coefficients;	//coefficients read in
	vector<complex<double>> final_solution;	//final solution


public:
	FFT(char *filename);
	void calculate();
	void FFT_recursive_ref(vector<complex<double>>& a);
	complex<double> radian_to_complex(double r);
	void print();

};

