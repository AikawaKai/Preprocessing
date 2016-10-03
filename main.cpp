#include <iostream>  
#include "type.h"
using namespace std;

int main(){
	IntVar a;
	a.name = "X1";
	a.coeff = -1;
	a.showName();
	BinVar b;
	b.name = "Y1";
	b.coeff = 10;
	b.showName();
}
