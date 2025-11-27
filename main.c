#include "headers/matrix.h"
#include "headers/matrix_operations.h"

void main(void) {
    Matrix* matrix = create_matrix(4,4);
    fill_matrix(matrix, 0);
    print_matrix(matrix);
    randomize_matrix(matrix, 5);
    print_matrix(matrix);
    matrix = transpose_matrix(matrix);
    print_matrix(matrix);
}