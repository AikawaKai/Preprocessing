#include <iostream>
#include <vector>

void boundsPreprocess(std::vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol);
void constraintsPreprocess(std::vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol);
bool update(std::vector<Variable*> *cond, int numcol, float coeffEqu, int numrow, int pos);
void deleteConstraint(float *coeffEqu, int i, int numcol);
