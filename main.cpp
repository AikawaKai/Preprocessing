#include <iostream>  
#include <limits>
#include <typeinfo>
#include <vector>
#include "type.h"
#include "preprocess.h"
using namespace std;

int main(){
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
	
	x1->max = std::numeric_limits<float>::max();
	x1->min = 0;
	x2->min = 0;
	x2->max = 3;
	x3->min = 1;
	x3->max = 5;
	y4->min = 2;
	y4->max = 4;
	y5->max = 0;
	y5->max = std::numeric_limits<int>::max();
	
	std::vector<Variable*> cond;
	cond.push_back(x1);
	cond.push_back(x2);
	cond.push_back(x3);
	cond.push_back(y4);
	cond.push_back(y5);
	int b1 = 13;
	int b2 = -9;
	int coeffEqu [2][5] = {{4, -3, -2, 1, 2}, {-3, 2, -1, 2, 3}};
	Variable *newCond = boundsPreprocess(&cond, 5, (int *)coeffEqu, 2, 5);
}


