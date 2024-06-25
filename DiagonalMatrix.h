#include <iostream>
#include <bits/stdc++.h>
#include "ArraySequence.h"

template <class T>
class DiagonalMatrix
{
private:
    Sequence<T> *elements;
    int size;

public:
    DiagonalMatrix();
    DiagonalMatrix(int rows, int columns);
    DiagonalMatrix(int rows, int columns, T *elements);

    void Addition(DiagonalMatrix<T> *matrix);
    void MultiplicationByScalar(T scalar);
    T *MatrixNorm();
    T Get(int row, int column);
    int GetSize();
    void Set(T value, int row, int column);
};

template <class T>
DiagonalMatrix<T>::DiagonalMatrix()
{
    elements = new ArraySequence<T>;
    size = 0;
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
        this->elements->InsertAt(columns * i + i, i);
    }
}

template <class T>
void DiagonalMatrix<T>::Set(T value, int row, int column)
{
    if (row != column)
        throw std::logic_error("This element can not be set in diagonal matrix");
    else
        this->elements->InsertAt(value, row);
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
int DiagonalMatrix<T>::GetSize()
{
    return this->size;
}

template <class T>
void DiagonalMatrix<T>::Addition(DiagonalMatrix<T> *matrix)
{
    if (this->size != matrix->size)
    {
        throw std::logic_error("matrices have different sizes");
    }
    for (int i = 0; i < this->size; i++)
    {
        this->elements->InsertAt(this->elements->Get(i) + matrix->elements->Get(i), i);
    }
}

template <class T>
void DiagonalMatrix<T>::MultiplicationByScalar(T scalar)
{
    if (scalar == 0)
        throw std::logic_error("matrix can't be multiplied by zero scalar");
    for (int i = 0; i < this->size; i++)
    {
        this->elements->InsertAt(this->elements->Get())
    }
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