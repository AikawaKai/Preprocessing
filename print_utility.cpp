#include "type.h"
#include <iostream>
#include <vector>
using namespace std;

void print_constraints(std::vector<Variable*> *cond, int *coeffEqu, int numrow, int numcol)
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
					cout<<coeff;
					cout<<"(";
					(*cond)[j]->showName();
					cout<<")";
				}else
				{
					to_sum+=(*cond)[j]->value;
				}
				
			}else if(coeff>0)
			{
				if(!(*cond)[j]->fixed)
				{
					cout<<"+";
					cout<<coeff;
					cout<<"(";
					(*cond)[j]->showName();
					cout<<")";
				}else
				{
					to_sum+=(*cond)[j]->value;
				}
			}
		}
		cout<<"<=";
		cout<<coeffEqu[i*(numcol+1)+numcol]-to_sum;
		cout<<"\n";
	}
	cout<<"\n";
	cout<<"Variables:\n";
	for(int j=0;j<numcol;j++)
	{
		cout<<(*cond)[j]->min;
		cout<<"<=(";
		(*cond)[j]->showName();
		cout<<")<=";
		cout<<(*cond)[j]->max;
		cout<<"\n";
	}
}
