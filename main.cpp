#include <iostream>  
#include <limits>
#include <typeinfo>
#include <vector>
#include "type.h"
#include "preprocess.h"
#include "print_utility.h"
using namespace std;

int main(){
	floatVar *x1 = new floatVar("x1" ,1 , 2);
	floatVar *x2 = new floatVar("x2" ,1 , 2);
	floatVar *x3 = new floatVar("x3" ,1 , 2);
	floatVar *x4 = new floatVar("x4" ,1 , 2);
	floatVar *x5 = new floatVar("x5" ,1 , 2);
	floatVar *x6 = new floatVar("x6" ,1 , 2);
	Variable *list[6] = {x1, x2, x3, x4, x5, x6};
	vector<Variable*>cond;
	cond.insert(cond.begin(), list, list+6);
	int numrow=1;
	int numcol=6;
	float coeffEqu[numrow][numcol+1]={6, 3, -5, 2, 7, -4, 15};
	coefficientsReduction((float*)coeffEqu, numrow, numcol);
	
}


