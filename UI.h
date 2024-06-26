#include "tests.h"

void actionUIRect(Matrix<int> *matrix, int row, int column);
void actionUIOther(Matrix<int> *matrix, int row, int column);

void UI()
{
    std::cout << "Choose action\n";
    std::cout << "1.Run tests\n";
    std::cout << "2.Create Matrix\n";
    std::cout << "3.Exit program\n\n";
    int action;
    int exit;
    std::cin >> action;

    if (action == 2)
    {
        std::cout << "1.Create Rectangle matrix\n";
        std::cout << "2.Create Diagonal matrix\n";
        std::cout << "3.Create Triangle matrix\n";
        int choice;
        int row, column;
        std::cin >> choice;
        std::cout << "\nEnter size(row x column)\n";
        std::cin >> row >> column;
        std::cout << "\nEnter matrix\n";
        int matrix[row][column];
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                std::cin >> matrix[i][j];
            }
        }
        if (choice == 1)
        {
            Matrix<int> *Rmatrix;
            Rmatrix = new RectangleMatrix<int>(row, column, &matrix[0][0]);
            do
            {
                actionUIRect(Rmatrix, row, column);
                std::cout << "1.Do next action\n";
                std::cout << "2.Stop\n";
                std::cin >> exit;
            } while (exit == 1);
            UI();
        }
        else if (choice == 2)
        {
            Matrix<int> *Dmatrix;
            Dmatrix = new DiagonalMatrix<int>(row, row, &matrix[0][0]);
            do
            {
                actionUIOther(Dmatrix, row, row);
                std::cout << "1.Do next action\n";
                std::cout << "2.Stop\n";
                std::cin >> exit;
            } while (exit == 1);
            UI();
        }
        else if (choice == 3)
        {
            Matrix<int> *Tmatrix;
            Tmatrix = new TriangleMatrix<int>(row, row, &matrix[0][0], UPPER);
            do
            {
                actionUIOther(Tmatrix, row, row);
                std::cout << "1.Do next action\n";
                std::cout << "2.Stop\n";
                std::cin >> exit;
            } while (exit == 1);
            UI();
        }

        else
            std::cout << "incorect action";
    }
    else if (action == 1)
    {
        tests();
        UI();
    }
    else if (action == 0)
    {
        std::cout << "program finished";
    }
    else
    {
        std::cout << "incorect action";
        UI();
    }
}

void IntMatrixUI(int choice)
{
}

void actionUIRect(Matrix<int> *matrix, int row, int column)
{
    std::cout << "Choose action\n\n";
    int MatrixAction;
    std::cout << "1.Print matrix\n";
    std::cout << "2.Multiply matrix by scalar\n";
    std::cout << "3.Get element\n";
    std::cout << "4.Swap rows\n";
    std::cout << "5.Swap columns\n";
    std::cout << "6.Transpose\n";
    std::cout << "7.Add row to row\n";
    std::cout << "8.Add column to column\n";
    std::cout << "9.Set element\n\n";
    std::cin >> MatrixAction;
    switch (MatrixAction)
    {
    case 1:
        PrintMatrix(matrix, row, column);
        break;

    case 2:
        std::cout << "Enter scalar\n";
        int scalar;
        std::cin >> scalar;
        matrix->MultiplicationByScalar(scalar);
        std::cout << "\n";
        PrintMatrix(matrix, row, column);
        break;
    case 3:
        std::cout << "Enter row then column\n";
        int r, c;
        std::cin >> r >> c;
        std::cout << "\nElement: "
                  << matrix->Get(r, c) << "\n";
        break;
    case 4:
        std::cout << "Enter two rows\n";
        int row1, row2;
        std::cin >> row1 >> row2;
        matrix->SwapRows(row1, row2);
        std::cout << "\n";
        PrintMatrix(matrix, row, column);
        break;
    case 5:
        std::cout << "Enter two columns\n";
        int col1, col2;
        std::cin >> col1 >> col2;
        matrix->SwapRows(col1, col2);
        std::cout << "\n";
        PrintMatrix(matrix, row, column);
        break;
    case 6:
        std::cout << "\n";
        PrintMatrix(matrix->Transpose(), column, row);
        break;
    case 7:
        std::cout << "Enter two rows\n";
        int row3, row4;
        std::cin >> row3 >> row4;
        matrix->AddRowToRow(row3, row4);
        std::cout << "\n";
        PrintMatrix(matrix, row, column);
        break;
    case 8:
        std::cout << "Enter two columns\n";
        int col3, col4;
        std::cin >> col3 >> col4;
        ;
        matrix->AddRowToRow(col3, col4);
        std::cout << "\n";
        PrintMatrix(matrix, row, column);
        break;
    case 9:
        std::cout << "Enter index: row and column\n";
        int rowSet, colSet;
        int value;
        std::cin >> rowSet >> colSet;
        std::cout << "Enter value\n";
        std::cin >> value;
        matrix->Set(value, rowSet, colSet);
        break;
    default:
        std::cout << "incorrect action";
        break;
    }
}

void actionUIOther(Matrix<int> *matrix, int row, int column)
{
    std::cout << "Choose action\n\n";
    int MatrixAction;
    std::cout << "1.Print matrix\n";
    std::cout << "2.Multiply matrix by scalar\n";
    std::cout << "3.Get element\n";
    std::cout << "4.Set element\n\n";
    std::cin >> MatrixAction;
    switch (MatrixAction)
    {
    case 1:
        PrintMatrix(matrix, row, column);
        break;

    case 2:
        std::cout << "Enter scalar\n";
        int scalar;
        std::cin >> scalar;
        matrix->MultiplicationByScalar(scalar);
        std::cout << "\n";
        PrintMatrix(matrix, row, column);
        break;
    case 3:
        std::cout << "Enter row then column\n";
        int r, c;
        std::cin >> r >> c;
        std::cout << "\nElement: "
                  << matrix->Get(r, c) << "\n";
        break;
    case 4:
        std::cout << "Enter index: row and column\n";
        int rowSet, colSet;
        int value;
        std::cin >> rowSet >> colSet;
        std::cout << "Enter value\n";
        std::cin >> value;
        matrix->Set(value, rowSet, colSet);
        break;
    default:
        std::cout << "incorrect action";
        break;
    }
}