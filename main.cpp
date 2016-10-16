#include <iostream>  
#include <limits>
#include <typeinfo>
#include <vector>
#include "type.h"
#include "preprocess.h"
#include "print_utility.h"
#include "write_utility.h"

int main(){
	intVar *x1 = new intVar("x1", 0, 2);
	intVar *x2 = new intVar("x2", 0, 1);
	intVar *x3 = new intVar("x3", 1, 2);
	intVar *x4 = new intVar("x4", 2, 3);
	int numcol = 4;
	int numrow = 3;
	float b1 = -6;
	float b2 = 4;
	float b3 = 0;
	float coeffEqu [numrow][numcol+1]={{1, 1, 1, -2, b1}, {-1, -3, 2, -1, b2}, {-1, 1, 0, 1, b3}};
	std::vector<Variable*> cond;
	Variable *list[]={x1, x2, x3, x4};
	cond.insert(cond.begin(), list, list+4);
	int num_x = 0;
	int num_y = 4;
	int num_z = 0;
	printConstraints(&cond, (float*)coeffEqu, numrow, numcol);
	writeDat("./Example3_prima.dat", &cond, (float*)coeffEqu, numrow, numcol, num_x, num_y, num_z);
	constraintsPreprocess(&cond, (float*)coeffEqu, numrow, numcol);
}


