#include <iostream>
#include <algorithm>
#include <iterator>
#include <array>
#include <fstream>
#include <stdlib.h>

using namespace std;
void reverseArray(int arr[], int n)  // used to reverse array later after copying
{
    for (int low = 0, high = n - 1; low < high; low++, high--)
    {
        swap(arr[low], arr[high]);
    }
}
int main()
{
    const long int max_gen = 1000, dim = (max_gen * 2 + 1);
    int *cellular1 = new int[dim]{0};  // memory allocation
    int *cellular2 = new int[dim]{0};
    int *blank = new int[dim]{0};

    cellular1[max_gen] = 1;

    int x = 1, y = 0, bias = 1;
    int middle_data[max_gen] = {0};

    middle_data[0] = 1;

    while (x < max_gen * 2)
    {
        int a = cellular1[x - 1];
        int b = cellular1[x];
        int c = cellular1[x + 1];
        // cout << a << b << c;
        if (a == 1 && b == 0 && c == 0)
        { // apply rules
            cellular2[x] = 1;
        }
        else if (a == 0 && b == 1 && c == 1)
        {
            cellular2[x] = 1;
        }
        else if (a == 0 && b == 1 && c == 0)
        {
            cellular2[x] = 1;
        }
        else if (a == 0 && b == 0 && c == 1)
        {
            cellular2[x] = 1;
        }
        if (bias == max_gen * 2 - 1)
        { // switch to next row
            x = 1;
            bias = 1;
            y += 1;
            middle_data[y] = cellular2[max_gen];
            int i;
            for (i = 0; i < dim; i++)
            {
                cellular1[i] = cellular2[dim - i - 1];
            }
            for (i = 0; i < dim; i++)
            {
                cellular2[i] = blank[dim - i - 1];
            }
            reverseArray(cellular1, dim);
            reverseArray(cellular2, dim);
        }

        if (y == max_gen - 1)
        { // end at last row
            break;
        }
        else
        { // go to next column
            x += 1;
            bias += 1;
        }
    }
    int i, j;
    ofstream outfile;
    outfile.open("result.csv"); // add custom path if you want to
    for (i = 0; i < max_gen; i++)
    {
        outfile << middle_data[i] << ",";
    }
    outfile.close();
    cout << "Done. ";
    system("pause");  // keep console open
}
