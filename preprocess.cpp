#include "type.h"
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

bool update(vector<Variable*> *cond, int numvar, int *coeffEqu, int row, int pos){
	float currcoeff = coeffEqu[row*(numvar+1)+pos];
	float tmp_val;
	float b;
	bool check;
	if(currcoeff==0)
	{
		return false;
	}
	float value = 1/currcoeff;
	float product = coeffEqu[row*(numvar+1)+numvar];
	float tosum = 0;
	for(int j=0;j<numvar;j++)
	{
		if(j!=pos)
		{
			int other = coeffEqu[row*(numvar+1)+j];
			if(other>0)
			{
				tosum+= (-1) * other * (*cond)[j]->returnMin();
			}else
			{
				tosum+= (-1) * other * (*cond)[j]->returnMax();
			}
		}
	}
	product += tosum;
	value = value * product;
	if(currcoeff>0)
	{
		if(value < (*cond)[pos]->returnMax() )
		{
			check = (*cond)[pos]->setMax(value);
		}
		else
		{
			return false;
		} 
	}
	else
	{
		if(value>(*cond)[pos]->returnMin())
		{
			check = (*cond)[pos]->setMin(value);
		}
		else
		{
			return false;
		} 
	}
	return true;
}

void boundsPreprocess(vector<Variable*> *cond, int numvar, int *coeffEqu, int numrow, int numcol) {
	bool updated = true;
	bool updated_t;
	while(updated)
	{
		updated = false;
		for(int i=0; i<numrow; i++)
		{
			for(int j=0; j<numcol;j++)
			{
				updated_t = update(cond, numcol, coeffEqu, i, j);
				if(updated_t)
				{
					updated = true;
				}
			}
		}
	}
}

