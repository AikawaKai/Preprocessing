#include "type.h"
#include <iostream>
#include <vector>    
using namespace std;

bool update(vector<Variable*> *cond, int numvar, int *coeffEqu, int row, int pos){
	//int currcoff = coeffEqu[row*numvar+pos];
	int currcoeff = coeffEqu[row*numvar+pos];
	float value = 1/currcoeff;
	float product = coeffEqu[row*numvar+(numvar+1)];
	float first = 0;
	float second = 0;
	for(int j=0;j<numvar;j++)
	{
		if(j!=pos)
		{
			int other = coeffEqu[row*numvar+j];
			if(other>0)
			{
				first+= (-1) * other * (*cond)[j]->min;
				cout<<(*cond)[j]->name+": ";
				cout<<(*cond)[j]->min;
			}else
			{
				second+= (-1) * other * (*cond)[j]->max;
				cout<<(*cond)[j]->name+": ";
				cout<<(*cond)[j]->max;
			}
			cout<<" ";
		}
	}
	cout<<"\n";
	product += (first + second);
	value = value * product;
	cout<<value;
	cout<<" ";
	return true;
}

void boundsPreprocess(vector<Variable*> *cond, int numvar, int *coeffEqu, int numrow, int numcol) {
	bool updated = true;
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
	for(int i=0; i<numrow; i++)
	{
		for(int j=0; j<numcol;j++)
		{
			//(*cond)[j]->showType();
			updated = update(cond, numcol, coeffEqu, i, j);
			
		}
		
		//**cond[i]->showType();
	}
	getchar();
}

