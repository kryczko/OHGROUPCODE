/* This program will create an xyz file that follows the OH group for a visualzation in vmd */

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

int main()
{

string infile;

cout << "Please enter the input file name: ";
cin >> infile;

ifstream input;

input.open(infile.c_str());

int counter1 = 0, counter2 = 0, nooa, noha;
string get;

double xlattice, ylattice, zlattice;

double x, y, z;
vector <double> xc;
vector <double> yc;
vector <double> zc;



while (!input.eof())
{
	if (counter1 < 15)
	{
		input >> get;

		if (counter1 == 2)
		{
			xlattice = strtod(get.c_str(), NULL);
		}
		if (counter1 == 6)
		{
			ylattice = strtod(get.c_str(), NULL);
		}
		if (counter1 == 10)
		{
			zlattice = strtod(get.c_str(), NULL);
		}
		if (counter1 == 13)
		{
			nooa = strtod(get.c_str(), NULL);
		}
		if (counter1 == 14)
        	{
                	noha = strtod(get.c_str(), NULL);
        	}
	}
	else
	{
		input >> x >> y >> z;
		xc.push_back(x);
		yc.push_back(y);
		zc.push_back(z);
		counter2 ++;
	}
	counter1 ++;
}

int timestep = (counter2 - 1)/(nooa+noha);
cout << timestep << endl;

input.close();
return 0;
}
