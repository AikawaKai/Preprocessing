#include <iostream>  
#include <limits>
#include <typeinfo>
#include <vector>
#include "type.h"
#include "preprocess.h"
#include "print_utility.h"
#include "write_utility.h"

int main(){
	floatVar *x1 = new floatVar("x1" ,1 , 2);
	floatVar *x2 = new floatVar("x2" ,1 , 2);
	floatVar *x3 = new floatVar("x3" ,1 , 2);
	floatVar *x4 = new floatVar("x4" ,1 , 2);
	floatVar *x5 = new floatVar("x5" ,1 , 2);
	floatVar *x6 = new floatVar("x6" ,1 , 2);
	Variable *list[6] = {x1, x2, x3, x4, x5, x6};
	std::vector<Variable*>cond;
	cond.insert(cond.begin(), list, list+6);
	int numrow=1;
	int numcol=6;
	int num_x = 6;
	int num_y = 0;
	int num_z = 0;
	float coeffEqu[numrow][numcol+1]={6, 3, -5, 2, 7, -4, 15};
	printConstraints(&cond, (float*)coeffEqu, numrow, numcol);
	writeDat("./Example7_prima.dat", &cond, (float*)coeffEqu, numrow, numcol, num_x, num_y, num_z);
	coefficientsReduction((float*)coeffEqu, numrow, numcol);
	printConstraints(&cond, (float*)coeffEqu, numrow, numcol);
	writeDat("./Example7_dopo.dat", &cond, (float*)coeffEqu, numrow, numcol, num_x, num_y, num_z);
}


