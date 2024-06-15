#include <iostream>
#include "Matrix.h"
#include "RectangleMatrix.h"
#include "DiagonalMatrix.h"
#include "TriangleMatrix.h"

template <class T>
class UnifiedRectangleMatrix : public Matrix<T>
{
private:
    RectangleMatrix<T> *matrix;

public:
    UnifiedRectangleMatrix()
    {
        this->matrix = new RectangleMatrix<T>();
    }

    UnifiedRectangleMatrix(int rows, int columns)
    {
        this->matrix = new RectangleMatrix<T>(rows, columns);
    }

    UnifiedRectangleMatrix(int rows, int columns, T *elements)
    {
        this->matrix = new RectangleMatrix<T>(rows, columns, elements);
    }

    T Get(int row, int column)
    {
        return this->matrix->Get(row, column);
    }

    Matrix<T> *Addition(Matrix<T> *matrix)
    {
        UnifiedRectangleMatrix<T> *tmp = static_cast<UnifiedRectangleMatrix<T> *>(matrix);
        this->matrix->Addition(tmp->matrix);
        return this;
    }

    Matrix<T> *MultiplicationByScalar(T scalar)
    {
        this->matrix->MultiplicationByScalar(scalar);
        return this;
    }

    T *MatrixNorm()
    {
        return this->matrix->MatrixNorm();
    }

    Matrix<T> *SwapRows(int row_1, int row_2)
    {
        this->matrix->SwapRows(row_1, row_2);
        return this;
    }

    Matrix<T> *SwapColumns(int col_1, int col_2)
    {
        this->matrix->SwapColumns(col_1, col_2);
        return this;
    }

    Matrix<T> *MultiplicationRowByNum(int row, T num)
    {
        this->matrix->MultiplicationRowByNum(row, num);
        return this;
    }

    Matrix<T> *MultiplicationColumnByNum(int column, T num)
    {
        this->matrix->MultiplicationColumnByNum(column, num);
        return this;
    }

    Matrix<T> *AddRowToRow(int row_1, int row_2)
    {
        this->matrix->AddRowToRow(row_1, row_2);
        return this;
    }

    Matrix<T> *AddColumnToColumn(int column_1, int column_2)
    {
        this->matrix->AddColumnToColumn(column_1, column_2);
        return this;
    }

    Matrix<T> *Transpose()
    {
        RectangleMatrix<T> *TransposeMatrix;
        TransposeMatrix = this->matrix->Transpose();
        UnifiedRectangleMatrix<T> *tmp = new UnifiedRectangleMatrix<T>;
        tmp->matrix = TransposeMatrix;
        return tmp;
    }
};

template <class T>
class UnifiedDiagonalMatrix : public Matrix<T>
{
private:
    DiagonalMatrix<T> *matrix;

public:
    UnifiedDiagonalMatrix()
    {
        this->matrix = new DiagonalMatrix<T>();
    }

    UnifiedDiagonalMatrix(int length)
    {
        this->matrix = new DiagonalMatrix<T>(length);
    }

    UnifiedDiagonalMatrix(int length, T *elements)
    {
        this->matrix = new DiagonalMatrix<T>(length, elements);
    }

    T Get(int row, int column)
    {
        return this->matrix->Get(row, column);
    }

    Matrix<T> *Addition(Matrix<T> *matrix)
    {
        UnifiedDiagonalMatrix<T> *tmp = static_cast<UnifiedDiagonalMatrix<T> *>(matrix);
        this->matrix->Addition(tmp->matrix);
        return this;
    }

    Matrix<T> *MultiplicationByScalar(T scalar)
    {
        this->matrix->MultiplicationByScalar(scalar);
        return this;
    }

    T *MatrixNorm()
    {
        return this->matrix->MatrixNorm();
    }

    Matrix<T> *SwapRows(int row_1, int row_2)
    {
        throw std::logic_error("This action can't be executed for diagonal matrix");
    }

    Matrix<T> *SwapColumns(int col_1, int col_2)
    {
        throw std::logic_error("This action can't be executed for diagonal matrix");
    }

    Matrix<T> *MultiplicationRowByNum(int row, T num)
    {
        throw std::logic_error("This action can't be executed for diagonal matrix");
    }

    Matrix<T> *MultiplicationColumnByNum(int column, T num)
    {
        throw std::logic_error("This action can't be executed for diagonal matrix");
    }

    Matrix<T> *AddRowToRow(int row_1, int row_2)
    {
        throw std::logic_error("This action can't be executed for diagonal matrix");
    }

    Matrix<T> *AddColumnToColumn(int column_1, int column_2)
    {
        throw std::logic_error("This action can't be executed for diagonal matrix");
    }

    Matrix<T> *Transpose()
    {
        throw std::logic_error("This action can't be executed for diagonal matrix");
    }
};

template <class T>
class UnifiedTriangleMatrix : public Matrix<T>
{
private:
    TriangleMatrix<T> *matrix;

public:
    UnifiedTriangleMatrix()
    {
        this->matrix = new TriangleMatrix<T>();
    }

    UnifiedTriangleMatrix(int length)
    {
        this->matrix = new TriangleMatrix<T>(length);
    }

    UnifiedTriangleMatrix(int length, T *elements)
    {
        this->matrix = new TriangleMatrix<T>(length, elements);
    }

    T Get(int row, int column)
    {
        return this->matrix->Get(row, column);
    }

    Matrix<T> *Addition(Matrix<T> *matrix)
    {
        UnifiedTriangleMatrix<T> *tmp = static_cast<UnifiedTriangleMatrix<T> *>(matrix);
        this->matrix->Addition(tmp->matrix);
        return this;
    }

    Matrix<T> *MultiplicationByScalar(T scalar)
    {
        this->matrix->MultiplicationByScalar(scalar);
        return this;
    }

    T *MatrixNorm()
    {
        return this->matrix->MatrixNorm();
    }

    Matrix<T> *SwapRows(int row_1, int row_2)
    {
        throw std::logic_error("This action can't be executed for triangle matrix");
    }

    Matrix<T> *SwapColumns(int col_1, int col_2)
    {
        throw std::logic_error("This action can't be executed for triangle matrix");
    }

    Matrix<T> *MultiplicationRowByNum(int row, T num)
    {
        throw std::logic_error("This action can't be executed for triangle matrix");
    }

    Matrix<T> *MultiplicationColumnByNum(int column, T num)
    {
        throw std::logic_error("This action can't be executed for triangle matrix");
    }

    Matrix<T> *AddRowToRow(int row_1, int row_2)
    {
        throw std::logic_error("This action can't be executed for triangle matrix");
    }

    Matrix<T> *AddColumnToColumn(int column_1, int column_2)
    {
        throw std::logic_error("This action can't be executed for triangle matrix");
    }

    Matrix<T> *Transpose()
    {
        throw std::logic_error("This action can't be executed for triangle matrix");
    }
};