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

const int max_val = 10;
const int min_val = -10;
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
	//* MIXED PROBLEM: CONTINUOS - INTEGER - BINARY 
    	std::mt19937 eng(std::chrono::steady_clock::now().time_since_epoch().count());
    	std::uniform_int_distribution<> distr(1, max_val);

	int num_var = distr(eng); 
	int numrow = distr(eng);
	std::uniform_int_distribution<> distr_x(1, num_var);
	int num_x = distr_x(eng);
	std::uniform_int_distribution<> distr_y(0, num_var-num_x);
	int num_y = distr_y(eng);
	int num_z = num_var - num_x - num_y;
	std::cout<<"tot: "<<num_var<<" x: "<<num_x<<" y: "<<num_y<<" z: "<<num_z;
	std::vector<Variable*> cond;
	std::uniform_int_distribution<> distr_min(min_val, max_val);
	for(int i=0; i<num_x;i++)
	{
		int min = distr_min(eng);
		std::uniform_int_distribution<> distr_max(min+1, max_val);
		int max = distr_max(eng);
		cond.push_back(new floatVar("x"+patch::to_string(i), min, max));
	}
	for(int i=0; i<num_y;i++)
	{
		int min = distr_min(eng);
		std::uniform_int_distribution<> distr_max(min+1, max_val);
		int max = distr_max(eng);
		cond.push_back(new intVar("y"+patch::to_string(i), min, max));
	}
	for(int i=0; i<num_z;i++)
	{
		cond.push_back(new binVar("z"+patch::to_string(i)));
	}
	float coeffEqu[numrow][num_var+1];
	for(int i=0;i<numrow;i++)
	{
		for(int j=0;j<num_var+1;j++)
		{
			coeffEqu[i][j]=distr_min(eng)*neg_pos();
		}
	}
	printConstraints(&cond, (float*)coeffEqu, numrow, num_var);
	writeDat("./firstattempt.dat", &cond, (float *)coeffEqu, numrow, num_var, num_x, num_y,num_z);
	numrow = constraintsPreprocess(&cond, (float*)coeffEqu, numrow, num_var);
	boundsPreprocess(&cond, (float*)coeffEqu, numrow, num_var);
	printConstraints(&cond, (float*)coeffEqu, numrow, num_var);
	writeDat("./firstattemptafter.dat", &cond, (float *)coeffEqu, numrow, num_var, num_x, num_y,num_z);
}


