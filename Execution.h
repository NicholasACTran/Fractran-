#ifndef EXECUTION_H
#define EXECUTION_H
#include "Parser.h"

int executionLoop(int currentNumber, vector<rational> &ProgramList, vector< vector<rational> > &FunctionList);
void print_Program(vector<rational> &ProgramList, vector< vector<rational> > &FunctionList);

#endif
