#include <iostream>
#include <bits/stdc++.h>
#include "ArraySequence.h"
#include "Matrix.h"

template <class T>
class RectangleMatrix : public Matrix<T>
{
private:
    int rows;
    int columns;
    Sequence<T> *elements;

public:
    RectangleMatrix();
    RectangleMatrix(const int &rows, const int &columns);
    RectangleMatrix(const int &rows, const int &columns, T *elements);
    ~RectangleMatrix();
    RectangleMatrix(const Matrix<T> &matrix);

    T *MatrixNorm();
    T Get(const int &row, const int &column);
    int GetRowSize();
    int GetColumnSize();

    Matrix<T> *Addition(const Matrix<T> &matrix);
    Matrix<T> *MultiplicationByScalar(const T &scalar);
    Matrix<T> *Set(const T &value, const int &row, const int &column);

    Matrix<T> *SwapRows(const int &row_1, const int &row_2);
    Matrix<T> *SwapColumns(const int &col_1, const int &col_2);
    Matrix<T> *MultiplicationRowByNum(const int &row, const T &num);
    Matrix<T> *MultiplicationColumnByNum(const int &column, const T &num);
    Matrix<T> *AddRowToRow(const int &row_1, const int &row_2);
    Matrix<T> *AddColumnToColumn(const int &column_1, const int &column_2);
    Matrix<T> *Transpose();
};

template <class T>
RectangleMatrix<T>::~RectangleMatrix()
{
    delete[] elements;
}

template <class T>
RectangleMatrix<T>::RectangleMatrix()
{
    rows = 0;
    columns = 0;
    elements = new ArraySequence<T>;
}

template <class T>
RectangleMatrix<T>::RectangleMatrix(const int &rows, const int &columns)
{
    elements = new ArraySequence<T>(rows * columns);
    this->rows = rows;
    this->columns = columns;
}

template <class T>
RectangleMatrix<T>::RectangleMatrix(const int &rows, const int &columns, T *elements)
{
    this->rows = rows;
    this->columns = columns;
    this->elements = new ArraySequence<T>(elements, rows * columns);
}

template <class T>
RectangleMatrix<T>::RectangleMatrix(const Matrix<T> &matrix)
{
    this->rows = (static_cast<const RectangleMatrix<T> *>(&matrix))->rows;
    this->columns = (static_cast<const RectangleMatrix<T> *>(&matrix))->columns;
    this->elements = new ArraySequence<T>(*((static_cast<const RectangleMatrix<T> *>(&matrix))->elements));
}

template <class T>
Matrix<T> *RectangleMatrix<T>::Set(const T &value, const int &row, const int &column)
{
    this->elements->InsertAt(value, columns * row + column);
    return this;
}

template <class T>
T RectangleMatrix<T>::Get(const int &row, const int &column)
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
Matrix<T> *RectangleMatrix<T>::Addition(const Matrix<T> &matrix)
{
    // const RectangleMatrix<T> *tmp = static_cast<const RectangleMatrix<T> *>(&matrix);
    if (this->rows != (static_cast<const RectangleMatrix<T> *>(&matrix))->rows || this->columns != (static_cast<const RectangleMatrix<T> *>(&matrix))->columns)
    {
        throw std::logic_error("matrices have different sizes");
    }
    for (int i = 0; i < rows * columns; i++)
    {
        this->elements->InsertAt(this->elements->Get(i) + (static_cast<const RectangleMatrix<T> *>(&matrix))->elements->Get(i), i);
    }
    return this;
}

template <class T>
Matrix<T> *RectangleMatrix<T>::MultiplicationByScalar(const T &scalar)
{
    if (scalar == 0)
    {
        throw std::logic_error("matrix can't be multiplied by zero scalar");
    }
    for (int i = 0; i < rows * columns; i++)
    {
        this->elements->InsertAt(this->elements->Get(i) * scalar, i);
    }
    return this;
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
Matrix<T> *RectangleMatrix<T>::SwapRows(const int &row_1, const int &row_2)
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
    return this;
}

template <class T>
Matrix<T> *RectangleMatrix<T>::SwapColumns(const int &col_1, const int &col_2)
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
    return this;
}

template <class T>
Matrix<T> *RectangleMatrix<T>::MultiplicationRowByNum(const int &row, const T &num)
{
    for (int i = 0; i < columns; i++)
    {
        this->elements->InsertAt(this->elements->Get(columns * row + i) * num, columns * row + i);
    }
    return this;
}

template <class T>
Matrix<T> *RectangleMatrix<T>::MultiplicationColumnByNum(const int &column, const T &num)
{
    for (int i = 0; i < rows; i++)
    {
        this->elements->InsertAt(this->elements->Get(columns * i + column) * num, columns * i + column);
    }
    return this;
}

template <class T>
Matrix<T> *RectangleMatrix<T>::AddRowToRow(const int &row_1, const int &row_2)
{
    if (row_1 < 0 || row_2 < 0 || row_1 > rows || row_2 > rows)
        throw std::out_of_range("rows are out of range");
    for (int i = 0; i < columns; i++)
    {
        this->elements->InsertAt(this->elements->Get(columns * row_1 + i) + this->elements->Get(columns * row_2 + i), columns * row_1 + i);
    }
    return this;
}

template <class T>
Matrix<T> *RectangleMatrix<T>::AddColumnToColumn(const int &col_1, const int &col_2)
{
    if (col_1 < 0 || col_2 < 0 || col_1 > columns || col_2 > columns)
        throw std::out_of_range("columns are out of range");
    for (int i = 0; i < rows; i++)
    {
        this->elements->InsertAt(this->elements->Get(columns * i + col_1) + this->elements->Get(columns * i + col_2), columns * i + col_1);
    }
    return this;
}

template <class T>
Matrix<T> *RectangleMatrix<T>::Transpose()
{
    RectangleMatrix<T> *TransposeMatrix = new RectangleMatrix<T>(columns, rows);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            TransposeMatrix->elements->InsertAt(this->elements->Get(columns * i + j), rows * j + i);
        }
    }
    return TransposeMatrix;
}
