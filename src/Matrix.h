
#ifndef DETERMINANT_MATRIX_H
#define DETERMINANT_MATRIX_H

#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

class Matrix {

private:

    static constexpr float zero = 1e-12;

    int m, n;
    float *matrix;
    bool isSquare();

    /**
     * Perform row operations on the matrix to transform it to an upper triangular form.
     * Mutates the matrix.
     * @return the beta value corresponding the row operations performed.
     */
    float makeUpperTriangular();

    /**
     * @return The product of a matrix's diagonal.
     */
    float multiplyDiagonal();

public:

    /**
     * Construct an mxn matrix.
     * @param m
     * @param n
     * @param data
     */
    explicit Matrix(int m, int n, const float *data);
    ~Matrix();

    /**
     * Create a new m-1 x n-1 matrix consisting of the original matrix with given row and column
     * removed.
     * @param row to remove in resulting matrix
     * @param column to remove in resulting matrix
     * @return new matrix with specified row and column removed.
     */
    Matrix getSubmatrix(int row, int column);

    /**
     * @return string representation of matrix
     */
    std::string toString();

    /**
     * Calculate the determinant of the matrix using the definition of determinants
     * @return the determinant of the matrix
     */
    float determinantSlow();

    /**
     * Calculate the determinant of the matrix by row reducing to upper triangular,
     * and multiplying across the diagonal.
     * @return the determinant of the matrix
     */
    float determinantFast();

    /**
     * Swap two rows of a matrix
     * @param row1Index
     * @param row2Index
     */
    void interchangeRows(int row1Index, int row2Index);

    /**
     * Scale the row of a matrix by a non-zero value.
     * @param rowIndex
     * @param c
     */
    void scaleRow(int rowIndex, float c);

    /**
     * Add the multiple of one row to another.
     * @param multiple
     * @param fromIndex
     * @param toIndex
     */
    void addMultipleOfRow(float multiple, int fromIndex, int toIndex);

};

#endif //DETERMINANT_MATRIX_H
