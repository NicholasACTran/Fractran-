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

//The rational struct is used to represent the data of the Fractran program.
//It holds only the numerator and denominator of the data type and can check if they are coprime.
//FractranMultiplication() is a function used to check the multiplication of the rational
//and a number, returning the product if it is a positive integer, else 0.

struct rational
{
    rational(int numerator, int denominator) : num(numerator), den(denominator) {}

    int numerator() const {return num;}
    int denominator() const {return den;}

    bool coprime()
    {
        unsigned x;
        unsigned a = abs(num);
        unsigned b = abs(den);
        while(b)
        {
            x = a % b;
            a = b;
            b = x;
        }
        if (a > 1) return false;
        else return true;
    }

    bool single_negative()
    {
        if (num < 0 && den < 0)
            return false;
        return true;
    }

    int fractranMultiplication(unsigned x)
    {
        if ((x * num) % den == 0) return (x * num / den);
        else return 0;
    }

    private:
        int num;
        int den;
};

void parse_Literals(queue<string> &FractranLiterals, string a);
int asterisk_parse(queue<string> &FractranLiterals, vector<int> &Multiplication, vector<int> &Exponentiation);
int carrot_parse (queue<string> &FractranLiterals, vector<int> &Multiplication, vector<int> Exponentiation);
int left_parenthesis_parse(queue<string> &FractranLiterals, vector<int> &FractranIntegers);
void parse(queue<string> &FractranLiterals, vector<int> &FractranIntegers);
void parse_DEBUG(vector<int> &FractranIntegers);
void integers_to_rationals(vector<int> &FractranIntegers, vector<rational> &FractranProgram);
void parse_start_integer (string b, unsigned int &a);

#endif
