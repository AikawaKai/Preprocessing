#include <iostream>
#include <vector>    

void boundsPreprocess(std::vector<Variable*> *cond, int *coeffEqu, int numrow, int numcol);
bool update(std::vector<Variable*> *cond, int numcol, int coeffEqu, int numrow, int pos);
