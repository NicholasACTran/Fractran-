#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

//This file holds all of the function declarations for the functions used to parse
//the Fractran program and create the data structure for execution.

void parse_Literals(queue<string> &FractranLiterals, string a);
int asterisk_parse(queue<string> &FractranLiterals, vector<int> &Multiplication, vector<int> &Exponentiation);
int carrot_parse (queue<string> &FractranLiterals, vector<int> &Multiplication, vector<int> Exponentiation);
int left_parenthesis_parse(queue<string> &FractranLiterals, vector<int> &FractranIntegers);
void parse(queue<string> &FractranLiterals, vector<int> &FractranIntegers);
void parse_DEBUG(vector<int> &FractranIntegers);

#endif
