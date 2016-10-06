#include "type.h"
#include <iostream>
using namespace std;

Variable * boundsPreprocess(Variable cond[], int *coeffEqu, int numrow, int numcol) {
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
	getchar();
	return NULL;
}

