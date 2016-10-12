#include <iostream>
#include <vector>

void boundsPreprocess(std::vector<Variable*> *cond, int *coeffEqu, int numrow, int numcol);
void constraintsPreprocess(std::vector<Variable*> *cond, int *coeffEqu, int numrow, int numcol);
bool update(std::vector<Variable*> *cond, int numcol, int coeffEqu, int numrow, int pos);
void deleteConstraint(int *coeffEqu, int i, int numcol);
