#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include "type.h"

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

std::string seqIntToString(int numofelements)
{
	std::string output = "";
	if(numofelements==0)
	{
		numofelements=1;
	}
	for(int i=0;i<numofelements;i++)
	{
		if(i==numofelements-1)
		{
			output+=patch::to_string(i)+";";
		}
		else
		{
			output+=patch::to_string(i)+",";	
		}
	}
	return output;
}

std:: string matrixCoeffToString(float *coeffEqu, int numrow, int numcol, int offset, int num_var)
{
	std::string firstrow = "\t";
	std::string nextline = "";
	for(int i=0;i<num_var;i++)
		{
			firstrow+=patch::to_string(i)+"  ";
		}
	if(num_var==0)
	{
		for(int i=0;i<numrow;i++)
		{
			nextline+=patch::to_string(i)+"\t"+"0"+"\n";
		}
		nextline+=";";
	}
	else
	{
		firstrow+="=:";
		for(int i=0;i<numrow;i++)
		{
			nextline+=patch::to_string(i)+"\t";
			for(int j=offset;j<num_var+offset;j++)
			{
				if(j==num_var+offset-1 && i==numrow-1)
				{
					nextline+=patch::to_string(coeffEqu[i*(numcol+1)+j])+";";
				}
				else
				{
					nextline+=patch::to_string(coeffEqu[i*(numcol+1)+j])+"  ";	
				}
			}
			nextline+="\n";
		}
	}
	
	
	return firstrow+"\n"+nextline;
}

void writeDat(std::vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol, int num_x, int num_y, int num_z)
{
	std::ofstream outfile;
	outfile.open("./prova.dat");
	std::string output;
	output = seqIntToString(numcol);
	outfile<<"set num_var := "<<output<<std::endl;
	output = seqIntToString(numrow);
	outfile<<"set num_vinc := "<<output<<std::endl;
	output = seqIntToString(num_x);
	outfile<<"set num_varx := "<<output<<std::endl;
	output = seqIntToString(num_y);
	outfile<<"set num_vary := "<<output<<std::endl;
	output = seqIntToString(num_z);
	outfile<<"set num_varz := "<<output<<std::endl;
	outfile<<"set min_max := min, max;"<<std::endl;
	output = matrixCoeffToString(coeffEqu, numrow, numcol, 0, num_x);
	outfile<<"param coeff_x:"<<std::endl;
	outfile<<output<<std::endl;
	output = matrixCoeffToString(coeffEqu, numrow, numcol, num_x, num_y);
	outfile<<"param coeff_y:"<<std::endl;
	outfile<<output<<std::endl;
	output = matrixCoeffToString(coeffEqu, numrow, numcol, num_x+num_y, num_z);
	outfile<<"param coeff_z:"<<std::endl;
	outfile<<output<<std::endl;
	
	outfile.close();
	
}
