#include <iostream>
#include <bits/stdc++.h>
#include "ArraySequence.h"
template <class T>
class RectangleMatrix
{
private:
    int rows;
    int columns;
    Sequence<T> *elements;

public:
    RectangleMatrix();
    RectangleMatrix(int rows, int columns);
    RectangleMatrix(int rows, int columns, T *elements);

    void Addition(RectangleMatrix<T> *matrix);
    void MultiplicationByScalar(const T &scalar);
    void Set(T value, int row, int column);

    T *MatrixNorm();
    T Get(int row, int column);
    int GetRowSize();
    int GetColumnSize();

    void SwapRows(int row_1, int row_2);
    void SwapColumns(int col_1, int col_2);
    void MultiplicationRowByNum(int row, T num);
    void MultiplicationColumnByNum(int column, T num);
    void AddRowToRow(int row_1, int row_2);
    void AddColumnToColumn(int column_1, int column_2);
    RectangleMatrix<T> *Transpose();
};

template <class T>
RectangleMatrix<T>::RectangleMatrix()
{
    rows = 0;
    columns = 0;
    elements = new ArraySequence<T>;
}

template <class T>
RectangleMatrix<T>::RectangleMatrix(int rows, int columns)
{
    elements = new ArraySequence<T>(rows * columns);
    this->rows = rows;
    this->columns = columns;
}

template <class T>
RectangleMatrix<T>::RectangleMatrix(int rows, int columns, T *elements)
{
    this->rows = rows;
    this->columns = columns;
    this->elements = new ArraySequence<T>(elements, rows * columns);
}

template <class T>
void RectangleMatrix<T>::Set(T value, int row, int column)
{
    this->elements->InsertAt(value, columns * row + column);
}

template <class T>
T RectangleMatrix<T>::Get(int row, int column)
{
    if ((row < 0) || (row >= this->rows) || (column < 0) || (column >= this->columns))
        throw std::out_of_range("index is out of range");
    return this->elements->Get(columns * row + column);
}

template <class T>
int RectangleMatrix<T>::GetRowSize()
{
    return this->rows;
}

template <class T>
int RectangleMatrix<T>::GetColumnSize()
{
    return this->columns;
}

template <class T>
void RectangleMatrix<T>::Addition(RectangleMatrix<T> *matrix)
{
    if (this->rows != matrix->rows || this->columns != matrix->columns)
    {
        throw std::logic_error("matrices have different sizes");
    }
    for (int i = 0; i < rows * columns; i++)
    {
        this->elements->InsertAt(this->elements->Get(i) + matrix->elements->Get(i), i);
    }
}

template <class T>
void RectangleMatrix<T>::MultiplicationByScalar(const T &scalar)
{
    if (scalar == 0)
    {
        throw std::logic_error("matrix can't be multiplied by zero scalar");
    }
    for (int i = 0; i < rows * columns; i++)
    {
        this->elements->InsertAt(this->elements->Get(i) * scalar, i);
    }
}

template <class T>
T *RectangleMatrix<T>::MatrixNorm()
{
    T *Norms = new T[3];
    T *rowsSum = new T[rows];
    T *columnsSum = new T[columns];
    T tmp;
    for (int i = 0; i < rows; i++)
    {
        tmp = this->elements->Get(columns * i);
        for (int j = 1; j < columns; j++)
        {
            tmp += this->elements->Get(columns * i + j);
        }
        rowsSum[i] = tmp;
    }

    for (int i = 0; i < columns; i++)
    {
        tmp = this->elements->Get(i);
        for (int j = 1; j < rows; j++)
        {
            tmp += this->elements->Get(columns * j + i);
        }
        columnsSum[i] = tmp;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (i == 0 && j == 0)
            {
                tmp = (this->elements->Get(0) * this->elements->Get(0));
            }
            else
            {
                tmp += (this->elements->Get(columns * i + j) * this->elements->Get(columns * i + j));
            }
        }
    }
    Norms[0] = *std::max_element(rowsSum, rowsSum + rows);
    Norms[1] = *std::max_element(columnsSum, columnsSum + columns);
    Norms[2] = sqrt(tmp);
    delete[] rowsSum;
    delete[] columnsSum;
    return Norms;
}

template <class T>
void RectangleMatrix<T>::SwapRows(int row_1, int row_2)
{
    if (row_1 < 0 || row_2 < 0 || row_1 > rows || row_2 > rows)
        throw std::out_of_range("rows are out of range");
    T tmp;
    for (int i = 0; i < columns; i++)
    {
        tmp = this->elements->Get(columns * row_1 + i);
        this->elements->InsertAt(this->elements->Get(columns * row_2 + i), columns * row_1 + i);
        this->elements->InsertAt(tmp, columns * row_2 + i);
    }
}

template <class T>
void RectangleMatrix<T>::SwapColumns(int col_1, int col_2)
{
    if (col_1 < 0 || col_2 < 0 || col_1 > columns || col_2 > columns)
        throw std::out_of_range("columns are out of range");
    T tmp;
    for (int i = 0; i < rows; i++)
    {
        tmp = this->elements->Get(columns * i + col_1);
        this->elements->InsertAt(this->elements->Get(columns * i + col_2), columns * i + col_1);
        this->elements->InsertAt(tmp, columns * i + col_2);
    }
}

template <class T>
void RectangleMatrix<T>::MultiplicationRowByNum(int row, T num)
{
    for (int i = 0; i < columns; i++)
    {
        this->elements->InsertAt(this->elements->Get(columns * row + i) * num, columns * row + i);
    }
}

template <class T>
void RectangleMatrix<T>::MultiplicationColumnByNum(int column, T num)
{
    for (int i = 0; i < rows; i++)
    {
        this->elements->InsertAt(this->elements->Get(columns * i + column) * num, columns * i + column);
    }
}

template <class T>
void RectangleMatrix<T>::AddRowToRow(int row_1, int row_2)
{
    if (row_1 < 0 || row_2 < 0 || row_1 > rows || row_2 > rows)
        throw std::out_of_range("rows are out of range");
    for (int i = 0; i < columns; i++)
    {
        this->elements->InsertAt(this->elements->Get(columns * row_1 + i) + this->elements->Get(columns * row_2 + i), columns * row_1 + i);
    }
}

template <class T>
void RectangleMatrix<T>::AddColumnToColumn(int col_1, int col_2)
{
    if (col_1 < 0 || col_2 < 0 || col_1 > columns || col_2 > columns)
        throw std::out_of_range("columns are out of range");
    for (int i = 0; i < rows; i++)
    {
        this->elements->InsertAt(this->elements->Get(columns * i + col_1) + this->elements->Get(columns * i + col_2), columns * i + col_1);
    }
}

template <class T>
RectangleMatrix<T> *RectangleMatrix<T>::Transpose()
{
    RectangleMatrix<T> *TransposeMatrix = new RectangleMatrix<T>(columns, rows);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            TransposeMatrix->elements->InsertAt(this->elements->Get(columns * i + j), columns * j + i);
        }
    }
    return TransposeMatrix;
}
