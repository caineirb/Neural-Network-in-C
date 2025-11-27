#pragma once

#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H
#include "matrix.h"

Matrix* hadamard_product(Matrix* m1, Matrix* m2);
Matrix* add_matrices(Matrix* m1, Matrix* m2);
Matrix* subtract_matrices(Matrix* m1, Matrix* m2);
Matrix* dot_matrices(Matrix* m1, Matrix* m2);
Matrix* apply_function(double (*func)(double), Matrix* m);
Matrix* scale_matrix(double n, Matrix* m);
Matrix* add_scalar(double n, Matrix* m);
Matrix* transpose_matrix(Matrix* m);

#endif // MATRIX_OPERATIONS_H
