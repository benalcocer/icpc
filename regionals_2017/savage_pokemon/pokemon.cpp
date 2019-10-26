/// @author Benjamin Alcocer

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void inputUnique(vector<int>& count, int input)
{
    if (count.empty())
    {
        count.push_back(input);
        return;
    }

    for (uint i = 0; i < count.size(); i++)
    {
        if (count[i] == input)
        {
            return;
        }
        else if (count[i] > input)
        {
            count.insert(count.begin() + i, input);
            return;
        }
    }
    count.push_back(input);
}

int main()
{
    const string FILE_NAME = "test2.txt";   // the name of the input file
    ifstream inputFile;                     // input file variable
    int n;
    int r;
    vector<int> leftSection;
    vector<int> rightSection;
    int parks;
    int temp[2];

    inputFile.open(FILE_NAME);
    if (!inputFile.is_open())
    {
        cerr << "File \"" << FILE_NAME << "\" could not be opened." << endl;
        return EXIT_FAILURE;
    }

    inputFile >> parks;
    while (!inputFile.eof() && parks > 0)
    {
        bool valid = true;  // if valid is true, then able to get to destination
        inputFile >> n;
        inputFile >> r;

        // Easy exit and extra newline is ignored
        if (inputFile.fail() && inputFile.eof())
        {
            inputFile.close();
            return EXIT_SUCCESS;
        }

        // Gather input N and R
        // MUST FOLLOW:
        // Y < N
        // X >= 0
        // X != Y
        for (int i = 0; valid && i < r; i++)
        {
            inputFile >> temp[0];
            inputFile >> temp[1];
            if (temp[1] < n && temp[0] >= 0 && temp[0] != temp[1])
            {
                leftSection.push_back(temp[0]);
                rightSection.push_back(temp[1]);
            }
            else
            {
                valid = false;
            }
        }

        // logic for "No sections connect to themselves, nor will there be
        // duplicate connection entries. Each section will have at least one
        // other section that connects to it, or that it connects to."
        vector<int> count;
        for (int i = 0; valid && i < r; i++)
        {
            for (int j = 0; valid && j < r; j++)
            {
                // First if: X1 -> Y1 == X2 -> Y2
                // Second if: test cross X1 == Y2, so if X2 == Y1 then false
                if (i != j && leftSection[i] == leftSection[j] &&
                    rightSection[i] == rightSection[j])
                {
                    valid = false;
                }
                else if (leftSection[i] == rightSection[j])
                {
                    inputUnique(count, leftSection[i]);

                    if (leftSection[j] == rightSection[i])
                    {
                        valid = false;
                    }
                }
            }
        }

        if (valid && count.size() == n)
        {
            cout << "Gotta Catch Them All!" << endl;
        }
        else
        {
            cout << "Oh, oh!" << endl;
        }

        leftSection.clear();
        rightSection.clear();
        count.clear();
        parks--;
    }

    inputFile.close();
    return EXIT_SUCCESS;
}
