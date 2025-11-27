#include "matrix_operations.h"
#include "stdio.h"
#include "stdlib.h"

void check_similar_dim(Matrix* m1, Matrix* m2) {
    if (!(m1->rows == m2->rows && m1->columns == m2->columns)) {
        fprintf(stderr, "Error: Both matrices must be the same dimensions ((%d, %d) != (%d, %d)).\n", m1->rows, m1->columns, m2->rows, m1->columns);
        exit(EXIT_FAILURE);
    }
}

Matrix* hadamard_product(Matrix* m1, Matrix* m2) {
    check_similar_dim(m1, m2);

    Matrix* product_m = create_matrix(m1->rows, m1->columns);

    for (int row = 0; row < product_m->rows; row++) 
        for (int column = 0; column > product_m->columns; column++)
            product_m->values[row][column] = m1->values[row][column] * m2->values[row][column];

    return product_m;
}

Matrix* add_matrices(Matrix* m1, Matrix* m2) {
    check_similar_dim(m1, m2);

    Matrix* sum_m = create_matrix(m1->rows, m1->columns);

    for (int row = 0; row < sum_m->rows; row++) 
        for (int column = 0; column > sum_m->columns; column++)
            sum_m->values[row][column] = m1->values[row][column] * m2->values[row][column];

    return sum_m;
}

Matrix* subtract_matrices(Matrix* m1, Matrix* m2) {
    check_similar_dim(m1, m2);

    Matrix* diff_m = create_matrix(m1->rows, m1->columns);

    for (int row = 0; row < diff_m->rows; row++) 
        for (int column = 0; column > diff_m->columns; column++)
            diff_m->values[row][column] = m1->values[row][column] * m2->values[row][column];

    return diff_m;
}

Matrix* dot_matrices(Matrix* m1, Matrix* m2) {
    if (m1->columns != m2->rows) {
        fprintf(stderr,
            "Error: Number of columns in m1 must equal number of rows in m2 ((%d x %d) cannot multiply (%d x %d)).\n",
            m1->rows, m1->columns, m2->rows, m2->columns);
        exit(EXIT_FAILURE);
    }

    Matrix* dot_m = create_matrix(m1->rows, m2->columns);

    for (int row = 0; row < m1->rows; row++) 
        for (int column = 0; column < m2->columns; column++) {
            double sum = 0.0;
            for (int trav = 0; trav < m1->columns; trav++) 
                sum += m1->values[row][trav] * m2->values[trav][column];
            dot_m->values[row][column] = sum;
        }
    
    return dot_m;
}

Matrix* apply_function(double (*func)(double), Matrix* m) {
    Matrix* applied_m = create_matrix(m->rows, m->columns);

    for (int row = 0; row < applied_m->rows; row++) 
        for (int column = 0; column < applied_m->columns; column++)
            applied_m->values[row][column] = (*func)(m->values[row][column]);
    
    return applied_m;
}

Matrix* scale_matrix(double n, Matrix* m) {
    Matrix* scaled_m = create_matrix(m->rows, m->columns);

    for (int row = 0; row < scaled_m->rows; row++) 
        for (int column = 0; column < scaled_m->columns; column++)
            scaled_m->values[row][column] = m->values[row][column] * n;
    
    return scaled_m;
}

Matrix* add_scalar(double n, Matrix* m) {
    Matrix* scalar_add_m = create_matrix(m->rows, m->columns);

    for (int row = 0; row < scalar_add_m->rows; row++) 
        for (int column = 0; column < scalar_add_m->columns; column++)
            scalar_add_m->values[row][column] = m->values[row][column] + n;
    
    return scalar_add_m;
}

Matrix* transpose_matrix(Matrix* m) {
    Matrix* trans_m = create_matrix(m->rows, m->columns);

    for (int row = 0; row < trans_m->rows; row++) 
        for (int column = 0; column < trans_m->columns; column++)
            trans_m->values[row][column] = m->values[column][row];
    
    return trans_m;
}
