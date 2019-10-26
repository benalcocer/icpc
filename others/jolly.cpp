/// @author Benjamin Alcocer
/// @file latinsquares.cpp
/// @version 2019-09-07
/// @brief Jolly Jumpers for UNLV ACM practice...

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool isJolly(vector<int>& vect);

int main()
{
    vector<int> numbers;    // vector holding the numbers
    int temp;               // temporary integer used to pull from input stream

    while (!cin.eof())
    {
        while (cin.peek() != '\n')
        {
            cin >> temp;
            numbers.push_back(temp);
        }
        if (!numbers.empty())
        {
            if (isJolly(numbers))
            {
                cout << "Jolly" << endl;
            }
            else
            {
                cout << "Not Jolly" << endl;
            }
            numbers.clear();
            cin >> temp;
        }
    }

    return 0;
}

/// ----------------------------------------------------------------------------
/// isJolly(): This function determines if a vector of integers is a jolly
/// jumper.
///
/// @param vect     The vector of integers containing the presumed jolly jumper
///
/// @return         Return a boolean indicating if the vector of integers is
/// a jolly jumper or not.
/// ----------------------------------------------------------------------------
bool isJolly(vector<int>& vect)
{
    vector<int> buffer;
    int tempNum;
    bool valid = true;

    // Insert numbers into vector and keep them in ascending order
    for (uint i = 0; i < vect.size() - 1; i++)
    {
        tempNum = abs(vect[i] - vect[i + 1]);
        if (buffer.empty())
        {
            buffer.push_back(tempNum);
        }
        else
        {
            uint count = 0;
            while (count < vect.size() && tempNum > buffer[count])
            {
                count++;
            }
            if (count == vect.size())
            {
                buffer.push_back(tempNum);
            }
            else
            {
                buffer.insert(buffer.begin() + count, tempNum);
            }
        }
    }

    // Would not be a jolly
    if (buffer[0] != 1 || buffer.back() >= vect.size())
    {
        valid = false;
    }

    // Starting at 2, last check for jolly
    tempNum = 2;
    for (uint i = 1; valid && i < buffer.size(); i++)
    {
        if (buffer[i] == tempNum)
        {
            tempNum++;
        }
        else if (buffer[i] != tempNum - 1)
        {
            valid = false;
        }
    }

    return valid;
}
