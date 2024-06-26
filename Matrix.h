#ifndef MATRIX_H
#define MATRIX_H

template <class T>
class Matrix
{
public:
    virtual Matrix<T> *Addition(const Matrix<T> &matrix) = 0;
    virtual Matrix<T> *MultiplicationByScalar(const T &scalar) = 0;
    virtual T *MatrixNorm() = 0;
    virtual T Get(const int &row, const int &column) = 0;
    virtual Matrix<T> *Set(const T &value, const int &row, const int &column) = 0;
    virtual int GetRowSize() = 0;
    virtual int GetColumnSize() = 0;

    virtual Matrix<T> *SwapRows(const int &row_1, const int &row_2) = 0;
    virtual Matrix<T> *SwapColumns(const int &col_1, const int &col_2) = 0;
    virtual Matrix<T> *MultiplicationRowByNum(const int &row, const T &num) = 0;
    virtual Matrix<T> *MultiplicationColumnByNum(const int &column, const T &num) = 0;
    virtual Matrix<T> *AddRowToRow(const int &row_1, const int &row_2) = 0;
    virtual Matrix<T> *AddColumnToColumn(const int &column_1, const int &column_2) = 0;
    virtual Matrix<T> *Transpose() = 0;
};

#endif