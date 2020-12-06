#include "FFT.h"

FFT::FFT(char* filename)
{
	//reads file in
	vector<complex<double>> nums;
	ifstream fin;
	strcpy_s(file, filename);
	fin.open(filename);
	int i = 0;
	int inval;
	while (fin >> inval)
	{
		nums.push_back(complex<double>(inval,0));
		i++;
		
	}
	fin.close();
	coefficient_count = i;

	//solves for power of 2
	int max = 2;
	while (max < coefficient_count)
	{
		max = max + max;
	}

	//pads zeros
	while (coefficients.size()+nums.size() != max)
	{
		coefficients.push_back(complex<double>(0, 0));

	}
	coefficients.insert(coefficients.end(), nums.begin(), nums.end());

	coefficient_count = max;

}

/*
Solves for a solution
*/
void FFT::calculate()
{

	vector<complex<double>> retval;
	vector<complex<double>> first;
	vector<complex<double>> second;

	FFT_recursive_ref(coefficients);

	final_solution.clear();
	complex<double> extra;

	int final_size = coefficients.size();

	//When FFT is solving, the vector reverses inside when recuresing back out
	//The last step out does not reverse the vector. The vector returned from FFT
	//call looks like A B-D E F-Z
	//This reverses to look like A Z-F E D-B
	for (auto i = 0; i != final_size; i++)
	{
		if (i == 0)
		{
			final_solution.push_back(coefficients[i]);
		}
		else if (i == coefficient_count / 2)
		{
			
			extra = coefficients[i];
		}
		else 
		{
			if (i < coefficient_count / 2)
			{
				first.push_back(coefficients[i]);
			}
			else
			{
				second.push_back(coefficients[i]);
			}
		}
	}
	
	//combine lists
	final_solution.insert(final_solution.end(), second.rbegin(), second.rend());
	final_solution.push_back(extra);
	final_solution.insert(final_solution.end(), first.rbegin(), first.rend());

	

}

/*
Prints out the FFT coefficients in linear time
*/
void FFT::print()
{
	
	cout   << left << setfill('-') << setw(38)  << file  << endl;
	std::cout << std::fixed;
	std::cout << std::setprecision(2);

	//This block will find the 7 largest items and print them out in linear time not nlgn

	if (coefficient_count >= 9)
	{
		int c = 0;

		Index_power x1 = Index_power(0, -DBL_MAX);
		Index_power x2 = Index_power(0, -DBL_MAX);
		Index_power x3 = Index_power(0, -DBL_MAX);
		Index_power x4 = Index_power(0, -DBL_MAX);
		Index_power x5 = Index_power(0, -DBL_MAX);
		Index_power x6 = Index_power(0, -DBL_MAX);
		Index_power x7 = Index_power(0, -DBL_MAX);


		for (auto i = final_solution.begin(); i != final_solution.end(); i++)
		{

			long double spectral_power = (i->real() * i->real()) + (i->imag() * i->imag());

			if (x1.power < spectral_power)
			{
				x7 = x6;
				x6 = x5;
				x5 = x4;
				x4 = x3;
				x3 = x2;
				x2 = x1;
				x1.index = c;
				x1.power = spectral_power;
				x1.value = *i;

			}
			else if (x2.power < spectral_power)
			{
				x7 = x6;
				x6 = x5;
				x5 = x4;
				x4 = x3;
				x3 = x2;
				x2.index = c;
				x2.power = spectral_power;
				x2.value = *i;
			}
			else if (x3.power < spectral_power)
			{
				x7 = x6;
				x6 = x5;
				x5 = x4;
				x4 = x3;
				x3.index = c;
				x3.power = spectral_power;
				x3.value = *i;
			}
			else if (x4.power < spectral_power)
			{
				x7 = x6;
				x6 = x5;
				x5 = x4;
				x4.index = c;
				x4.power = spectral_power;
				x4.value = *i;
			}
			else if (x5.power < spectral_power)
			{
				x7 = x6;
				x6 = x5;
				x5.index = c;
				x5.power = spectral_power;
				x5.value = *i;
			}
			else if (x6.power < spectral_power)
			{
				x7 = x6;
				x6.index = c;
				x6.power = spectral_power;
				x6.value = *i;
			}
			else if (x7.power < spectral_power)
			{
				x7.index = c;
				x7.power = spectral_power;
				x7.value = *i;
			}

			c++;
		}

		cout << x1 << endl;
		cout << x2 << endl;
		cout << x3 << endl;
		cout << x4 << endl;
		cout << x5 << endl;
		cout << x6 << endl;
		cout << x7 << endl;


	}
	else
	{
		//standard print
		for (int i=0; i<final_solution.size(); i++)
		{
			cout << "(" << final_solution[i].real() << ", " << final_solution[i].imag() << ")" << endl;
		}
	}
	cout << "\n\n";
	
}


/*
converts a radian to complex number
*/
complex<double> FFT::radian_to_complex(double r)
{

	double x = cos(r);
	double y = sin(r);
	if (abs(x) < 0.001)
		x = 0.0;
	if (abs(y) < 0.001)
		y = 0.0;
	return complex<double> (x, y);

}

/*
calcualtes FFT recursivley based on pg 911 of the textbook
*/
void FFT::FFT_recursive_ref(vector<complex<double>>& a)
{
	//base case
	if (a.size() == 1)
	{
		return;
	}


	int amount = a.size();				//total size
	int half_amount = amount / 2;		//half the size
	vector<complex<double>> e;			//left side
	vector<complex<double>> d;			//even side

	vector<complex<double>> solution;	//2nd half solution
	double multiplier = 2 * PI / double(amount);	//multiplier for complex number calculation

	//split vector into left and right side alternating
	for (int i = 0; i < amount; i+=2)
	{
		d.push_back(a[i]);
		e.push_back(a[i + 1]);
	}

	//dive left, dive right
	FFT_recursive_ref(e);
	FFT_recursive_ref(d);
	

	//solve the correct real and imaginary values
	int j = amount / 2;
	for (int i = 0;  i < half_amount; i++,j++)
	{
		a[i] = (e[i] + (d[i] * radian_to_complex(i * multiplier)));
		a[j] = (e[i] + (d[i] * radian_to_complex(j * multiplier)));

	}
	
	
	return;
}

