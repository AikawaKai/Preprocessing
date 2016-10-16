#include <iostream>  
#include <limits>
#include <typeinfo>
#include <vector>
#include "type.h"
#include "preprocess.h"
#include "print_utility.h"
#include "write_utility.h"

int main(){
	binVar *y1 = new binVar("y1");
	binVar *y2 = new binVar("y2");
	binVar *y3 = new binVar("y3");
	binVar *y4 = new binVar("y4");
	Variable *lista[] = {y1, y2, y3, y4};
	std::vector<Variable*> cond;
	cond.insert(cond.begin(), lista, lista+4);
	float b1 = 0;
	float b2 = -5;
	int numrow = 2;
	int numcol = 4;
	float coeffEqu [numrow][numcol+1]={{8, 11, -9, 4, b1}, {1, -4, -6, 1, b2}};
	int num_x = 0;
	int num_y = 0;
	int num_z = 4;
	
	std::cout<<"[Before update]\n";
	printConstraints(&cond, (float *)coeffEqu, numrow, numcol);
	writeDat("./Example2_prima.dat", &cond, (float *)coeffEqu, numrow, numcol, num_x, num_y, num_z); 
	std::cout<<"\n[After update]\n";
	boundsPreprocess(&cond, (float *)coeffEqu, numrow, numcol);
	printConstraints(&cond, (float *)coeffEqu, numrow, numcol);
	writeDat("./Example2_dopo.dat", &cond, (float *)coeffEqu, numrow, numcol, num_x, num_y, num_z);
}


