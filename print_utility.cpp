#include "type.h"
#include <iostream>
#include <vector>
using namespace std;

bool checkRow(vector<Variable*> *cond, float *coeffEqu, int i, int numcol)
{
	bool check = false;
	for(int j=0; j<numcol;j++)
	{
		if(!(*cond)[j]->fixed && coeffEqu[i*(numcol+1)+j]!=0)
		{
			return true;
		}
	}
	return check;
}

void printConstraints(vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol)
{
	float coeff;
	float to_sum;
	cout<<"\nConstraints:\n";
	for(int i=0;i<numrow;i++)
	{
		to_sum = 0;
		if(checkRow(cond, coeffEqu, i, numcol))
		{
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
