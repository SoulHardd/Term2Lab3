#include <iostream>
#include "UnifiedMatrices.h"
#include "Matrix.h"
using namespace std;

typedef enum
{
    SUCCESS,
    FAILURE
} result;

template <class T>
result CheckMatrix(Matrix<T> *matrix_1, T *matrixForCheck, int row, int column)
{
    int pos = 0;
    T **matrix_2;
    matrix_2 = new T *[row];
    for (int i = 0; i < row; i++)
    {
        matrix_2[i] = new T[column];
        for (int j = 0; j < column; j++)
        {
            matrix_2[i][j] = matrixForCheck[pos];
            pos++;
        }
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (matrix_1->Get(i, j) != matrix_2[i][j])
                return FAILURE;
        }
    }
    return SUCCESS;
}

template <class T>
void PrintMatrix(Matrix<T> *matrix, int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cout << left << setw(5);
            cout << matrix->Get(i, j);
        }
        cout << "\n";
    }
}

template <class T>
void PrintArray(T *matrix, int row, int column)
{
    int pos = 0;
    T **matrix_;
    matrix_ = new T *[row];
    for (int i = 0; i < row; i++)
    {
        matrix_[i] = new T[column];
        for (int j = 0; j < column; j++)
        {
            matrix_[i][j] = matrix[pos];
            pos++;
        }
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            cout << left << setw(5);
            cout << matrix_[i][j];
        }
        cout << "\n";
    }
}

void tests()
{
    int SqrMatrixData[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 4, 5, 6}, {2, 6, 5, 4}};
    int RectMatrixData[2][3] = {{1, 4, 5}, {5, 6, 4}};
    double DiaMatrixData[3][3] = {{1.2, 0, 0}, {0, 3.4, 0}, {0, 0, 5.6}};
    int TriaMatrixData[5][5] = {{1, 2, 3, 4, 5}, {0, 6, 7, 8, 9}, {0, 0, 10, 11, 12}, {0, 0, 0, 13, 14}, {0, 0, 0, 0, 15}};

    Matrix<int> *SqrMatrix;
    Matrix<int> *RectMatrix;
    Matrix<double> *DiaMatrix;
    Matrix<int> *TriaMatrix;

    SqrMatrix = new UnifiedRectangleMatrix<int>(4, 4, &SqrMatrixData[0][0]);
    RectMatrix = new UnifiedRectangleMatrix<int>(2, 3, &RectMatrixData[0][0]);
    DiaMatrix = new UnifiedRectangleMatrix<double>(3, 3, &DiaMatrixData[0][0]);
    TriaMatrix = new UnifiedRectangleMatrix<int>(5, 5, &TriaMatrixData[0][0]);

    // Addition test
    cout << "Addition test\n\n";
    cout << "Square Matrix:\n";
    SqrMatrix->Addition(SqrMatrix);
    int CorrectSqrMatrixData1[4][4] = {{2, 4, 6, 8}, {10, 12, 14, 16}, {18, 8, 10, 12}, {4, 12, 10, 8}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectSqrMatrixData1[0][0], 4, 4);
    cout << "\nActual:\n";
    PrintMatrix(SqrMatrix, 4, 4);
    if (CheckMatrix(SqrMatrix, &CorrectSqrMatrixData1[0][0], 4, 4) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Rectangle Matrix:\n";
    RectMatrix->Addition(RectMatrix);
    int CorrectRectMatrixData1[2][3] = {{2, 8, 10}, {10, 12, 8}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectRectMatrixData1[0][0], 2, 3);
    cout << "\nActual:\n";
    PrintMatrix(RectMatrix, 2, 3);
    if (CheckMatrix(RectMatrix, &CorrectRectMatrixData1[0][0], 2, 3) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Diagonal Matrix:\n";
    DiaMatrix->Addition(DiaMatrix);
    double CorrectDiaMatrixData1[3][3] = {{2.4, 0, 0}, {0, 6.8, 0}, {0, 0, 11.2}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectDiaMatrixData1[0][0], 3, 3);
    cout << "\nActual:\n";
    PrintMatrix(DiaMatrix, 3, 3);
    if (CheckMatrix(DiaMatrix, &CorrectDiaMatrixData1[0][0], 3, 3) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Triangle Matrix:\n";
    TriaMatrix->Addition(TriaMatrix);
    int CorrectTriaMatrixData1[5][5] = {{2, 4, 6, 8, 10}, {0, 12, 14, 16, 18}, {0, 0, 20, 22, 24}, {0, 0, 0, 26, 28}, {0, 0, 0, 0, 30}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectTriaMatrixData1[0][0], 5, 5);
    cout << "\nActual:\n";
    PrintMatrix(TriaMatrix, 5, 5);
    if (CheckMatrix(TriaMatrix, &CorrectTriaMatrixData1[0][0], 5, 5) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";
    // MultiplicationByScalar test

    cout << "MultiplicationByScalar test\n\n";
    cout << "Square Matrix:\n";
    SqrMatrix->MultiplicationByScalar(2);
    int CorrectSqrMatrixData2[4][4] = {{4, 8, 12, 16}, {20, 24, 28, 32}, {36, 16, 20, 24}, {8, 24, 20, 16}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectSqrMatrixData2[0][0], 4, 4);
    cout << "\nActual:\n";
    PrintMatrix(SqrMatrix, 4, 4);
    if (CheckMatrix(SqrMatrix, &CorrectSqrMatrixData2[0][0], 4, 4) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Rectangle Matrix:\n";
    RectMatrix->MultiplicationByScalar(10);
    int CorrectRectMatrixData2[2][3] = {{20, 80, 100}, {100, 120, 80}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectRectMatrixData2[0][0], 2, 3);
    cout << "\nActual:\n";
    PrintMatrix(RectMatrix, 2, 3);
    if (CheckMatrix(RectMatrix, &CorrectRectMatrixData2[0][0], 2, 3) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Diagonal Matrix:\n";
    DiaMatrix->MultiplicationByScalar(1);
    double CorrectDiaMatrixData2[3][3] = {{2.4, 0, 0}, {0, 6.8, 0}, {0, 0, 11.2}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectDiaMatrixData2[0][0], 3, 3);
    cout << "\nActual:\n";
    PrintMatrix(DiaMatrix, 3, 3);
    if (CheckMatrix(DiaMatrix, &CorrectDiaMatrixData2[0][0], 3, 3) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Triangle Matrix:\n";
    TriaMatrix->MultiplicationByScalar(-1);
    int CorrectTriaMatrixData2[5][5] = {{-2, -4, -6, -8, -10}, {0, -12, -14, -16, -18}, {0, 0, -20, -22, -24}, {0, 0, 0, -26, -28}, {0, 0, 0, 0, -30}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectTriaMatrixData2[0][0], 5, 5);
    cout << "\nActual:\n";
    PrintMatrix(TriaMatrix, 5, 5);
    if (CheckMatrix(TriaMatrix, &CorrectTriaMatrixData2[0][0], 5, 5) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    // SwapRows test

    cout << "Swap rows test\n\n";
    cout << "Square Matrix:\n";
    SqrMatrix->SwapRows(1, 3);
    int CorrectSqrMatrixData3[4][4] = {{36, 16, 20, 24}, {20, 24, 28, 32}, {4, 8, 12, 16}, {8, 24, 20, 16}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectSqrMatrixData3[0][0], 4, 4);
    cout << "\nActual:\n";
    PrintMatrix(SqrMatrix, 4, 4);
    if (CheckMatrix(SqrMatrix, &CorrectSqrMatrixData3[0][0], 4, 4) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Rectangle Matrix:\n";
    RectMatrix->SwapRows(1, 2);
    int CorrectRectMatrixData3[2][3] = {{100, 120, 80}, {20, 80, 100}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectRectMatrixData3[0][0], 2, 3);
    cout << "\nActual:\n";
    PrintMatrix(RectMatrix, 2, 3);
    if (CheckMatrix(RectMatrix, &CorrectRectMatrixData3[0][0], 2, 3) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    // SwapColumns test

    cout << "Swap columns test\n\n";
    cout << "Square Matrix:\n";
    SqrMatrix->SwapColumns(2, 4);
    int CorrectSqrMatrixData4[4][4] = {{36, 24, 20, 16}, {20, 32, 28, 24}, {4, 16, 12, 8}, {8, 16, 20, 24}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectSqrMatrixData4[0][0], 4, 4);
    cout << "\nActual:\n";
    PrintMatrix(SqrMatrix, 4, 4);
    if (CheckMatrix(SqrMatrix, &CorrectSqrMatrixData4[0][0], 4, 4) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Rectangle Matrix:\n";
    RectMatrix->SwapColumns(1, 3);
    int CorrectRectMatrixData4[2][3] = {{80, 120, 100}, {100, 80, 20}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectRectMatrixData4[0][0], 2, 3);
    cout << "\nActual:\n";
    PrintMatrix(RectMatrix, 2, 3);
    if (CheckMatrix(RectMatrix, &CorrectRectMatrixData4[0][0], 2, 3) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    // MultiplicationRowByNum test

    cout << "Multiplication row by num test\n\n";
    cout << "Square Matrix:\n";
    SqrMatrix->MultiplicationRowByNum(2, 3);
    int CorrectSqrMatrixData5[4][4] = {{36, 24, 20, 16}, {60, 96, 84, 72}, {4, 16, 12, 8}, {8, 16, 20, 24}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectSqrMatrixData5[0][0], 4, 4);
    cout << "\nActual:\n";
    PrintMatrix(SqrMatrix, 4, 4);
    if (CheckMatrix(SqrMatrix, &CorrectSqrMatrixData5[0][0], 4, 4) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Rectangle Matrix:\n";
    RectMatrix->MultiplicationRowByNum(1, 1);
    int CorrectRectMatrixData5[2][3] = {{80, 120, 100}, {100, 80, 20}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectRectMatrixData5[0][0], 2, 3);
    cout << "\nActual:\n";
    PrintMatrix(RectMatrix, 2, 3);
    if (CheckMatrix(RectMatrix, &CorrectRectMatrixData5[0][0], 2, 3) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    // MultiplicationColumnByNum test

    cout << "Multiplication column by num test\n\n";
    cout << "Square Matrix:\n";
    SqrMatrix->MultiplicationColumnByNum(2, 10);
    int CorrectSqrMatrixData6[4][4] = {{36, 240, 20, 16}, {60, 960, 84, 72}, {4, 160, 12, 8}, {8, 160, 20, 24}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectSqrMatrixData6[0][0], 4, 4);
    cout << "\nActual:\n";
    PrintMatrix(SqrMatrix, 4, 4);
    if (CheckMatrix(SqrMatrix, &CorrectSqrMatrixData6[0][0], 4, 4) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Rectangle Matrix:\n";
    RectMatrix->MultiplicationColumnByNum(3, 24);
    int CorrectRectMatrixData6[2][3] = {{80, 120, 2400}, {100, 80, 480}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectRectMatrixData6[0][0], 2, 3);
    cout << "\nActual:\n";
    PrintMatrix(RectMatrix, 2, 3);
    if (CheckMatrix(RectMatrix, &CorrectRectMatrixData6[0][0], 2, 3) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    // AddRowToRow test

    cout << "Add row to row test\n\n";
    cout << "Square Matrix:\n";
    SqrMatrix->AddRowToRow(1, 3);
    int CorrectSqrMatrixData7[4][4] = {{40, 400, 32, 24}, {60, 960, 84, 72}, {4, 160, 12, 8}, {8, 160, 20, 24}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectSqrMatrixData7[0][0], 4, 4);
    cout << "\nActual:\n";
    PrintMatrix(SqrMatrix, 4, 4);
    if (CheckMatrix(SqrMatrix, &CorrectSqrMatrixData7[0][0], 4, 4) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Rectangle Matrix:\n";
    RectMatrix->AddRowToRow(2, 1);
    int CorrectRectMatrixData7[2][3] = {{80, 120, 2400}, {180, 200, 2880}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectRectMatrixData7[0][0], 2, 3);
    cout << "\nActual:\n";
    PrintMatrix(RectMatrix, 2, 3);
    if (CheckMatrix(RectMatrix, &CorrectRectMatrixData7[0][0], 2, 3) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    // AddColumnToColumn test

    cout << "Add column to column test\n\n";
    cout << "Square Matrix:\n";
    SqrMatrix->AddColumnToColumn(1, 4);
    int CorrectSqrMatrixData8[4][4] = {{64, 400, 32, 24}, {132, 960, 84, 72}, {12, 160, 12, 8}, {32, 160, 20, 24}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectSqrMatrixData8[0][0], 4, 4);
    cout << "\nActual:\n";
    PrintMatrix(SqrMatrix, 4, 4);
    if (CheckMatrix(SqrMatrix, &CorrectSqrMatrixData8[0][0], 4, 4) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Rectangle Matrix:\n";
    RectMatrix->AddColumnToColumn(3, 2);
    int CorrectRectMatrixData8[2][3] = {{80, 120, 2520}, {180, 200, 3080}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectRectMatrixData8[0][0], 2, 3);
    cout << "\nActual:\n";
    PrintMatrix(RectMatrix, 2, 3);
    if (CheckMatrix(RectMatrix, &CorrectRectMatrixData8[0][0], 2, 3) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    // Transpose test

    cout << "Transpose test\n\n";
    cout << "Square Matrix:\n";
    Matrix<int> *TransposedSqrMatrix = new UnifiedRectangleMatrix<int>;
    TransposedSqrMatrix = SqrMatrix->Transpose();
    int CorrectSqrMatrixData9[4][4] = {{64, 132, 12, 32}, {400, 960, 160, 160}, {32, 84, 12, 20}, {24, 72, 8, 24}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectSqrMatrixData9[0][0], 4, 4);
    cout << "\nActual:\n";
    PrintMatrix(TransposedSqrMatrix, 4, 4);
    if (CheckMatrix(TransposedSqrMatrix, &CorrectSqrMatrixData9[0][0], 4, 4) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";

    cout << "Rectangle Matrix:\n";
    Matrix<int> *TransposedRectMatrix = new UnifiedRectangleMatrix<int>;
    TransposedRectMatrix = RectMatrix->Transpose();
    int CorrectRectMatrixData9[3][2] = {{80, 180}, {120, 200}, {2520, 3080}};
    cout << "\nExpexted:\n";
    PrintArray(&CorrectRectMatrixData9[0][0], 3, 2);
    cout << "\nActual:\n";
    PrintMatrix(TransposedRectMatrix, 3, 2);
    if (CheckMatrix(TransposedRectMatrix, &CorrectRectMatrixData9[0][0], 3, 2) == FAILURE)
        cout << "failure\n\n";
    else
        cout << "success\n\n";
}