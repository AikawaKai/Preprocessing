#include <iostream>
#include <vector>    

void boundsPreprocess(std::vector<Variable*> *cond, int numvar, int *coeffEqu, int numrow, int numcol);
bool update(std::vector<Variable*> cond, int numvar, int coeffEqu, int row, int pos);
