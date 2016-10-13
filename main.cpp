#include <iostream>  
#include <limits>
#include <typeinfo>
#include <vector>
#include "type.h"
#include "preprocess.h"
#include "print_utility.h"
using namespace std;

int main(){
	binVar *y1 = new binVar("y1");
	binVar *y2 = new binVar("y2");
	binVar *y3 = new binVar("y3");
	vector<Variable*> cond;
	Variable *list[3]= {y1, y2, y3};
	cond.insert(cond.begin(), list, list+3);
	float b1 = 7;
	float b2 = 3;
	int numrow = 2;
	int numcol = 3;
	float coeffEqu[numrow][numcol+1]={{2, 1, 3, b1},{3, -2, -1, b2}};
	printConstraints(&cond, (float*)coeffEqu, numrow, numcol);
	constraintsPreprocess(&cond, (float*)coeffEqu, numrow, numcol);
	printConstraints(&cond, (float*)coeffEqu, numrow, numcol);
}


