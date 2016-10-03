#include <iostream>  
#include <limits>
#include "type.h"
using namespace std;

int main(){
	floatVar x1;
	floatVar x2;
	floatVar x3;
	floatVar y4;
	intVar y5;
	
	x1.name="X1";
	x2.name="X2";
	x3.name="X3";
	y4.name="Y4";
	y5.name="Y5";
	
	x1.max = std::numeric_limits<float>::max();
	x1.min = 0;
	x2.min = 0;
	x2.max = 3;
	x3.min = 1;
	x3.max = 5;
	y4.min = 2;
	y4.max = 4;
	y5.max = 0;
	y5.max = std::numeric_limits<int>::max();
	
	Variable equ1 []  = {x1, x2, x3, y4, y5};
	int coeffEqu1 [] = {4, -3, -2, 1, 2};
	Variable equ2 []  = {x1, x2, x3, y4, y5};
	int coeffEqu2 [] = {-3, 2, -1, 2, 3};
}
