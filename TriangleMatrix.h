#include <iostream>

template <class T>
class TriangleMatrix
{
private:
    T *elements;
    int length;

public:
    TriangleMatrix();
    TriangleMatrix(int length);
    TriangleMatrix(int length, T *elements);

    void Addition(TriangleMatrix<T> *matrix);
    void MultiplicationByScalar(T scalar);
    T *MatrixNorm();
    T Get(int row, int column);
};

template <class T>
T TriangleMatrix<T>::Get(int row, int column)
{
    int NumsBfr = 0;
    if (row >= column)
        return 0;
    else
    {
        for (int i = 0; i < (row - 1); i++)
        {
            NumsBfr += length - i;
        }
        return elements[NumsBfr + column - row];
    }
}

template <class T>
TriangleMatrix<T>::TriangleMatrix()
{
    elements = nullptr;
    length = 0;
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(int length)
{
    int tmp = ((length + 1) * length) / 2;
    elements = new T[tmp];
    this->length = length;
}

template <class T>
TriangleMatrix<T>::TriangleMatrix(int length, T *elements)
{
    int tmp = ((length + 1) * length) / 2;
    elements = new T[tmp];
    this->length = length;
    int jtmp = 0;
    int k = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = i; j < length; j++)
        {
            this->elements[k] = elements[i * length + j];
            k++;
        }
    }
}

template <class T>
void TriangleMatrix<T>::Addition(TriangleMatrix<T> *matrix)
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
void TriangleMatrix<T>::MultiplicationByScalar(T scalar)
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
T *TriangleMatrix<T>::MatrixNorm()
{
    T *Norms = new T[3];
    T *rowsSum = new T[this->length];
    T *columnsSum = new T[this->length];
    int p, q = 0;
    T tmp;
    for (int i = 0; i < this->length; i++)
    {
        p = q;
        tmp = this->elements[p];
        q = p + this->length - i;
        for (p; p < q; p++)
        {
            tmp += this->elements[p];
        }
        rowsSum[i] = tmp - this->elements[p];
    }

    q = 0;
    int t;
    for (int i = 0; i < this->length; i++)
    {
        tmp = this->elements[i];
        p = i;
        t = 1;
        for (p; p <= q; p += this->length - t)
        {
            tmp += this->elements[p];
            t++;
        }
        q = q + this->length - i;
        columnsSum[i] = tmp = this->elements[i];
    }

    Norms[1] = *std::max_element(rowsSum, rowsSum + this->length);
    Norms[1] = *std::max_element(columnsSum, columnsSum + this->length);
    Norms[2] = this->elements[0] * this->elements[0];
    for (int i = 1; i < this->length; i++)
    {
        Norms[2] += (this->elements[i] * this->elements[i]);
    }
    Norms[2] = sqrt(Norms[2]);
    return Norms;
}