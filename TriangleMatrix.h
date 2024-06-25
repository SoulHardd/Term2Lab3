#include <iostream>
#include "ArraySequence.h"
#include "Matrix.h"

typedef enum
{
    UPPER,
    LOWER,
    NOTDEFINED
} TrMatrixType;

template <class T>
class TriangleMatrix : public Matrix<T>
{
private:
    Sequence<T> *elements;
    int size;
    TrMatrixType MType;

public:
    TriangleMatrix();
    TriangleMatrix(int rows, int columns);
    TriangleMatrix(int rows, int columns, T *elements, TrMatrixType Mtype);

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
Matrix<T> *TriangleMatrix<T>::Set(T value, int row, int column)
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
int TriangleMatrix<T>::GetRowSize()
{
    return this->size;
}

template <class T>
int TriangleMatrix<T>::GetColumnSize()
{
    return this->size;
}

template <class T>
Matrix<T> *TriangleMatrix<T>::Addition(Matrix<T> *matrix)
{
    TriangleMatrix<T> *tmp = static_cast<TriangleMatrix<T> *>(matrix);
    if (this->size != tmp->size)
        throw std::logic_error("matrices have different sizes");
    for (int i = 0; i < this->size; i++)
    {
        this->elements->InsertAt(this->elements->Get(i) + tmp->elements->Get(i), i);
    }
}

template <class T>
Matrix<T> *TriangleMatrix<T>::MultiplicationByScalar(T scalar)
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

template <class T>
Matrix<T> *TriangleMatrix<T>::SwapColumns(int col_1, int col_2)
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}

template <class T>
Matrix<T> *TriangleMatrix<T>::MultiplicationRowByNum(int row, T num)
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}

template <class T>
Matrix<T> *TriangleMatrix<T>::MultiplicationColumnByNum(int column, T num)
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}

template <class T>
Matrix<T> *TriangleMatrix<T>::AddRowToRow(int row_1, int row_2)
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}

template <class T>
Matrix<T> *TriangleMatrix<T>::AddColumnToColumn(int column_1, int column_2)
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}

template <class T>
Matrix<T> *TriangleMatrix<T>::Transpose()
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}