#include <iostream>
#include <bits/stdc++.h>
template <class T>
class RectangleMatrix
{
private:
    int rows;
    int columns;
    T **elements;

public:
    RectangleMatrix();
    RectangleMatrix(int rows, int columns);
    RectangleMatrix(int rows, int columns, T *elements);

    void Addition(RectangleMatrix<T> *matrix);
    void MultiplicationByScalar(T scalar);
    T *MatrixNorm();
    T Get(int row, int column);

    void SwapRows(int row_1, int row_2);
    void SwapColumns(int col_1, int col_2);
    void MultiplicationRowByNum(int row, T num);
    void MultiplicationColumnByNum(int column, T num);
    void AddRowToRow(int row_1, int row_2);
    void AddColumnToColumn(int column_1, int column_2);
    RectangleMatrix<T> *Transpose();
};

template <class T>
T RectangleMatrix<T>::Get(int row, int column)
{
    if ((row < 0) || (row >= this->rows) || (column < 0) || (column >= this->columns))
        throw std::out_of_range("index is out of range");
    return this->elements[row][column];
}

template <class T>
RectangleMatrix<T>::RectangleMatrix()
{
    rows = 0;
    columns = 0;
    elements = nullptr;
}

template <class T>
RectangleMatrix<T>::RectangleMatrix(int rows, int columns)
{
    elements = new T *[rows];
    for (int i = 0; i < rows; i++)
    {
        elements[i] = new T[columns];
    }
    this->rows = rows;
    this->columns = columns;
}

template <class T>
RectangleMatrix<T>::RectangleMatrix(int rows, int columns, T *elements)
{
    int pos = 0;
    this->elements = new T *[rows];
    for (int i = 0; i < rows; i++)
    {
        this->elements[i] = new T[columns];
        for (int j = 0; j < columns; j++)
        {
            this->elements[i][j] = elements[pos];
            pos++;
        }
    }
    this->rows = rows;
    this->columns = columns;
}

template <class T>
void RectangleMatrix<T>::Addition(RectangleMatrix<T> *matrix)
{
    if (this->rows != matrix->rows || this->columns != matrix->columns)
    {
        throw std::logic_error("matrices have different sizes");
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            this->elements[i][j] += matrix->elements[i][j];
        }
    }
}

template <class T>
void RectangleMatrix<T>::MultiplicationByScalar(T scalar)
{
    if (scalar == 0)
    {
        throw std::logic_error("matrix can't be multiplied by zero scalar");
    }
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            this->elements[i][j] *= scalar;
        }
    }
}

template <class T>
T *RectangleMatrix<T>::MatrixNorm()
{
    T *Norms = new T[3];
    T *rowsSum = new T[this->rows];
    T *columnsSum = new T[this->columns];
    T tmp;
    for (int i = 0; i < this->rows; i++)
    {
        tmp = this->elements[i][0];
        for (int j = 1; j < this->columns; j++)
        {
            tmp += this->elements[i][j];
        }
        rowsSum[i] = tmp;
    }

    for (int i = 0; i < this->columns; i++)
    {
        tmp = this->elements[0][i];
        for (int j = 1; j < this->rows; j++)
        {
            tmp += this->elements[j][i];
        }
        columnsSum[i] = tmp;
    }

    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            if (i == 0 && j == 0)
            {
                tmp = (this->elements[0][0] * this->elements[0][0]);
            }
            else
            {
                tmp += (this->elements[i][j] * this->elements[i][j]);
            }
        }
    }
    Norms[0] = *std::max_element(rowsSum, rowsSum + this->rows);
    Norms[1] = *std::max_element(columnsSum, columnsSum + this->columns);
    Norms[2] = sqrt(tmp);

    return Norms;
}

template <class T>
void RectangleMatrix<T>::SwapRows(int row_1, int row_2)
{
    row_1--;
    row_2--;
    for (int i = 0; i < this->columns; i++)
    {
        T temp = this->elements[row_1][i];
        this->elements[row_1][i] = this->elements[row_2][i];
        this->elements[row_2][i] = temp;
    }
}

template <class T>
void RectangleMatrix<T>::SwapColumns(int col_1, int col_2)
{
    col_1--;
    col_2--;
    for (int i = 0; i < this->rows; i++)
    {
        T temp = this->elements[i][col_1];
        this->elements[i][col_1] = this->elements[i][col_2];
        this->elements[i][col_2] = temp;
    }
}

template <class T>
void RectangleMatrix<T>::MultiplicationRowByNum(int row, T num)
{
    row--;
    for (int i = 0; i < this->columns; i++)
    {
        this->elements[row][i] *= num;
    }
}

template <class T>
void RectangleMatrix<T>::MultiplicationColumnByNum(int column, T num)
{
    column--;
    for (int i = 0; i < this->rows; i++)
    {
        this->elements[i][column] *= num;
    }
}

template <class T>
void RectangleMatrix<T>::AddRowToRow(int row_1, int row_2)
{
    row_1--;
    row_2--;
    for (int i = 0; i < this->columns; i++)
    {
        this->elements[row_1][i] += this->elements[row_2][i];
    }
}

template <class T>
void RectangleMatrix<T>::AddColumnToColumn(int column_1, int column_2)
{
    column_1--;
    column_2--;
    for (int i = 0; i < this->rows; i++)
    {
        this->elements[i][column_1] += this->elements[i][column_2];
    }
}

template <class T>
RectangleMatrix<T> *RectangleMatrix<T>::Transpose()
{
    RectangleMatrix<T> *TransposeMatrix = new RectangleMatrix<T>(this->columns, this->rows);
    for (int i = 0; i < this->rows; i++)
    {
        for (int j = 0; j < this->columns; j++)
        {
            TransposeMatrix->elements[j][i] = this->elements[i][j];
        }
    }
    return TransposeMatrix;
}