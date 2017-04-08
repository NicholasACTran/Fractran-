#include "Parser.h"

using namespace std;

//This file will hold all the functions used to parse the main Fractran Program into data structures for execution.

//This Function will take in a string, and then parse out the literals into a queue

void parse_Literals(queue<string> &FractranLiterals, string a)
{
    size_t prev_pos = 0, pos;
    while ((pos = a.find_first_of("/ *()^-", prev_pos)) != string::npos)
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

//When encountering a carrot during parsing, this function will parse the following
//literals. This will recursively call itself whenever it comes across another carrot,
//call asterisk_parse when it comes across an asterisk, or close and return on a right
//parenthesis.

int carrot_parse (queue<string> &FractranLiterals, vector<int> &Multiplication, vector<int> Exponentiation)
{
    string token_a = FractranLiterals.front();
    FractranLiterals.pop();
    string token_b = FractranLiterals.front();
    FractranLiterals.pop();
    if (token_a.find_first_not_of( "0123456789" ) == string::npos && token_b == "^")
    {
        int ProgramInteger;
        stringstream ss(token_a);
        ss >> ProgramInteger;
        if (ProgramInteger > 0)
        {
            Exponentiation.push_back(ProgramInteger);
            return carrot_parse(FractranLiterals, Multiplication, Exponentiation);
        }
        else throw "Cannot Parse " + token_a + token_b;
    }
    else if (token_a.find_first_not_of( "0123456789" ) == string::npos && token_b == ")")
    {
        int ProgramInteger;
        stringstream ss(token_a);
        ss >> ProgramInteger;
        if (ProgramInteger > 0)
        {
            int total = ProgramInteger;
            for (unsigned i = 0; i < Exponentiation.size(); i++)
                total = total^Exponentiation.at(i);
            for (unsigned i = 0; i < Multiplication.size(); i++)
                total = total * Multiplication.at(i);
            return total;
        }
        else throw "Cannot Parse " + token_a + token_b;
    }
    else if (token_a.find_first_not_of( "0123456789" ) == string::npos && token_b == "*")
    {
        int ProgramInteger;
        stringstream ss(token_a);
        ss >> ProgramInteger;
        if (ProgramInteger > 0)
        {
            int total = ProgramInteger;
            for (unsigned i = 0; i < Exponentiation.size(); i++)
                total = total^Exponentiation.at(i);
            Exponentiation.clear();
            Multiplication.push_back(total);
            return asterisk_parse(FractranLiterals, Multiplication, Exponentiation);
        }
        else throw "Cannot Parse " + token_a + token_b;
    }
    else throw "Cannot Parse " + token_a + token_b;
}

//When encountering an asterisk during parsing, this function will parse the following
//literals. This will recursively call itself whenever it comes across another asterisk,
//call carrot_parse when it comes across a carrot, or close and return on a right
//parenthesis.

int asterisk_parse (queue<string> &FractranLiterals, vector<int> &Multiplication, vector<int> &Exponentiation)
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
            return asterisk_parse(FractranLiterals, Multiplication, Exponentiation);
        }
        else throw "Cannot Parse " + token_a + token_b;
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
        else throw "Cannot Parse " + token_a + token_b;
    }
    else if (token_a.find_first_not_of( "0123456789" ) == string::npos && token_b == "^")
    {
        int ProgramInteger;
        stringstream ss(token_a);
        ss >> ProgramInteger;
        if (ProgramInteger > 0)
        {
            Exponentiation.push_back(ProgramInteger);
            return carrot_parse(FractranLiterals, Multiplication, Exponentiation);
        }
        else throw "Cannot Parse " + token_a + token_b;
    }
    else throw "Cannot Parse " + token_a + token_b;
}

//When encountering a left parenthesis during parsing, this will parse out the parenthesis
//and all possible following cases.

int left_parenthesis_parse(queue<string> &FractranLiterals, vector<int> &FractranIntegers)
{
    vector<int> multiplication;
    vector<int> exponentiation;
    string token = FractranLiterals.front();
    FractranLiterals.pop();
    if(!(token.find_first_not_of( "0123456789" ) == string::npos))
    {
        throw "Cannot Parse " + token;
    }
    int ProgramInteger;
    stringstream ss(token);
    ss >> ProgramInteger;
    if (ProgramInteger > 0)
        multiplication.push_back(ProgramInteger);
    else throw "Cannot Parse " + token;

    token = FractranLiterals.front();
    FractranLiterals.pop();
    if (token == ")")
        return multiplication.at(0);
    else if (token == "*")
        return asterisk_parse(FractranLiterals, multiplication, exponentiation);
    else if (token == "^")
        return carrot_parse(FractranLiterals, multiplication, exponentiation);
    else throw "Cannot Parse " + token;
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
            else throw "Cannot Parse " + token;
        }
        else if (token == "(")
            FractranIntegers.push_back(left_parenthesis_parse(FractranLiterals, FractranIntegers));
        else if (token == "-")
        {
            token = FractranLiterals.front();
            FractranLiterals.pop();
            if (token.find_first_not_of( "0123456789" ) == string::npos)
            {
                int ProgramInteger;
                stringstream ss(token);
                ss >> ProgramInteger;
                if (ProgramInteger > 0)
                    FractranIntegers.push_back(-ProgramInteger);
                else throw "Cannot Parse " + token;
            }
            else if (token == "(")
                FractranIntegers.push_back(-left_parenthesis_parse(FractranLiterals, FractranIntegers));
            else throw "Cannot Parse -" + token;
        }
        else if (token == "/")
            continue;
        else throw "Cannot Parse " + token;
    }
}

void parse_DEBUG(vector<int> &FractranIntegers)
    {
        for (unsigned i = 0; i < FractranIntegers.size(); i++)
            cout << FractranIntegers.at(i) << endl;
    }
