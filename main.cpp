#include <iostream>  
#include <limits>
#include <typeinfo>
#include <vector>
#include "type.h"
#include "preprocess.h"
#include "print_utility.h"
#include "write_utility.h"

int main(){
	floatVar *x1 = new floatVar("X1" ,0 , 2);
	floatVar *x2 = new floatVar("x2" ,0 , 1);
	floatVar *x3 = new floatVar("x3" ,1 , 2);
	floatVar *x4 = new floatVar("x4" ,2 , 3);
	Variable *listOfVar[]={x1, x2, x3, x4};
	std::vector<Variable*> cond;
	cond.insert(cond.begin(),listOfVar, listOfVar+4);
	float b1 = -1;
	float b2 = 4;
	float b3 = 0;
	int row = 3;
	int col = 4;
	int num_x = 4;
	int num_y = 0;
	int num_z = 0;
	float coeffEqu[row][col+1] = {{1, 1, 1, -2, b1}, {-1, -3, 2, -1, b2}, {-1, 1, 0, 1, b3}};
	printConstraints(&cond, (float*)coeffEqu,row,col);
	writeDat("./Example4_prima.dat", &cond, (float*)coeffEqu, row, col, num_x, num_y, num_z);
	row = constraintsPreprocess(&cond, (float*)coeffEqu, row, col);
	std::cout<<"\n";
	printConstraints(&cond, (float*)coeffEqu, row, col);
	writeDat("./Example4_dopo.dat", &cond, (float*)coeffEqu, row, col, num_x, num_y, num_z);
	delete x1;
	delete x2;
	delete x3;
	delete x4;
}


