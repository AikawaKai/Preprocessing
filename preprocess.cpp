#include "type.h"
#include <iostream>
#include <vector>    
using namespace std;

bool update(vector<Variable*> *cond, int numvar, int *coeffEqu, int row, int pos){
	//int currcoff = coeffEqu[row*numvar+pos];
	int currcoeff = coeffEqu[row*numvar+pos];
	if(currcoeff==0)
	{
		return false;
	}
	float value = 1/(float)currcoeff;
	float product = coeffEqu[row*(numvar+1)+numvar];
	float first = 0;
	float second = 0;
	for(int j=0;j<numvar;j++)
	{
		if(j!=pos)
		{
			int other = coeffEqu[row*numvar+j];
			if(other>0)
			{
				first+= (-1) * other * (*cond)[j]->returnMin();
			}else
			{
				second+= (-1) * other * (*cond)[j]->returnMax();
			}
		}
	}
	product += (first + second);
	value = value * product;
	if(currcoeff>0)
	{
		if(value < (*cond)[pos]->returnMax() )
		{
			(*cond)[pos]->setMax(value);
		}
		else
		{
			return false;
		} 
	}
	else
	{
		if(value>(*cond)[pos]->returnMax())
		{
			(*cond)[pos]->setMin(value);
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
	/*
	while(updated)
	{
		for(int i=0; i< numrow; i++)
		{
			for(int j=0; j<numcol; j++)
			{
				cout<<coeffEqu[i*numcol+j];
				cout<<"\n";
			}
		}
		updated = false;
	}*/
	while(updated)
	{
		updated = false;
		for(int i=0; i<numrow; i++)
		{
			for(int j=0; j<numcol;j++)
			{
				//(*cond)[j]->showType();
				updated_t = update(cond, numcol, coeffEqu, i, j);
				if(updated_t)
				{
					updated = true;
				}
			}
		}
	}
	getchar();
}

