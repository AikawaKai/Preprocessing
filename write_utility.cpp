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
	outfile<<"set min_max := min, max;";
	
	outfile.close();
	
}
