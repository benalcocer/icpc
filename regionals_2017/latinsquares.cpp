/// @author Benjamin Alcocer
/// @file latinsquares.cpp
/// @version 2019-09-07
/// @brief Latin Squares for UNLV ACM practice...

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void insertInVector(vector<char>& vect, const string& str, const uint size);
bool checkRow(const string& array, const uint n);
bool checkCollumn(const vector<char>& vect, const uint n);

int main()
{
    vector<char> symbols;       // vector of chars holding the latin square
    int size;                   // the size of the row/square "n"
    bool isLatinSquare = true;  // boolean indicating if it is a latin square
    string tempStr;             // temporary string to check & copy over

    while (!cin.eof())
    {
        tempStr = "";

        // Get the size of the latin square (n)
        cin >> size;
        if (!cin.fail())
        {
            isLatinSquare = true;
        }
        else
        {
            isLatinSquare = false;
            if (!cin.eof())
            {
                cout << "Input stream failure." << endl;
                return EXIT_FAILURE;
            }
        }

        // Get a string from each row and check if row is unique
        for (int i = 0; isLatinSquare && i < size; i++)
        {
            cin >> tempStr;

            if (tempStr.size() == size && checkRow(tempStr, size))
            {
                insertInVector(symbols, tempStr, size);
            }
            else
            {
                isLatinSquare = false;
                while (i < size)
                {
                    cin.ignore(100, '\n');
                    i++;
                }
            }
        }

        // If rows were unique and collumns are unique
        if (isLatinSquare && checkCollumn(symbols, size))
        {
            bool exitLoop = false;  // exitloop bool

            // Check to see if Latin Square is reduced
            for (int i = 0; !exitLoop && i < size - 1; i++)
            {
                if (symbols[i] + 1 != symbols[i + 1] ||
                    symbols[i] + 1 != symbols[i * size + size])
                {
                    exitLoop = true;
                }
            }

            if (exitLoop)   // not reduced
            {
                cout << "Not Reduced" << endl;
            }
            else
            {
                cout << "Reduced" << endl;
            }
        }
        else if (!tempStr.empty())
        {
            cout << "No" << endl;
        }
        symbols.clear();
    }

    return EXIT_SUCCESS;
}

/// ----------------------------------------------------------------------------
/// insertInVector(): This function inserts a string into a vector.
///
/// @param vect     The vector that will take the string.
/// @param str      The string that acts as a template.
/// @param size     The size of the string.
/// ----------------------------------------------------------------------------
void insertInVector(vector<char>& vect, const string& str, const uint size)
{
    for (int i = 0; i < size; i++)
    {
        vect.push_back(str[i]);
    }
}

/// ----------------------------------------------------------------------------
/// checkRow(): This function checks the row to determine if it is a Latin
/// Square. This function not only checks for unique characters, but also
/// checks to see if the amount of unique characters is equal to n.
///
/// @param array    The string holding the current row.
/// @param n        The size of the string or n (number of symbols)
///
/// @return         Return a boolean indicating if the row has unique chars and
/// the number of unique characters = n.
/// ----------------------------------------------------------------------------
bool checkRow(const string& array, const uint n)
{
    bool isUnique = true;   // boolean indicating if row has unique chars
    vector<char> temp;      // vector holding temporary unique characters

    for (int count = 0; isUnique && count < n - 1; count++)
    {
        if (temp.empty())   // If vector is empty, simply add to vector
        {
            temp.push_back(array[count]);
        }
        else
        {
            // Check if character in question is unique to vector
            for (int check = 0; isUnique && check < temp.size(); check++)
            {
                if (temp[check] == array[count])
                {
                    isUnique = false;
                }
            }

            // If char is unique AND adding a char will not make vectsize > n
            if (isUnique && temp.size() < n)
            {
                temp.push_back(array[count]);
            }
            else
            {
                isUnique = false;
            }
        }
    }

    return isUnique;
}

/// ----------------------------------------------------------------------------
/// checkCollumn(): This function checks the collumn to determine if it is a
/// Latin Square.
/// ----------------------------------------------------------------------------
bool checkCollumn(const vector<char>& vect, const uint n)
{
    bool isUnique = true;   // boolean indicating if collumn has unique chars
    int maxSize = n * n;   // maximum size of the latin square
    char temp;              // character holding temporary unique symbol

    if (vect.empty())
    {
        return false;
    }

    // For each collumn
    for (int collumn = 0; isUnique && collumn < n; collumn++)
    {
        temp = vect[collumn];

        // Run n - 1 times for each level of checks
        for (int i = 1; i < n; i++)
        {
            // for loop arithmetic goes down each collumn but not past maxSize
            for (int j = (n * i) + collumn; isUnique && j < maxSize; j += n)
            {
                if (temp == vect[j])
                {
                    isUnique = false;
                }
            }
            // store the next char that will be checked against subsequent chars
            temp = vect[(n * i) + collumn];
        }
    }

    return isUnique;
}
