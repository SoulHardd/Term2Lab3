#ifndef MATRIX_H

#define MATRIX_H

template <class T>
class Matrix
{
public:
    virtual Matrix<T> *Addition(Matrix<T> *matrix) = 0;
    virtual Matrix<T> *MultiplicationByScalar(T scalar) = 0;
    virtual T *MatrixNorm() = 0;
    virtual T Get(int row, int column) = 0;
    virtual Matrix<T> *Set(T value, int row, int column) = 0;
    virtual int GetRowSize() = 0;
    virtual int GetColumnSize() = 0;

    virtual Matrix<T> *SwapRows(int row_1, int row_2) = 0;
    virtual Matrix<T> *SwapColumns(int col_1, int col_2) = 0;
    virtual Matrix<T> *MultiplicationRowByNum(int row, T num) = 0;
    virtual Matrix<T> *MultiplicationColumnByNum(int column, T num) = 0;
    virtual Matrix<T> *AddRowToRow(int row_1, int row_2) = 0;
    virtual Matrix<T> *AddColumnToColumn(int column_1, int column_2) = 0;
    virtual Matrix<T> *Transpose() = 0;
};

#endif