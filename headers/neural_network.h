#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "matrix.h"
#include "image.h"

typedef struct {
    int input;
    int hidden;
    int output;
    double learning_rate;
    Matrix* hidden_weights;
    Matrix* output_weights;
} NeuralNetwork;

NeuralNetwork* create_network(int input, int hidden, int output, double learning_rate);
double compute_loss(Matrix* output_pred, Matrix* output_real);
void train_network(NeuralNetwork* nn, Matrix* input_data, Matrix* output_data);
void train_images(NeuralNetwork* nn, Image** imgs, int batch_size);
Matrix* predict_image(NeuralNetwork* nn, Image* img);
double predict_images(NeuralNetwork* nn, Image** imgs, int num_images);
Matrix* predict_network(NeuralNetwork* nn, Matrix* input_data);
// void save_network(NeuralNetwork* nn, char* file_location);
// NeuralNetwork* load_network(char* file_location);
// void print_network(NeuralNetwork* nn);
void free_network(NeuralNetwork* nn);

#endif //NEURAL_NETWORK_H
