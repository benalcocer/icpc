/// @author Benjamin Alcocer

#include <iostream>

using namespace std;

bool valid(const int size, const int x, const int y)
{
    int total = x + y;  // since 2 rows must exist
    bool alternate = true;

    while (total < size)
    {
        if (alternate)
        {
            total += x;
        }
        else
        {
            total += y;
        }
        alternate = !alternate;
    }

    return total == size;
}

int main()
{
    int size;
    int x;

    while (cin >> size)
    {
        if (size >= 3 && size <= 1000000)
        {
            x = 2;
            cout << size << ":" << endl;

            while (x <= (size / 2) + 1)     // divide 2 then add 1
            {
                for (int y = x - 1; y <= x; y++)
                {
                    if (valid(size, x, y))
                    {
                        cout << " " << x << "," << y << endl;
                    }
                }
                x++;
            }
        }
    }

    return 0;
}
