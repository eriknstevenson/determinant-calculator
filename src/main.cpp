/**
 * MATH 211 Extra Problem #3
 * Erik Stevenson - October 24, 2017
 *
 * Description: Demonstrates the difference in efficiency between two ways of
 * calculating a 10x10 matrix's determinant.
 */

#include <iostream>
#include <random>
#include "Matrix.h"

int main() {

    // setup the random number generation
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_real_distribution<float> dist(-1.f, 1.f);

    // make a random mxn matrix with values between -1 and 1
    const auto m = 10, n = 10;
    float matrixData[m * n];
    for (int i = 0; i < m * n; ++i) {
        matrixData[i] = dist(gen);
    }

    // calculate determinant using the slower method, track time elapsed
    clock_t time1 = clock();
    Matrix matrix1(m, n, matrixData);
    const auto det1 = matrix1.determinantSlow();
    time1 = clock() - time1;

    // calculate determinant using the quicker method, track time elapsed
    clock_t time2 = clock();
    Matrix matrix2(m, n, matrixData);
    const auto det2 = matrix2.determinantFast();
    time2 = clock() - time2;

    // display results
    std::cout << "Using matrix: " << std::endl << matrix1.toString();
    std::cout << "calculated by definition: " << det1 << " ("
              << static_cast<float>(time1) / CLOCKS_PER_SEC << " seconds elapsed)" << std::endl;
    std::cout << "calculated by row reducing and multiplying: " << det2 << " ("
              << static_cast<float>(time2) / CLOCKS_PER_SEC << " seconds elapsed)" << std::endl;

    return EXIT_SUCCESS;
}
