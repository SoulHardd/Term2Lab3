#include <iostream>
#include <bits/stdc++.h>
#include "ArraySequence.h"
#include "Matrix.h"

template <class T>
class DiagonalMatrix : public Matrix<T>
{
private:
    Sequence<T> *elements;
    int size;

public:
    DiagonalMatrix();
    ~DiagonalMatrix();
    DiagonalMatrix(int rows, int columns);
    DiagonalMatrix(int rows, int columns, T *elements);

    Matrix<T> *Addition(Matrix<T> *matrix);
    Matrix<T> *MultiplicationByScalar(T scalar);
    T *MatrixNorm();
    T Get(int row, int column);
    Matrix<T> *Set(T value, int row, int column);
    int GetRowSize();
    int GetColumnSize();

    Matrix<T> *SwapRows(int row_1, int row_2);
    Matrix<T> *SwapColumns(int col_1, int col_2);
    Matrix<T> *MultiplicationRowByNum(int row, T num);
    Matrix<T> *MultiplicationColumnByNum(int column, T num);
    Matrix<T> *AddRowToRow(int row_1, int row_2);
    Matrix<T> *AddColumnToColumn(int column_1, int column_2);
    Matrix<T> *Transpose();
};

template <class T>
DiagonalMatrix<T>::DiagonalMatrix()
{
    elements = new ArraySequence<T>;
    size = 0;
}

template <class T>
DiagonalMatrix<T>::~DiagonalMatrix()
{
    delete[] elements;
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(int rows, int columns)
{
    if (rows != columns)
        throw std::logic_error("Diagonal matrix must be square");
    elements = new ArraySequence<T>(rows);
    this->size = rows;
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(int rows, int columns, T *elements)
{
    if (rows != columns)
        throw std::logic_error("Diagonal matrix must be square");
    this->elements = new ArraySequence<T>(rows);
    this->size = rows;
    for (int i = 0; i < this->size; i++)
    {
        this->elements->InsertAt(elements[columns * i + i], i);
    }
}

template <class T>
Matrix<T> *DiagonalMatrix<T>::Set(T value, int row, int column)
{
    if (row != column)
        throw std::logic_error("This element can not be set in diagonal matrix");
    else
        this->elements->InsertAt(value, row);
    return this;
}

template <class T>
T DiagonalMatrix<T>::Get(int row, int column)
{
    if ((row < 0) || (row >= size) || (column < 0) || (column >= size))
        throw std::out_of_range("index is out of range");
    if (row != column)
        return 0;
    else
        return this->elements->Get(row);
}

template <class T>
int DiagonalMatrix<T>::GetRowSize()
{
    return this->size;
}

template <class T>
int DiagonalMatrix<T>::GetColumnSize()
{
    return this->size;
}

template <class T>
Matrix<T> *DiagonalMatrix<T>::Addition(Matrix<T> *matrix)
{
    DiagonalMatrix<T> *tmp = static_cast<DiagonalMatrix<T> *>(matrix);
    if (this->size != tmp->size)
    {
        throw std::logic_error("matrices have different sizes");
    }
    for (int i = 0; i < tmp->size; i++)
    {
        this->elements->InsertAt(this->elements->Get(i) + tmp->elements->Get(i), i);
    }
    return this;
}

template <class T>
Matrix<T> *DiagonalMatrix<T>::MultiplicationByScalar(T scalar)
{
    if (scalar == 0)
        throw std::logic_error("matrix can't be multiplied by zero scalar");
    for (int i = 0; i < this->size; i++)
    {
        this->elements->InsertAt(this->elements->Get(i) * scalar, i);
    }
    return this;
}

template <class T>
T *DiagonalMatrix<T>::MatrixNorm()
{
    T *Norms = new T[3];
    Norms[0] = this->elements->Get(0);
    for (int i = 1; i < size; i++)
    {
        if (this->elements->Get(i) > Norms[0])
            Norms[0] = this->elements->Get(i);
    }

    Norms[1] = Norms[0];
    Norms[2] = this->elements->Get(0) * this->elements->Get(0);
    for (int i = 1; i < this->size; i++)
    {
        Norms[2] += (this->elements->Get(i) * this->elements->Get(i));
    }
    Norms[2] = sqrt(Norms[2]);
    return Norms;
}

template <class T>
Matrix<T> *DiagonalMatrix<T>::SwapRows(int row_1, int row_2)
{
    throw std::logic_error("This action can't be executed for diagonal matrix");
}

template <class T>
Matrix<T> *DiagonalMatrix<T>::SwapColumns(int col_1, int col_2)
{
    throw std::logic_error("This action can't be executed for diagonal matrix");
}

template <class T>
Matrix<T> *DiagonalMatrix<T>::MultiplicationRowByNum(int row, T num)
{
    throw std::logic_error("This action can't be executed for diagonal matrix");
}

template <class T>
Matrix<T> *DiagonalMatrix<T>::MultiplicationColumnByNum(int column, T num)
{
    throw std::logic_error("This action can't be executed for diagonal matrix");
}

template <class T>
Matrix<T> *DiagonalMatrix<T>::AddRowToRow(int row_1, int row_2)
{
    throw std::logic_error("This action can't be executed for diagonal matrix");
}

template <class T>
Matrix<T> *DiagonalMatrix<T>::AddColumnToColumn(int column_1, int column_2)
{
    throw std::logic_error("This action can't be executed for diagonal matrix");
}

template <class T>
Matrix<T> *DiagonalMatrix<T>::Transpose()
{
    throw std::logic_error("This action can't be executed for diagonal matrix");
}