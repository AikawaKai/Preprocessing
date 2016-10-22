#include <iostream>
#include <vector>

int boundsPreprocess(std::vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol);
int constraintsPreprocess(std::vector<Variable*> *cond, float *coeffEqu, int numrow, int numcol);
bool update(std::vector<Variable*> *cond, int numcol, float coeffEqu, int numrow, int pos);
void deleteConstraint(float *coeffEqu, int i, int numrow, int numcol);
void fixingVariables(std::vector<Variable*> *cond, float *coeffEqu, int numcol);
int coefficientsReduction(float *coeffEqu, int numrow, int numcol);
void coeffRed(float *coeffEqu, int i, int numcol, int &count);
