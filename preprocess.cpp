#include "type.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>

bool update(std::vector<Variable*> *cond, int numvar, float *coeffEqu, int row, int pos){
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
		if(value < (*cond)[pos]->returnMax() && (*cond)[pos]->returnMax()!=(*cond)[pos]->returnMin())
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
		if(value>(*cond)[pos]->returnMin() && (*cond)[pos]->returnMax()!=(*cond)[pos]->returnMin())
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

int boundsPreprocess(std::vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol) {
	bool updated = true;
	bool updated_t;
	int bounds = 0;
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
					bounds += 1;
				}
			}
		}
	}
	return bounds;
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

void fixingVariables(std::vector<Variable*> *cond, float *coeffEqu, int numcol)
{
	for(int i=0;i<numcol;i++)
	{
		if(coeffEqu[i]>0)
		{
			(*cond)[i]->setValue((*cond)[i]->min);
		}else if(coeffEqu[i]<0)
		{
			(*cond)[i]->setValue((*cond)[i]->max);
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
			std::cout<<"Constraint "<<i<<" is infeasable"<<"\n";
			return numrow;
		}
		else if(bi>=U)
		{
			std::cout<<"Constraint "<<i<<" is redundant"<<std::endl;
			deleteConstraint(coeffEqu, i, newrow, numcol);
			newrow = constraintsPreprocess(cond, coeffEqu, newrow-1, numcol);
			return newrow;
		}
		else if(bi==L)
		{
			float coeffCurr[numcol];
			for(int k=0;k<numcol+1;k++)
			{
				coeffCurr[k]=coeffEqu[i*(numcol+1)+k];
			}
			fixingVariables(cond, coeffCurr, numcol);
		}
	}
	return newrow;
}

void coeffRed(float *coeffEqu, int i, int numcol, int &count)
{
	float M=0;
	float diff = 0;
	int index[numcol];
	for(int j=0;j<numcol;j++)
	{
		index[j]=0;
	}
	for(int j=0;j<numcol;j++)
	{
		float currCoeff = coeffEqu[i*(numcol+1)+j];
		if(currCoeff>0)
		{
			M+=currCoeff;
		}
	}
	diff = M - coeffEqu[i*(numcol+1)+numcol];
	for(int j=0; j<numcol;j++)
	{
		if(abs(coeffEqu[i*(numcol+1)+j])>diff)
		{
			index[j]=1;
		}
	}
	int indexes = 0;
	for(int j=0;j<numcol;j++)
	{
		indexes+=index[j];
	}
	if(indexes>0)
	{
		for(int j=0;j<numcol;j++)
		{
			if(index[j]==1)
			{
				if(coeffEqu[i*(numcol+1)+j]>0)
				{
					float a_ = coeffEqu[i*(numcol+1)+j];
					coeffEqu[i*(numcol+1)+j] = diff;
					coeffEqu[i*(numcol+1)+numcol] = M - a_;
					count+=1;	
				}
				else
				{
					coeffEqu[i*(numcol+1)+j] = coeffEqu[i*(numcol+1)+numcol]-M;
					count+=1;
				}
				break;
			}
		}
		coeffRed(coeffEqu, i, numcol, count);
	}
	
}

int coefficientsReduction(float *coeffEqu, int numrow, int numcol){
	int count = 0;
	for(int i=0;i<numrow;i++)
	{
		coeffRed(coeffEqu, i, numcol, count);
	
	}
	return count;
}
