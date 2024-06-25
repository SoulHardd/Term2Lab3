#include <iostream>
#include "ArraySequence.h"

typedef enum
{
    UPPER,
    LOWER,
    NOTDEFINED
} TrMatrixType;

template <class T>
class TriangleMatrix
{
private:
    Sequence<T> *elements;
    int size;
    TrMatrixType MType;

public:
    TriangleMatrix();
    TriangleMatrix(int rows, int columns);
    TriangleMatrix(int rows, int columns, T *elements, TrMatrixType Mtype);

    void Addition(TriangleMatrix<T> *matrix);
    void MultiplicationByScalar(T scalar);
    T *MatrixNorm();
    T Get(int row, int column);
    int GetSize();
    void Set(T value, int row, int column);
};

template <class T>
TriangleMatrix<T>::TriangleMatrix()
{
    elements = new ArraySequence<T>;
    size = 0;
    MType = NOTDEFINED;
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(int rows, int columns)
{
    if (rows != columns)
        throw std::logic_error("Triangle matrix must be square");
    size = rows;
    elements = new ArraySequence<T>(((rows + 1) * columns) / 2);
    MType = NOTDEFINED;
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(int rows, int columns, T *elements, TrMatrixType Mtype)
{
    if (rows != columns)
        throw std::logic_error("Triangle matrix must be square");
    this->MType = Mtype;
    this->elements = new ArraySequence<T>(((rows + 1) * rows) / 2);
    size = rows;
    if (Mtype == UPPER)
    {
        int k = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = i; j < size; j++)
            {
                this->elements->InsertAt(elements[size * i + j], k);
                k++;
            }
        }
    }
    if (MType == LOWER)
    {
        int k = 0;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < i + 1; j++)
            {
                this->elements->InsertAt(elements[size * i + j], k);
                k++;
            }
        }
    }
}

template <class T>
void TriangleMatrix<T>::Set(T value, int row, int column)
{
    if (MType == UPPER)
    {
        if (row > column)
            throw std::logic_error("this element can not be set in Triangular Matrix");
        else
            this->elements->InsertAt(value, size * row + column - (row * (row + 1)) / 2);
    }
    if (MType == LOWER)
    {
        if (row < column)
            throw std::logic_error("this element can not be set in Triangular Matrix");
        else
            this->elements->InsertAt(value, size * row + column - ((size - row) * (size - 1) * row) / 2);
    }
}

template <class T>
T TriangleMatrix<T>::Get(int row, int column)
{
    if (row >= size || column >= size || row < 0 || column < 0)
        throw std::out_of_range("index is out of range");
    if (MType == UPPER)
    {
        if (row > column)
            return 0;
        else
            return this->elements->Get(size * row + column - (row * (row + 1)) / 2);
    }
    if (MType == LOWER)
    {
        if (row < column)
            return 0;
        else
            return this->elements->Get(size * row + column - ((size - row) * (size - 1) * row) / 2);
    }
}

template <class T>
int TriangleMatrix<T>::GetSize()
{
    return this->size;
}

template <class T>
void TriangleMatrix<T>::Addition(TriangleMatrix<T> *matrix)
{
    if (this->size != matrix->size)
        throw std::logic_error("matrices have different sizes");
    for (int i = 0; i < this->size; i++)
    {
        this->elements->InsertAt(this->elements->Get(i) + matrix->elements->Get(i), i);
    }
}

template <class T>
void TriangleMatrix<T>::MultiplicationByScalar(T scalar)
{
    if (scalar == 0)
        throw std::logic_error("matrix can't be multiplied by zero scalar");
    for (int i = 0; i < size; i++)
    {
        this->elements->InsertAt(this->elements->Get(i) * scalar, i);
    }
}

template <class T>
T *TriangleMatrix<T>::MatrixNorm()
{
    T *Norms = new T[3];
    T *rowsSum = new T[size];
    T *columnsSum = new T[size];
    T tmp;
    for (int i = 0; i < size; i++)
    {
        tmp = this->Get(i, 0);
        for (int j = 1; j < size; j++)
        {
            tmp += this->Get(i, j);
        }
        rowsSum[i] = tmp;
    }

    for (int i = 0; i < size; i++)
    {
        tmp = this->Get(0, i);
        for (int j = 1; j < size; j++)
        {
            tmp += this->Get(j, i);
        }
        columnsSum[i] = tmp;
    }

    Norms[0] = *std::max_element(rowsSum, rowsSum + this->size);
    Norms[1] = *std::max_element(columnsSum, columnsSum + this->size);
    delete[] rowsSum;
    delete[] columnsSum;

    Norms[2] = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            Norms[2] += this->Get(i, j) * this->Get(i, j);
        }
    }
    Norms[2] = sqrt(Norms[2]);
    return Norms;
}