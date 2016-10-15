#include <iostream>
#include <vector>
#include <fstream>
#include "type.h"

void writeDat(std::vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol, int num_x, int num_y, int num_z)
{
	std::ofstream outfile;
	outfile.open("./afile.dat");
	outfile<<"ciao"<<std::endl;
	outfile.close();
	
}
