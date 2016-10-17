#include <iostream> 
#include <sstream> 
#include <limits>
#include <typeinfo>
#include <vector>
#include <random>
#include <chrono>
#include <ctime>
#include <string>
#include "type.h"
#include "preprocess.h"
#include "print_utility.h"
#include "write_utility.h"

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

int neg_pos()
{
	std::mt19937 eng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<> distr_pari_dispari(0, 1);
    if(distr_pari_dispari(eng)==0)
    {
    	return 1;
	}else
	{
		return -1;
	}
    
	
}

int main(){
	binVar *x1 = new binVar("x1");
	binVar *x2 = new binVar("x2");
	binVar *x3 = new binVar("x3");
	binVar *x4 = new binVar("x4");
	binVar *x5 = new binVar("x5");
	binVar *x6 = new binVar("x6");
	Variable *list[6] = {x1, x2, x3, x4, x5, x6};
	std::vector<Variable*>cond;
	cond.insert(cond.begin(), list, list+6);
	int numrow=1;
	int numcol=6;
	int num_x = 0;
	int num_y = 0;
	int num_z = 6;
	float coeffEqu[numrow][numcol+1]={6, 3, -5, 2, 7, -4, 15};
	printConstraints(&cond, (float*)coeffEqu, numrow, numcol);
	writeDat("./Example7_prima.dat", &cond, (float*)coeffEqu, numrow, numcol, num_x, num_y, num_z);
	coefficientsReduction((float*)coeffEqu, numrow, numcol);
	printConstraints(&cond, (float*)coeffEqu, numrow, numcol);
	writeDat("./Example7_dopo.dat", &cond, (float*)coeffEqu, numrow, numcol, num_x, num_y, num_z);
}


