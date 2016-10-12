#include "type.h"
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

bool update(vector<Variable*> *cond, int numvar, float *coeffEqu, int row, int pos){
	float currcoeff = coeffEqu[row*(numvar+1)+pos];
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

void boundsPreprocess(vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol) {
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

void deleteConstraint(float *coeffEqu, int i, int numrow, int numcol)
{
	float newCoeffEqu[(numrow-1)*(numcol+1)];
	for(int k=0;k<numrow-1;k++)
	{
		for(int j=0; j<numcol+1;j++)
		{
			if(k<i)
			{
				newCoeffEqu[k*(numcol+1)+j]=coeffEqu[k*(numcol+1)+j];
			}
			else
			{
				newCoeffEqu[k*(numcol+1)+j]=coeffEqu[(k+1)*(numcol+1)+j];
			}
		}
	}
	numrow-=1;
	for(int k=0; k<numrow;k++)
	{
		for(int j=0; j<numcol+1;j++)
		{
			coeffEqu[k*(numcol+1)+j]=newCoeffEqu[k*(numcol+1)+j];
		}
	}
}

int constraintsPreprocess(std::vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol)
{
	float U;
	float L;
	float currcoeff;
	float bi;
	int toDelete;
	int newrow = numrow;
	for(int i=0; i<numrow;i++)
	{
		U = 0;
		L = 0;
		for(int j=0; j<numcol;j++)
		{
			currcoeff = coeffEqu[i*(numcol+1)+j];
			if(currcoeff>0)
			{
				U+=(currcoeff*(*cond)[j]->max);
				L+=(currcoeff*(*cond)[j]->min);
			}else if(currcoeff<0)
			{
				U+=(currcoeff*(*cond)[j]->min);
				L+=(currcoeff*(*cond)[j]->max);
			}
		}
		bi = coeffEqu[i*(numcol+1)+numcol];
		if(L>bi)
		{
			cout<<"Constraint "<<i<<" is infeasable";
			break;
		}else if(bi>=U)
		{
			cout<<"Constraint "<<i<<" is redundant";
			deleteConstraint(coeffEqu, i, newrow, numcol);
			newrow-=1;
		}else
		{
			
		}
	}
	return newrow;
}

