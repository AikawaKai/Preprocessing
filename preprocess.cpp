#include "type.h"
#include <iostream>
#include <vector>    
using namespace std;

bool update(vector<Variable*> *cond, int numvar, int *coeffEqu, int row, int pos){
	//int currcoff = coeffEqu[row*numvar+pos];
	for(int j=0;j<numvar;j++)
	{
		if(j!=pos)
		{
			cout<<coeffEqu[row*numvar+j];;
			cout<<" ";
		}
	}
	cout<<"\n";
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

