/*
problem 14 :
write a program to check  if the matrix is scalar or not
------------
 x 0 0
 0 x 0
 0 0 x
-----------
*/

#include <iostream>
#include "myLib.h"
#include <ctime>
#include <iomanip>
using namespace std;

int getRandomNumber(int min, int max)
{

    return rand() % max + min;
}

void printIntersectedValuesBetween2Matrices(int matrix[3][3], int l, int c, int minRandValue, int maxRandValue)
{

    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {

            matrix[i][j] = getRandomNumber(minRandValue, maxRandValue);
        }
    }
}

void printMatrix(int matrix[3][3], int l, int c)
{

    cout << "\n";
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {

            printf("%02d  ", matrix[i][j]);
        }
        cout << endl;
    }
    cout << "\n";
}

enum isScalar
{
    no,
    yes
};

isScalar checkIf2MatricesScalar(int matrix[3][3], int l, int c)
{

    int previousDiagonalValue = matrix[0][0];
    for (int i = 0; i < l; i++)
    {
        for (int j = 0; j < c; j++)
        {

            if ((i == j && matrix[i][j] != previousDiagonalValue) || (i != j && matrix[i][j] != 0))
                return isScalar::no;
                }
    }

    return isScalar::yes;
}

int main()
{
    srand(time(NULL));

    int matrix1[3][3] = {{9, 0, 0}, {0, 9, 0}, {0, 0, 9}};

    // FillMatrixWithRandomNumber(matrix1, 3, 3, 0, 9);
    cout << "matrix 1:";
    printMatrix(matrix1, 3, 3);

    cout << "matrices is " << (checkIf2MatricesScalar(matrix1, 3, 3) == isScalar::yes ? "" : "not") << " Scalar" << endl;
    return 0;
}
