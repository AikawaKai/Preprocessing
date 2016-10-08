#include "type.h"
#include <iostream>
#include <vector>    
using namespace std;

Variable* boundsPreprocess(vector<Variable*> *cond, int numvar, int *coeffEqu, int numrow, int numcol) {
	bool updated = true;
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
	}
	for(int i=0; i<numvar; i++)
	{
		(*cond)[i]->showType();
		
		//**cond[i]->showType();
	}
	getchar();
	return NULL;
}

