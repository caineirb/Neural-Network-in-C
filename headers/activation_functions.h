#ifndef ACTIVATION_FUNCTIONS_H
#define ACTIVATION_FUNCTIONS_H

#include "matrix.h"

double sigmoid(double input);
Matrix* sigmoid_derivative(Matrix* m);
Matrix* softmax(Matrix* m);

#endif //ACTIVATION_FUNCTIONS_H