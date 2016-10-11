#include "type.h"
#include <iostream>
#include <vector>
using namespace std;

void print_constraints(std::vector<Variable*> *cond, int *coeffEqu, int numrow, int numcol)
{
	int coeff;
	for(int i=0;i<numrow;i++)
	{
		for(int j=0;j<numcol;j++)
		{
			coeff = coeffEqu[i*(numcol+1)+j];
			if(coeff<0)
			{
				cout<<coeff;
				cout<<"(";
				(*cond)[j]->showName();
				cout<<")";
			}else if(coeff>0)
			{
				cout<<"+";
				cout<<coeff;
				cout<<"(";
				(*cond)[j]->showName();
				cout<<")";
			}
		}
		cout<<"<=";
		cout<<coeffEqu[i*(numcol+1)+numcol];
		cout<<"\n";
	}
}
