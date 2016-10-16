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
		firstrow+="0 :=";
		for(int i=0;i<numrow;i++)
		{
			if(i==numrow-1)
			{
				nextline+=patch::to_string(i)+"\t"+"0"+";";	
			}
			else
			{
				nextline+=patch::to_string(i)+"\t"+"0"+"\n";
			}
			
		}
		nextline+="\n";
	}
	else
	{
		firstrow+=":=";
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

std::string matrixBoundsToString(std::vector<Variable*> *cond, int offset, int numrow, int num_var)
{
	std::string firstrow = "\t";
	std::string nextline = "";
	firstrow+="min	max :=";
	if(num_var == 0)
	{
		nextline+="0\t0\t0;";
	}
	else
	{
		for(int i=offset;i<num_var+offset;i++)
		{
			nextline+=patch::to_string(i-offset)+"\t";
			if(i==num_var-1+offset)
			{
				nextline+=patch::to_string((*cond)[i]->returnMin())+"\t"+patch::to_string((*cond)[i]->returnMax())+";";
			}
			else
			{
				nextline+=patch::to_string((*cond)[i]->returnMin())+"\t"+patch::to_string((*cond)[i]->returnMax())+"\n";
			}	
		}		
	}
	return firstrow+"\n"+nextline+"\n";
}

std::string bParametersToString(float* coeff, int numrow, int numcol)
{
	std::string to_return = "";
	for(int i=0;i<numrow;i++)
	{
		if(i==numrow-1)
		{
			to_return+=patch::to_string(i)+"\t"+patch::to_string(coeff[i*(numcol+1)+numcol])+";";
		}
		else
		{
			to_return+=patch::to_string(i)+"\t"+patch::to_string(coeff[i*(numcol+1)+numcol])+",\t";
		}
	}
	return to_return;
}

void writeDat(std::string name_file, std::vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol, int num_x, int num_y, int num_z)
{
	if(numrow==0)
	{
		for(int j=0; j<numcol+1;j++)
		{
			coeffEqu[j] = 0;
		}
		numrow+=1;
	}
	std::ofstream outfile;
	outfile.open(name_file.c_str());
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
	output = matrixBoundsToString(cond, 0, numrow, num_x);
	outfile<<"param bounds_x:"<<std::endl;
	outfile<<output<<std::endl;
	output = matrixBoundsToString(cond, num_x, numrow, num_y);
	outfile<<"param bounds_y:"<<std::endl;
	outfile<<output<<std::endl;		
	outfile<<"param b:= ";
	output = bParametersToString(coeffEqu, numrow, numcol);
	outfile<<output<<std::endl;
	outfile.close();
}
