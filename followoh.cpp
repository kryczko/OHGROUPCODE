/* This program will create an xyz file that follows the OH group for a visualzation in vmd */

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

int pbc_round(double input)
{
	int i  = input;

	if (abs(input - i) >= 0.5)
	{
		if (input > 0) {i += 1;}
		if (input < 0) {i -= 1;}
	}
return i;
}

int main()
{

string infile;

cout << "Please enter the input file name: ";
cin >> infile;

ifstream input;
input.open(infile.c_str());

ofstream output;
output.open("ohgroup.xyz");

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
int noa = nooa + noha;

int timestep = (counter2 - 1)/(nooa+noha), ohindices[nooa][6];

for (int i = 0; i < nooa; i ++)
{
	for (int j = 0; j < 6; j ++)
	{
		ohindices[i][j] = -1;
	}
}

double oxyz[nooa][3], hxyz[noha][3], dx, dy, dz, ohdist;

for (int i = 0; i < timestep; i ++)
{
	for (int j = 0; j < nooa; j ++)
	{
		oxyz[j][0] = xlattice*xc[j + i*noa];
		oxyz[j][1] = ylattice*yc[j + i*noa];
		oxyz[j][2] = zlattice*zc[j + i*noa];
	}

	for (int j = 0; j < noha; j ++)
	{
		hxyz[j][0] = xlattice*xc[j + nooa + i*noa];
		hxyz[j][1] = ylattice*yc[j + nooa + i*noa];
		hxyz[j][2] = zlattice*zc[j + nooa + i*noa]; 
	}

	for (int j = 0; j < nooa; j ++)
	{
		int count = 0;
		for (int k = 0; k < noha; k ++)
		{
			dx = oxyz[j][0] - hxyz[k][0];
			dy = oxyz[j][1] - hxyz[k][1];
			dz = oxyz[j][2] - hxyz[k][2];

			dx -= xlattice*pbc_round(dx/xlattice);
			dy -= ylattice*pbc_round(dy/ylattice);
			dz -= zlattice*pbc_round(dz/zlattice);

			ohdist = sqrt ( dx*dx + dy*dy + dz*dz );
			if ( ohdist < 1.2 )
			{
				ohindices[j][count] = k;
				count ++;
			}
		}
	}

	output << 2 << "\n\n";

	for (int j = 0; j < nooa; j ++)
	{
		int hcount = 0;
		for (int k = 1; k < 6; k ++)
		{
			if (ohindices[j][0] != ohindices[j][k] && ohindices[j][k] != -1)
			{
				hcount ++;
			}
		}
		
		if (hcount != 1)
		{
			output << "O" << "\t" << oxyz[j][0] << "\t" << oxyz[j][1] << "\t" << oxyz[j][2] << endl;
			output << "H" << "\t" << hxyz[ohindices[j][0]][0] << "\t" << hxyz[ohindices[j][0]][1] << "\t" << hxyz[ohindices[j][0]][2] << endl;
		}
	}				
}



input.close();
output.close();
return 0;
}
