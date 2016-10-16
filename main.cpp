#include <iostream>  
#include <limits>
#include <typeinfo>
#include <vector>
#include "type.h"
#include "preprocess.h"
#include "print_utility.h"
#include "write_utility.h"

int main(){
	floatVar* x1 = new floatVar("x1" ,0 , 10000000);
	floatVar* x2 = new floatVar("x2" ,0 , 3);
	floatVar* x3 = new floatVar("x3" ,1 , 5);
	intVar* y4 = new intVar("y4" , 2, 4);
	intVar* y5 = new intVar("y5" , 0, 10000000);
	Variable *list[]={x1, x2, x3, y4, y5};
	std::vector<Variable*> cond;
	cond.insert(cond.begin(),list, list+5);
	
	float b1 = 13;
	float b2 = -9;
	int numrow = 2;
	int numcol = 5;
	int num_x = 3;
	int num_y = 2;
	int num_z = 0;
	float coeffEqu [numrow][numcol+1] = {{4, -3, -2, 1, 2, b1}, {-3, 2, -1, 2, 3, b2}};
	writeDat("./esempio1_prima.dat", &cond, (float*)coeffEqu, numrow, numcol, num_x, num_y, num_z);
	printConstraints(&cond, (float*) coeffEqu, numrow, numcol);
	boundsPreprocess(&cond, (float*) coeffEqu, numrow, numcol);
	writeDat("./esempio1_dopo.dat", &cond, (float*)coeffEqu, numrow, numcol, num_x, num_y, num_z);
	std::cout<<"\n";
	printConstraints(&cond, (float*) coeffEqu, numrow, numcol);
}


