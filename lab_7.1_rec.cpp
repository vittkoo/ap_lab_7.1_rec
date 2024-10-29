#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** r, const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0);
void Print(int** r, const int rowCount, const int colCount, int i = 0, int j = 0);
void Sort(int** r, const int rowCount, const int colCount, int i0 = 0, int i1 = 0);
void Change(int** r, const int row1, const int row2, const int colCount);
void Calc(int** r, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0);

int main()
{
    srand((unsigned)time(NULL));

    const int Low = 4;
    const int High = 51;

    const int rowCount = 8;
    const int colCount = 5;

    int** r = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        r[i] = new int[colCount];

    Create(r, rowCount, colCount, Low, High);
    cout << "Start matrix:" << endl;
    cout << endl;
    Print(r, rowCount, colCount);
    Sort(r, rowCount, colCount);
    cout << endl;
    cout << "Sorted matrix:" << endl;
    cout << endl;
    Print(r, rowCount, colCount);

    int S = 0;
    int k = 0;
    Calc(r, rowCount, colCount, S, k);
    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << endl;
    cout << "Modified matrix:" << endl;
    Print(r, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] r[i];
    delete[] r;

    return 0;
}

void Create(int** r, const int rowCount, const int colCount, const int Low, const int High, int i, int j)
{
    if (i >= rowCount) return;
    r[i][j] = Low + rand() % (High - Low + 1);
    if (j < colCount - 1)
        Create(r, rowCount, colCount, Low, High, i, j + 1);
    else
        Create(r, rowCount, colCount, Low, High, i + 1, 0);
}

void Print(int** r, const int rowCount, const int colCount, int i, int j)
{
    if (i >= rowCount) return;
    cout << setw(4) << r[i][j];
    if (j < colCount - 1)
        Print(r, rowCount, colCount, i, j + 1);
    else
    {
        cout << endl;
        Print(r, rowCount, colCount, i + 1, 0);
    }
}

void Sort(int** r, const int rowCount, const int colCount, int i0, int i1)
{
    if (i0 >= rowCount - 1) return;

    if (i1 < rowCount - i0 - 1)
    {
        if ((r[i1][0] > r[i1 + 1][0]) ||
            (r[i1][0] == r[i1 + 1][0] && r[i1][1] < r[i1 + 1][1]) ||
            (r[i1][0] == r[i1 + 1][0] && r[i1][1] == r[i1 + 1][1] && r[i1][2] < r[i1 + 1][2]))
        {
            Change(r, i1, i1 + 1, colCount);
        }
        Sort(r, rowCount, colCount, i0, i1 + 1);
    }
    else
    {
        Sort(r, rowCount, colCount, i0 + 1, 0);
    }
}

void Change(int** r, const int row1, const int row2, const int colCount)
{
    int tmp;
    for (int j = 0; j < colCount; j++)
    {
        tmp = r[row1][j];
        r[row1][j] = r[row2][j];
        r[row2][j] = tmp;
    }
}

void Calc(int** r, const int rowCount, const int colCount, int& S, int& k, int i, int j)
{
    if (i >= rowCount) return;

    if (!(r[i][j] % 2 == 0) && !(i % 3 == 0 && j % 3 == 0))
    {
        S += r[i][j];
        k++;
        r[i][j] = 0;
    }

    if (j < colCount - 1)
        Calc(r, rowCount, colCount, S, k, i, j + 1);
    else
        Calc(r, rowCount, colCount, S, k, i + 1, 0);
}
