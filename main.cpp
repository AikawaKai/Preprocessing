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

const int max_var = 20;
const int max_val = 10;
const int min_val = -10;

//* PATCH PER IL TO_STRING DI VARIABILI INTERE *//
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

//* FUNZIONE PER IL CAMBIO DI SEGNO *//
int neg_pos()
{
	std::mt19937 eng(11);
    std::uniform_int_distribution<> distr_pari_dispari(0, 1);
    if(distr_pari_dispari(eng)==0)
    {
    	return 1;
	}else
	{
		return -1;
	}
    
	
}

//* MIXED PROBLEM: CONTINUOS - INTEGER - BINARY  *//
int main(int argc,char *argv[]){
    //std::mt19937 eng(std::chrono::steady_clock::now().time_since_epoch().count());
    //* PSEUDO RANDOM *//	
    std::mt19937 eng(5);
    std::uniform_int_distribution<> distr(1, max_var);
	
	int bounds;
	int coeffred;
	int num_var = distr(eng);
	int numrow = distr(eng);
	int num_x, num_y, num_z;
	
	//* LANCIO UN DADO PER CAPIRE SE SIAMO IN UN MIP O BIP (PER TESTARE LA COEFFICIENT REDUCTION NEL CASO SPECIFICO DELLA BIP) *//
	if(neg_pos()==-1)
	{
		//* CASO BINARIO *//
		num_x = 0;
		num_y = 0;
		num_z = num_var;
	}
	else
	{
		//* CASO MIXED *//
		std::uniform_int_distribution<> distr_x(0, num_var);
		num_x = distr_x(eng);
		std::uniform_int_distribution<> distr_y(0, num_var-num_x);
		num_y = distr_y(eng);
		num_z = num_var - num_x - num_y;
	}
	std::cout<<"tot: "<<num_var<<" x: "<<num_x<<" y: "<<num_y<<" z: "<<num_z;
	
	//* COSTRUISCO IL PROBLEMA *//
	std::vector<Variable*> cond;
	std::uniform_int_distribution<> distr_min(min_val, max_val);
	
	//* VARIABILI CONTINUE *//
	for(int i=0; i<num_x;i++)
	{
		int min = distr_min(eng);
		std::uniform_int_distribution<> distr_max(min+1, max_val);
		int max = distr_max(eng);
		if(min == max_val)
		{
			max = min;
		}
		cond.push_back(new floatVar("x"+patch::to_string(i), min, max));
	}
	
	//* VARIABILI INTERE *//
	for(int i=0; i<num_y;i++)
	{
		int min = distr_min(eng);
		std::uniform_int_distribution<> distr_max(min+1, max_val);
		int max = distr_max(eng);
		if(min == max_val)
		{
			max = min;
		}
		cond.push_back(new intVar("y"+patch::to_string(i), min, max));
	}
	
	//* VARIABILI BINARIE *//
	for(int i=0; i<num_z;i++)
	{
		cond.push_back(new binVar("z"+patch::to_string(i)));
	}
	
	//* COSTRUISCO MATRICE DEI COEFFICIENTI E TERMINI NOTI *//
	float coeffEqu[numrow][num_var+1];
	for(int i=0;i<numrow;i++)
	{
		for(int j=0;j<num_var+1;j++)
		{
			coeffEqu[i][j]=distr_min(eng);
		}
	}
	printConstraints(&cond, (float*)coeffEqu, numrow, num_var);
	
	//* SCRIVO SU FILE I DATI DEL PROBLEMA SENZA PREPROCESSAMENTO *//
	writeDat("./firstattempt.dat", &cond, (float *)coeffEqu, numrow, num_var, num_x, num_y,num_z);
	
	std::cout<<"\n------ AFTER PREPROCESSING -------\n\n";
	
	//* PROVO A RIDURRE I BOUNDS DELLE VARIABILI *//
	bounds = boundsPreprocess(&cond, (float*)coeffEqu, numrow, num_var);
	std::cout<<"\nBounds tightned: "<<bounds<<std::endl;
	
	//* APPLICO LA COEFFICIENTS REDUCTION SOLO NEL CASO BINARIO *//
	if(num_x==0 && num_y==0)
	{
		coeffred = coefficientsReduction((float*)coeffEqu, numrow, num_var);
		std::cout<<"Binary problem. Reduced coefficients: "<<coeffred<<std::endl;
	}
	
	//* APPLICO PREPROCESS SUI VINCOLI *//
	numrow = constraintsPreprocess(&cond, (float*)coeffEqu, numrow, num_var);
	
	//* SCRIVI SU FILE SOLO SE IL PROBLEMA HA SOLUZIONI AMMISSIBILI *//
	if(numrow!=-1)
	{
		printConstraints(&cond, (float*)coeffEqu, numrow, num_var);
		writeDat("./firstattemptafter.dat", &cond, (float *)coeffEqu, numrow, num_var, num_x, num_y,num_z);
	}
	std::cout<<"\n\ntot: "<<num_var<<" x: "<<num_x<<" y: "<<num_y<<" z: "<<num_z<<" Numrow: "<<numrow<<std::endl;
	
}


