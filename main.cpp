#include <iostream> 
#include <sstream> 
#include <fstream>
#include <iterator>
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

//* FUNZIONE PER LEGGERE I PARAMETRI DA FILE *//
Parameters readFileToVector(const std::string& filename)
{
	Parameters param;
    std::ifstream source;
    source.open(filename);
    std::vector<std::string> lines;
    std::string line;
    std::vector<std::string> tokens;
    while (std::getline(source, line))
    {
    	std::istringstream iss(line);
        tokens = {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
        lines.push_back(tokens.at(1));
        
    }
    param.numOfVar=std::stoi(lines.at(0));
    param.numRow = std::stoi(lines.at(1));
    param.maxVal=std::stoi(lines.at(2));
    param.minVal=std::stoi(lines.at(3));
    param.seed1 = std::stoi(lines.at(4));
    param.namefiledat1 = lines.at(5);
    param.namefiledat2 = lines.at(6);
    param.bin = std::stoi(lines.at(7));
    param.max_tn = std::stoi(lines.at(8));
    param.min_tn = std::stoi(lines.at(9));
    return param;
}

//* MIXED PROBLEM: CONTINUOS - INTEGER - BINARY  *//
int main(int argc,char *argv[]){
	
	std::string charactersFilename(argv[1]);
    Parameters param = readFileToVector(charactersFilename);
    
    int num_var = param.numOfVar;
    int numrow = param.numRow;
	int max_val = param.maxVal;
	int min_val = param.minVal;
	int seed1 = param.seed1;
	std::string namefile1 = param.namefiledat1;
	std::string namefile2 = param.namefiledat2;
	int bin = param.bin;
	int max_tn = param.max_tn;
	int min_tn = param.min_tn;
    
    //* RANDOM *//
    //std::mt19937 eng(std::chrono::steady_clock::now().time_since_epoch().count());
    
    //* PSEUDO RANDOM *//	
    std::mt19937 eng(seed1);
    
    //* DISTRIBUZIONE TERMINI NOTI VINCOLI *//
    std::uniform_int_distribution<> distr_tn(min_tn, max_tn);
	
	int bounds;
	int coeffred;
	int num_x, num_y, num_z;
	
	//* CASO BINARIO O CASO MIP *//
	if(bin==1)
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
	
	//* DISTRIBUZIONE PER COEFFICIENTI E BOUND DELLE VARIABILI *//
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
			if(j==num_var)
			{
				coeffEqu[i][j]=distr_tn(eng);
			}
			else
			{
				coeffEqu[i][j]=distr_min(eng);
			}
		}
	}
	printConstraints(&cond, (float*)coeffEqu, numrow, num_var);
	
	//* SCRIVO SU FILE I DATI DEL PROBLEMA SENZA PREPROCESSAMENTO *//
	writeDat(namefile1, &cond, (float *)coeffEqu, numrow, num_var, num_x, num_y,num_z);
	
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
	
	printConstraints(&cond, (float*)coeffEqu, numrow, num_var);
	writeDat(namefile2, &cond, (float *)coeffEqu, numrow, num_var, num_x, num_y,num_z);
	
	std::cout<<"\n\ntot: "<<num_var<<" x: "<<num_x<<" y: "<<num_y<<" z: "<<num_z<<" Numrow: "<<numrow<<std::endl;
	
}


