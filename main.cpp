#include <iostream>  
#include <limits>
#include <typeinfo>
#include <vector>
#include "type.h"
#include "preprocess.h"
#include "print_utility.h"
using namespace std;

int main(){
	/*FIRST EXAMPLE MIXED INTEGER VARIABLE
	floatVar* x1 = new floatVar();
	floatVar* x2 = new floatVar();
	floatVar* x3 = new floatVar();
	intVar* y4 = new intVar();
	intVar* y5 = new intVar();	
	x1->name="X1";
	x2->name="X2";
	x3->name="X3";
	y4->name="Y4";
	y5->name="Y5";
	
	x1->min = 0;
	x1->max = 10000000;
	x2->min = 0;
	x2->max = 3;
	x3->min = 1;
	x3->max = 5;
	y4->min = 2;
	y4->max = 4;
	y5->min = 0;
	y5->max = 10000000;
	
	std::vector<Variable*> cond;
	cond.push_back(x1);
	cond.push_back(x2);
	cond.push_back(x3);
	cond.push_back(y4);
	cond.push_back(y5);
	int b1 = 13;
	int b2 = -9;
	int numrow = 2;
	int numcol = 5;
	int coeffEqu [numrow][numcol+1] = {{4, -3, -2, 1, 2, b1}, {-3, 2, -1, 2, 3, b2}};
	
	/*SECOND EXAMPLE: BINARY VARIABLE
	binVar *y1 = new binVar();
	binVar *y2 = new binVar();
	binVar *y3 = new binVar();
	binVar *y4 = new binVar();
	y1->name = "Y1";
	y2->name = "Y2";
	y3->name = "Y3";
	y4->name = "Y4";
	Variable *lista[] = {y1, y2, y3, y4};
	std::vector<Variable*> cond;
	cond.insert(cond.begin(), lista, lista+4);
	int b1 = 0;
	int b2 = -5;
	int numrow = 2;
	int numcol = 4;
	int coeffEqu [numrow][numcol+1]={{8, 11, -9, 4, b1}, {1, -4, -6, 1, b2}};
	
	cout<<"[Before update]\n";
	print_constraints(&cond, (int *)coeffEqu, numrow, numcol);
	
	cout<<"\n[After update]\n";
	boundsPreprocess(&cond, (int *)coeffEqu, numrow, numcol);
	print_constraints(&cond, (int *)coeffEqu, numrow, numcol);*/
	
	//*Third Example
	intVar *x1 = new intVar();
	intVar *x2 = new intVar();
	intVar *x3 = new intVar();
	intVar *x4 = new intVar();
	x1->name = "X1";
	x2->name = "X2";
	x3->name = "X3";
	x4->name = "X4";
	x1->min = 0;
	x1->max = 2;
	x2->min = 0;
	x2->max = 1;
	x3->min = 1;
	x3->max = 2;
	x4->min = 2;
	x4->max = 3;
	int numcol = 4;
	int numrow = 3;
	int b1 = -6;
	int b2 = 4;
	int b3 = 0;
	int coeffEqu [numrow][numcol+1]={{1, 1, 1, -2, b1}, {-1, -3, 2, -1, b2}, {-1, 1, 0, 1, b3}};
	vector<Variable*> cond;
	Variable *lista[] = {x1, x2, x3, x4};
	cond.insert(cond.begin(),lista, lista+4);
	print_constraints(&cond, (int*)coeffEqu, numrow, numcol);
	
}


