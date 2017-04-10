#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Parser.h"
#include "Parser.cpp"

using namespace std;

//This is the main function of the Fractran Compiler. It asks for the name of the txt file of the Fractran program.
//This file must be formatted in a way for the rest of the compiler to work and not throw a compiler time error. The
//first is that the file only has two lines, where the first line represents the Fractran program, and the second
//line is the input integer. The first line must be a list of rationals, represented as fractions, which are separated
//by spaces. This compiler will output every change of the input integer and break if certain loops are detected, or
//a final output is determined.

int main()
{
    string nameOfFile;
    cout << "Enter name of file for Fractran Code without extension: ";
    cin >> nameOfFile;
    cout << endl;
    nameOfFile = nameOfFile + ".txt";

    unsigned int startInteger; //The input integer to the Fractran Program
    vector<rational> FractranProgram; //A vector of rationals that represent the Fractran Program

    string line;
    vector<string> fileVector;
    ifstream myfile(nameOfFile.c_str());
    if (myfile.is_open())
    {
        //Reads in the file
        while (getline(myfile, line))
            fileVector.push_back(line);
        myfile.close();

        bool has_only_legal_characters;
        if (fileVector.size() == 2)
        {
            //Parses the program from the first line.
            string a = fileVector.at(0);
            vector<int> FractranProgramIntegers;
            vector< vector<int> > FractranFunctionIntegers;
            queue<string> FractranProgramLiterals;
            has_only_legal_characters = (a.find_first_not_of("0123456789/*()^ -<>") == string::npos);
            if (has_only_legal_characters)
            {
                parse_Literals(FractranProgramLiterals, a);
                try
                {
                    parse(FractranProgramLiterals, FractranProgramIntegers, FractranFunctionIntegers);
                    integers_to_rationals(FractranProgramIntegers, FractranProgram);
                    parse_start_integer(fileVector.at(1), startInteger);
                }
                catch (char const* msg) {cout << msg; return 0;}
            }
            else
            {
                cout << "ERROR: Illegal characters in program.";
                return 0;
            }
        }
        else
        {
            cout << "ERROR: There are an incorrect number of lines in this program.\n";
            cout << "The first line contains the program. The second, the starting number.";
            return 0;
        }

    }
    else
    {
        cout << "ERROR: Unable to open file";
        return 0;
    }

    //Runs the program
    bool found = true;
    bool jump = false;
    unsigned int currentNumber = startInteger;
    unsigned j = 0;
    vector<int> historyOfNumbers;
    historyOfNumbers.push_back(currentNumber);
    while(found)
    {
        cout<<currentNumber<<endl;
        jump = false;
        found = false;
        for (; j < FractranProgram.size(); j++)
        {
            int product = FractranProgram.at(j).fractranMultiplication(currentNumber);
            if (product != 0 && FractranProgram.at(j).numerator() < 0)
            {
                j = (abs(FractranProgram.at(j).numerator()) % FractranProgram.size()) - 1;
                found = true;
                jump = true;
                break;
            }
            else if (product != 0 && FractranProgram.at(j).denominator() < 0)
            {
                j = ((FractranProgram.at(j).numerator() * currentNumber) % FractranProgram.size()) - 1;
                found = true;
                jump = true;
                break;
            }
            else if (product != 0)
            {
                j = 0;
                found = true;
                currentNumber = product;
                break;
            }
        }
        if(!historyOfNumbers.empty() && found && !jump)
        {
            if(find(historyOfNumbers.begin(), historyOfNumbers.end(), currentNumber) != historyOfNumbers.end())
            {
                cout << "LOOP DETECTED\n";
                break;
            }
            else historyOfNumbers.push_back(currentNumber);
        }
        else if (historyOfNumbers.empty())
            historyOfNumbers.push_back(currentNumber);
    }
    cout << "Program End";

    return 0;
}
