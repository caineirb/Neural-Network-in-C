#include "matrix.h"
#include "matrix_operations.h"
#include "activation_functions.h"
#include "math.h"

double sigmoid(double input) {
    return 1.0 / (1+exp(-1 * input));
}

Matrix* sigmoid_derivative(Matrix* m) {
    Matrix* sigder_m = create_matrix(m->rows, m->columns);
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->columns; j++) {
            double s = m->values[i][j];
            sigder_m->values[i][j] = s * (1.0 - s);
        }

    return sigder_m;
}


Matrix* softmax(Matrix* m) {
    Matrix* softmax_m = create_matrix(m->rows, m->columns);

    for (int row = 0; row < m->rows; row++) {
        double total = 0;
        for (int column = 0; column < m->columns; column++) {
            double expo = exp(m->values[row][column]);
            softmax_m->values[row][column] = expo;
            total += expo;
        }

        for (int column = 0; column < m->columns; column++) {
            softmax_m->values[row][column] /= total;
        }
    }
    
    return softmax_m;
}
