#include "Execution.h"

using namespace std;

//This is the execution loop that will run the program.

int executionLoop(int currentNumber, vector<rational> &ProgramList, vector< vector<rational> > &FunctionList)
{
    //Runs the program
    bool found = true;
    bool jump = false;
    unsigned j = 0;
    vector<int> historyOfNumbers;
    historyOfNumbers.push_back(currentNumber);
    while(found)
    {
        cout<<currentNumber<<"\n";
        jump = false;
        found = false;
        for (; j < ProgramList.size(); j++)
        {
            if (ProgramList.at(j).getfunctiontype() == -1)
            {
                int product = ProgramList.at(j).fractranMultiplication(currentNumber);
                if (product != 0 && ProgramList.at(j).numerator() < 0)
                {
                    j = (abs(ProgramList.at(j).numerator()) % ProgramList.size()) - 1;
                    found = true;
                    jump = true;
                    break;
                }
                else if (product != 0 && ProgramList.at(j).denominator() < 0)
                {
                    j = ((ProgramList.at(j).numerator() * currentNumber) % ProgramList.size()) - 1;
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
            else
            {
                currentNumber = executionLoop(currentNumber, FunctionList.at(ProgramList.at(j).getfunctionpointer()), FunctionList);
                found = true;
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

    return currentNumber;
}

//Helper function used to Debug the program during the execution loop.

void print_Program(vector<rational> &ProgramList, vector< vector<rational> > &FunctionList)
{
    for (unsigned i = 0; i < ProgramList.size(); i++)
    {
        ProgramList.at(i).toString();
        if (ProgramList.at(i).getfunctiontype() != -1)
        {
            cout<<ProgramList.at(i).getfunctionpointer()<<" ";
            for (unsigned j = 0; j < FunctionList.at(ProgramList.at(i).getfunctionpointer()).size(); j++)
                FunctionList.at(ProgramList.at(i).getfunctionpointer()).at(j).toString();
        }
    }
}
