#include <iostream>
#include "ArraySequence.h"
#include "Matrix.h"

typedef enum
{
    UPPER,
    LOWER,
    NOTDEFINED
} TriangleMatrixType;

template <class T>
class TriangleMatrix : public Matrix<T>
{
private:
    Sequence<T> *elements;
    int size;
    TriangleMatrixType MatrixType;

public:
    TriangleMatrix();
    ~TriangleMatrix();
    TriangleMatrix(const int &rows, const int &columns);
    TriangleMatrix(const int &rows, const int &columns, T *elements, TriangleMatrixType MatrixType);
    TriangleMatrix(const Matrix<T> &matrix);

    Matrix<T> *Addition(const Matrix<T> &matrix);
    Matrix<T> *MultiplicationByScalar(const T &scalar);
    T *MatrixNorm();
    T Get(const int &row, const int &column);
    Matrix<T> *Set(const T &value, const int &row, const int &column);
    int GetRowSize();
    int GetColumnSize();

    Matrix<T> *SwapRows(const int &row_1, const int &row_2);
    Matrix<T> *SwapColumns(const int &col_1, const int &col_2);
    Matrix<T> *MultiplicationRowByNum(const int &row, const T &num);
    Matrix<T> *MultiplicationColumnByNum(const int &column, const T &num);
    Matrix<T> *AddRowToRow(const int &row_1, const int &row_2);
    Matrix<T> *AddColumnToColumn(const int &column_1, const int &column_2);
    Matrix<T> *Transpose();
};

template <class T>
TriangleMatrix<T>::TriangleMatrix(const Matrix<T> &matrix)
{
    this->rows = (static_cast<const TriangleMatrix<T> *>(&matrix))->rows;
    this->columns = (static_cast<const TriangleMatrix<T> *>(&matrix))->columns;
    this->elements = new ArraySequence<T>(*((static_cast<const TriangleMatrix<T> *>(&matrix))->elements));
}

template <class T>
TriangleMatrix<T>::TriangleMatrix()
{
    elements = new ArraySequence<T>;
    size = 0;
    MatrixType = NOTDEFINED;
}

template <class T>
TriangleMatrix<T>::~TriangleMatrix()
{
    delete[] elements;
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const int &rows, const int &columns)
{
    if (rows != columns)
        throw std::logic_error("Triangle matrix must be square");
    size = rows;
    elements = new ArraySequence<T>(((rows + 1) * columns) / 2);
    MatrixType = NOTDEFINED;
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(const int &rows, const int &columns, T *elements, TriangleMatrixType MatrixType)
{
    if (rows != columns)
        throw std::logic_error("Triangle matrix must be square");
    this->MatrixType = MatrixType;
    this->elements = new ArraySequence<T>(((rows + 1) * rows) / 2);
    size = rows;
    if (MatrixType == UPPER)
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
    if (MatrixType == LOWER)
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
Matrix<T> *TriangleMatrix<T>::Set(const T &value, const int &row, const int &column)
{
    if (MatrixType == UPPER)
    {
        if (row > column)
            throw std::logic_error("this element can not be set in Triangular Matrix");
        else
            this->elements->InsertAt(value, size * row + column - (row * (row + 1)) / 2);
    }
    if (MatrixType == LOWER)
    {
        if (row < column)
            throw std::logic_error("this element can not be set in Triangular Matrix");
        else
            this->elements->InsertAt(value, size * row + column - ((size - row) * (size - 1) * row) / 2);
    }
    return this;
}

template <class T>
T TriangleMatrix<T>::Get(const int &row, const int &column)
{
    if (row >= size || column >= size || row < 0 || column < 0)
        throw std::out_of_range("index is out of range");
    if (MatrixType == UPPER)
    {
        if (row > column)
            return 0;
        else
            return this->elements->Get(size * row + column - (row * (row + 1)) / 2);
    }
    if (MatrixType == LOWER)
    {
        if (row < column)
            return 0;
        else
            return this->elements->Get(size * row + column - ((size - row) * (size - 1) * row) / 2);
    }
    return 0;
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
Matrix<T> *TriangleMatrix<T>::Addition(const Matrix<T> &matrix)
{
    const TriangleMatrix<T> *tmp = static_cast<const TriangleMatrix<T> *>(&matrix);
    if (this->size != tmp->size)
        throw std::logic_error("matrices have different sizes");
    for (int i = 0; i < (((this->size + 1) * this->size) / 2); i++)
    {
        this->elements->InsertAt(this->elements->Get(i) + tmp->elements->Get(i), i);
    }
    return this;
}

template <class T>
Matrix<T> *TriangleMatrix<T>::MultiplicationByScalar(const T &scalar)
{
    if (scalar == 0)
        throw std::logic_error("matrix can't be multiplied by zero scalar");
    for (int i = 0; i < (((this->size + 1) * this->size) / 2); i++)
    {
        this->elements->InsertAt(this->elements->Get(i) * scalar, i);
    }
    return this;
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
Matrix<T> *TriangleMatrix<T>::SwapRows(const int &row_1, const int &row_2)
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}

template <class T>
Matrix<T> *TriangleMatrix<T>::SwapColumns(const int &col_1, const int &col_2)
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}

template <class T>
Matrix<T> *TriangleMatrix<T>::MultiplicationRowByNum(const int &row, const T &num)
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}

template <class T>
Matrix<T> *TriangleMatrix<T>::MultiplicationColumnByNum(const int &column, const T &num)
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}

template <class T>
Matrix<T> *TriangleMatrix<T>::AddRowToRow(const int &row_1, const int &row_2)
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}

template <class T>
Matrix<T> *TriangleMatrix<T>::AddColumnToColumn(const int &column_1, const int &column_2)
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}

template <class T>
Matrix<T> *TriangleMatrix<T>::Transpose()
{
    throw std::logic_error("This action can't be executed for triangle matrix");
}