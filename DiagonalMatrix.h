#include <iostream>
#include <bits/stdc++.h>
template <class T>
class DiagonalMatrix
{
private:
    T *elements;
    int length;

public:
    DiagonalMatrix();
    DiagonalMatrix(int length);
    DiagonalMatrix(int length, T *elements);

    void Addition(DiagonalMatrix<T> *matrix);
    void MultiplicationByScalar(T scalar);
    T *MatrixNorm();
    T Get(int row, int column);
};

template <class T>
T DiagonalMatrix<T>::Get(int row, int column)
{
    if ((row < 0) || (row >= this->length) || (column < 0) || (column >= this->length))
        throw std::out_of_range("index is out of range");
    if (row != column)
        return 0;
    else
        return this->elements[row];
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix()
{
    elements = nullptr;
    length = 0;
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(int length)
{
    elements = new T[length];
    this->length = length;
}

template <class T>
DiagonalMatrix<T>::DiagonalMatrix(int length, T *elements)
{
    int pos = 0;
    this->elements = new T[length];
    for (int i = 0; i < length * length; i++)
    {
        this->elements[i] = elements[pos];
        pos += length + 1;
    }
}

template <class T>
void DiagonalMatrix<T>::Addition(DiagonalMatrix<T> *matrix)
{
    if (this->length != matrix->length)
    {
        throw std::logic_error("matrices have different sizes");
    }
    for (int i = 0; i < this->length; i++)
    {
        this->elements[i] = matrix->elements[i];
    }
}

template <class T>
void DiagonalMatrix<T>::MultiplicationByScalar(T scalar)
{
    if (scalar == 0)
    {
        throw std::logic_error("matrix can't be multiplied by zero scalar");
    }
    for (int i = 0; i < this->length; i++)
    {
        this->elements[i] *= scalar;
    }
}

template <class T>
T *DiagonalMatrix<T>::MatrixNorm()
{
    T *Norms = new T[3];
    Norms[0] = *std::max_element(this->elements, this->elements + this->length);
    Norms[1] = Norms[0];
    Norms[2] = this->elements[0] * this->elements[0];
    for (int i = 1; i < this->length; i++)
    {
        Norms[2] += (this->elements[i] * this->elements[i]);
    }
    Norms[2] = sqrt(Norms[2]);
    return Norms;
}