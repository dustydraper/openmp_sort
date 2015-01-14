//============================================================================
// Name        : openmp_sort.cpp
// Author      : dusty
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <omp.h>
#include <math.h>
using namespace std;


int main() {
	int i,j,k,min,max,gmin,gmax;
	int A[3][100][100];
	for(i=0;i<3;i++)
	{
		for(j=0;j<100;j++)
		{
			for(k=0;k<100;k++)
			{
				A[i][j][k]=i+j+k;
			}
		}
	}
	min=A[2][2][2];
	max=A[2][2][2];
	gmin=A[2][2][2];
	gmax=A[2][2][2];

	cout << "min = " <<min<< endl<<"max = "<<max<<endl;
#pragma omp parallel default(shared) private(i,j,k) firstprivate(min,max)
	{
#pragma omp for
		for(i=0;i<3;i++)
			{
				for(j=0;j<100;j++)
				{
					for(k=0;k<100;k++)
					{
						if(A[i][j][k]<min) min= A[i][j][k];
						if(A[i][j][k]>max) max= A[i][j][k];
					}
				}
			}
#pragma omp critical
		{
			if(gmin>min) gmin = min;
			if(gmax<max) gmax = max;
		}
	}
	cout << "min = " <<gmin<< endl<<"max = "<<gmax<<endl;
	return 0;
}
