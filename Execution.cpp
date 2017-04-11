#include "Execution.h"
#include "Parser.h"

using namespace std;

void executionLoop(int currentNumber, vector<rational> &ProgramList, vector< vector<rational> > &FunctionList)
{
    //Runs the program
    bool found = true;
    bool jump = false;
    unsigned j = 0;
    vector<int> historyOfNumbers;
    historyOfNumbers.push_back(currentNumber);
    while(found)
    {
        cout<<currentNumber<<endl;
        jump = false;
        found = false;
        for (; j < ProgramList.size(); j++)
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
}
