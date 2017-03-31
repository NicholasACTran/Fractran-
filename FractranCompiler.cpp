#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

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
        unsigned a = num;
        unsigned b = den;
        while(b)
        {
            x = a % b;
            a = b;
            b = x;
        }
        if (a > 1) return false;
        else return true;
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

//This Function will take in a string, and then parse out the literals into a queue

void parse_Literals(queue<string> &FractranLiterals, string a)
{
    size_t prev_pos = 0, pos;
    while ((pos = a.find_first_of("/ *()", prev_pos)) != string::npos)
    {
        if (pos > prev_pos && a.at(pos) == ' ')
            FractranLiterals.push(a.substr(prev_pos, pos-prev_pos));
        else if (pos > prev_pos)
        {
            FractranLiterals.push(a.substr(prev_pos, pos-prev_pos));
            FractranLiterals.push(a.substr(pos, 1));
        }
        else if (prev_pos == pos && a.at(pos) == ' ')
        {
            //do nothing
        }
        else
        {
            FractranLiterals.push(a.substr(pos, 1));
        }
        prev_pos = pos+1;
    }
    if (prev_pos < a.length())
        FractranLiterals.push(a.substr(prev_pos, string::npos));
}

//When encountering an asterisk during parsing, this function will parse the following
//literals until it reaches a close parenthesis.

int asterisk_parse (queue<string> &FractranLiterals, vector<int> &Multiplication)
{
    string token_a = FractranLiterals.front();
    FractranLiterals.pop();
    string token_b = FractranLiterals.front();
    FractranLiterals.pop();
    if (token_a.find_first_not_of( "0123456789" ) == string::npos && token_b == "*")
    {
        int ProgramInteger;
        stringstream ss(token_a);
        ss >> ProgramInteger;
        if (ProgramInteger > 0)
        {
            Multiplication.push_back(ProgramInteger);
            return asterisk_parse(FractranLiterals, Multiplication);
        }
        else
        {
            throw "Program must be written as rationals";
        }
    }
    else if (token_a.find_first_not_of( "0123456789" ) == string::npos && token_b == ")")
    {
        int ProgramInteger;
        stringstream ss(token_a);
        ss >> ProgramInteger;
        if (ProgramInteger > 0)
        {
            int product = ProgramInteger;
            for (unsigned i = 0; i < Multiplication.size(); i++)
                product = product*Multiplication.at(i);
            return product;
        }
        else
        {
            throw "Program must be written as rationals";
        }
    }
    else
    {
        throw "Program must be written as rationals";
    }
}

//When encountering a left parenthesis during parsing, this will parse out the parenthesis
//and all possible following cases.

int left_parenthesis_parse(queue<string> &FractranLiterals, vector<int> &FractranIntegers)
{
    vector<int> multiplication;
    string token = FractranLiterals.front();
    FractranLiterals.pop();
    if(!(token.find_first_not_of( "0123456789" ) == string::npos))
    {
        throw "Program must be written as rationals";
    }
    int ProgramInteger;
    stringstream ss(token);
    ss >> ProgramInteger;
    if (ProgramInteger > 0)
        multiplication.push_back(ProgramInteger);
    else
    {
        throw "Program must be written as rationals";
    }

    token = FractranLiterals.front();
    FractranLiterals.pop();
    if (token == ")")
        return multiplication.at(0);
    else if (token == "*")
        return asterisk_parse(FractranLiterals, multiplication);
    else
    {
        throw "Program must be written as rationals";
    }
}

//Function will parse out the queue of Literals into a vector of integers.

void parse(queue<string> &FractranLiterals, vector<int> &FractranIntegers)
{
    while(!FractranLiterals.empty())
    {
        string token = FractranLiterals.front();
        FractranLiterals.pop();
        if (token.find_first_not_of( "0123456789" ) == string::npos)
        {
            int ProgramInteger;
            stringstream ss(token);
            ss >> ProgramInteger;
            if (ProgramInteger > 0)
                FractranIntegers.push_back(ProgramInteger);
            else
            {
                throw "Program must be written as rationals";
            }
        }
        else if (token == "(")
            FractranIntegers.push_back(left_parenthesis_parse(FractranLiterals, FractranIntegers));
        else if (token == "/")
            continue;
        else
        {
            throw "Program must be written as rationals";
        }
    }
}

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

    int startInteger; //The input integer to the Fractran Program
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
            queue<string> FractranProgramLiterals;
            has_only_legal_characters = (a.find_first_not_of("0123456789/*() ") == string::npos);
            if (has_only_legal_characters)
            {
                parse_Literals(FractranProgramLiterals, a);
                parse(FractranProgramLiterals, FractranProgramIntegers);

                if(FractranProgramIntegers.size()%2 !=0)
                {
                    cout << "ERROR: All rationals need to be written in form a/b.";
                    return 0;
                }

                //From a vector of integers, creates rationals and constructs the FractranProgram vector.
                for (unsigned i = 0; i < FractranProgramIntegers.size(); i += 2)
                {
                    rational rat(FractranProgramIntegers.at(i), FractranProgramIntegers.at(i+1));
                    if(rat.coprime())
                        FractranProgram.push_back(rat);
                    else
                    {
                        cout << "ERROR: All rationals must be coprime." << endl;
                        cout << "The rational "<<rat.numerator()<<"/"<<rat.denominator()<<" is not coprime.";
                        return 0;
                    }
                }
            }

            //Parses the input integer from the second line.
            string b = fileVector.at(1);
            has_only_legal_characters = (b.find_first_not_of( "0123456789" ) == string::npos);
            if (has_only_legal_characters)
            {
                stringstream ss(b);
                ss >> startInteger;
            }
            else
            {
                cout << "ERROR: The second line needs to contain only integers.";
                return 0;
            }
        }
        else
        {
            cout << "ERROR: There are an incorrect number of lines in this program." << endl;
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
    unsigned int currentNumber = startInteger;
    vector<int> historyOfNumbers;
    historyOfNumbers.push_back(currentNumber);
    while(found)
    {
        cout<<currentNumber<<endl;
        found = false;
        for (unsigned j = 0; j < FractranProgram.size(); j++)
        {
            int product = FractranProgram.at(j).fractranMultiplication(currentNumber);
            if (product != 0)
            {
                found = true;
                currentNumber = product;
                break;
            }
        }
        if(!historyOfNumbers.empty())
        {
            if(find(historyOfNumbers.begin(), historyOfNumbers.end(), currentNumber) != historyOfNumbers.end())
            {
                cout << "LOOP DETECTED";
                break;
            }
            else historyOfNumbers.push_back(currentNumber);
        }
        else historyOfNumbers.push_back(currentNumber);
    }
    cout << currentNumber << endl;

    return 0;
}
