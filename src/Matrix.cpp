
#include "Matrix.h"

Matrix::Matrix(const int m, const int n, const float *data) : m(m), n(n) {

    matrix = new float[m * n];

    for (int i = 0; i < m * n; ++i) {
        matrix[i] = data[i];
    }
}

Matrix::~Matrix() {
    delete matrix;
    matrix = nullptr;
}

Matrix Matrix::getSubmatrix(const int row, const int column) {
    const int adjustedRow = row - 1;
    const int adjustedColumn = column - 1;
    const int submatrixSize = (m - 1) * (n - 1);
    float submatrix[submatrixSize];

    float *toMatrix = &submatrix[0];

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == adjustedRow) continue;
            if (j == adjustedColumn) continue;
            *toMatrix++ = matrix[i * n + j];
        }
    }

    return Matrix(m - 1, n - 1, submatrix);
}

void Matrix::addMultipleOfRow(const float multiple, const int fromIndex, const int toIndex) {

    float *from = &matrix[(fromIndex - 1) * n];
    float *to = &matrix[(toIndex - 1) * n];

    for (int i = 0; i < n; ++i) {
        *to++ += *from++ * multiple;
    }
}

void Matrix::interchangeRows(const int row1Index, const int row2Index) {

    float *row1 = &matrix[(row1Index - 1) * n];
    float *row2 = &matrix[(row2Index - 1) * n];

    for (int i = 0; i < n; ++i) {
        std::swap(*row1++, *row2++);
    }

}

void Matrix::scaleRow(const int rowIndex, const float c) {
    assert(std::abs(c) > zero);
    float *row = &matrix[(rowIndex - 1) * n];

    for (int i = 0; i < n; ++i) {
        *row++ *= c;
    }
}

std::string Matrix::toString() {

    std::stringstream result;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            result << matrix[i * n + j] << " ";
        }
        result << std::endl;
    }

    return result.str();

}

bool Matrix::isSquare() {
    return m == n;
}

float Matrix::determinantSlow() {
    assert(isSquare());

    float det = 0;
    int multiplier = 1;

    if (m == 1) return matrix[0];

    for (int i = 0; i < n; ++i) {
        det += multiplier * matrix[i] * getSubmatrix(1, i + 1).determinantSlow();
        multiplier *= -1;
    }

    return det;
}

float Matrix::determinantFast() {
    assert(isSquare());

    // Take a copy of the matrix before mutating it with the determinant calculations
    float *originalMatrix = new float [m * n];
    for (int i = 0; i < m * n; ++i) {
        originalMatrix[i] = matrix[i];
    }

    const float beta = makeUpperTriangular();
    const float det = beta * multiplyDiagonal();

    // restore matrix to original matrix
    delete matrix;
    matrix = originalMatrix;

    return det;
}

float Matrix::makeUpperTriangular() {


    float beta = 1;
    for (int i = 0; i < n; ++i) {
        int row = -1;

        // Find a non-zero entry in the column
        for (int j = i; j < m; ++j) {
            if (std::abs(matrix[j * n + i]) > zero) {
                row = j;
                break;
            }
        }

        // A column of all 0's exists, return 0 immediately
        if (row == -1) return 0;

        // Swap rows if necessary to bring a non-zero to this place in the matrix
        if (row != i) {
            interchangeRows(row + 1, i + 1);
            // Update the beta value because the row swap happened.
            beta *= -1;
        }

        // eliminate values below this entry
        for (int k = i + 1; k < m; ++k) {
            if (std::abs(matrix[k * n + i]) < zero) continue;
            addMultipleOfRow(-1 * matrix[k * n + i] / matrix[i * n + i], i + 1, k + 1);
        }
    }

    return beta;
}

float Matrix::multiplyDiagonal() {
    assert(isSquare());

    float result = 1;
    for (int i = 0; i < n; ++i) {
        result *= matrix[i * n + i];
        if (result == 0) break;
    }

    return result;
}
