#include "type.h"
#include <iostream>
#include <vector>
using namespace std;

void printConstraints(std::vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol)
{
	float coeff;
	float to_sum;
	cout<<"\nConstraints:\n";
	for(int i=0;i<numrow;i++)
	{
		to_sum = 0;
		for(int j=0;j<numcol;j++)
		{
			coeff = coeffEqu[i*(numcol+1)+j];
			if(coeff<0)
			{
				if(!(*cond)[j]->fixed)
				{
					cout<<coeff<<"(";
					(*cond)[j]->showName();
					cout<<")";
				}else
				{
					to_sum+=(*cond)[j]->value*coeff;
				}
				
			}else if(coeff>0)
			{
				if(!(*cond)[j]->fixed)
				{
					cout<<"+"<<coeff<<"(";
					(*cond)[j]->showName();
					cout<<")";
				}else
				{
					to_sum+=(*cond)[j]->value*coeff;
				}
			}
		}
		cout<<"<="<<coeffEqu[i*(numcol+1)+numcol]-to_sum<<"\n";
	}
	cout<<"\n";
	cout<<"Variables:\n";
	for(int j=0;j<numcol;j++)
	{
		cout<<(*cond)[j]->min<<"<=(";
		(*cond)[j]->showName();
		cout<<")<="<<(*cond)[j]->max<<" ";
		(*cond)[j]->showType();
		if((*cond)[j]->fixed)
		{
			cout<<" fixed:"<<(*cond)[j]->value;
		}
		cout<<"\n";
	}
}
