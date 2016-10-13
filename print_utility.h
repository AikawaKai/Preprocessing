#include <string>
#include <iostream>
#include <math.h>
#include <vector>

void printConstraints(std::vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol);
bool checkRow(vector<Variable*> *cond, float *coeffEqu, int i, int numcol);
