#include "neural_network.h"
#include "matrix.h"
#include "matrix_operations.h"
#include "activation_functions.h"
#include "image.h"
#include "sys/stat.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAXCHAR 1000
#define CATEGORIES 10   // Change to the number of categories, in this case 0 - 9

NeuralNetwork* create_network(int input, int hidden, int output, double learning_rate) {
    NeuralNetwork* nn = malloc(sizeof(NeuralNetwork));
    
    nn->input = input;
    nn->hidden = hidden;
    nn->output = output;
    nn->learning_rate = learning_rate;
    
    nn->hidden_weights = create_matrix(nn->hidden, nn->input);
    nn->output_weights = create_matrix(nn->output, nn->hidden);
    randomize_matrix(nn->hidden_weights, rand() % hidden + 1); // random value from 1 to hidden
    randomize_matrix(nn->output_weights, rand() % output + 1); // random value from 1 to output
    
    return nn;
}

double compute_loss(Matrix* output_pred, Matrix* output_real) {
    // Safety checks
    if (output_real->rows != output_pred->rows || output_real->columns != output_pred->columns) {
        fprintf(stderr, "Matrix size mismatch in compute_loss_matrix\n");
        exit(EXIT_FAILURE);
    }

    double sum = 0.0;
    int total_elems = output_real->rows * output_real->columns;

    for (int row = 0; row < output_real->rows; row++)
        for (int column = 0; column < output_real->columns; column++) {
            double diff = output_real->values[row][column] - output_pred->values[row][column];
            sum += diff * diff;
        }

    return sum / total_elems;
}

//TODO! Need to fix this
void train_network(NeuralNetwork* nn, Matrix* input_data, Matrix* output_data) {
    // Feed Forward
    Matrix* bias = create_matrix(input_data->rows, nn->hidden_weights->rows);
    randomize_matrix(bias, 1);
    Matrix* hidden_layer = apply_function(sigmoid, add_matrices(dot_matrices(input_data, nn->hidden_weights), bias));
    randomize_matrix(bias, 1);
    Matrix* output_layer = apply_function(sigmoid, add_matrices(dot_matrices(hidden_layer, nn->output_weights), bias));
    
    // Loss calculations
    double ff_loss = compute_loss(output_layer, output_data);
    Matrix* output_errs = subtract_matrices(output_data, output_layer);
    Matrix* trans_mat = transpose_matrix(nn->output_weights);
    Matrix* hidden_errs = dot_matrices(trans_mat, output_errs);
    

    // Backpropagation
    nn->output_weights = add_matrices(nn->output_weights,
        scale_matrix(nn->learning_rate,
            dot_matrices(hadamard_product(output_errs, sigmoid_derivative(output_layer)),
                transpose_matrix(hidden_layer)
            )
        )
    );
    nn->hidden_weights = add_matrices(nn->hidden_weights,
        scale_matrix(nn->learning_rate,
            dot_matrices(hadamard_product(hidden_errs, sigmoid_derivative(hidden_layer)),
                transpose_matrix(input_data)
            )
        )
    );

    // Free matrices
    free_matrix(trans_mat);
    free_matrix(bias);
    free_matrix(hidden_layer);
    free_matrix(output_layer);
    free_matrix(output_errs);
    free_matrix(hidden_errs);

    // Print or store loss here
}

void train_images(NeuralNetwork* nn, Image** imgs, int batch_size) {
    for (int batch = 0; batch < batch_size; batch++) {
        printf("Img No. %d\n", batch);
        Image* img = imgs[batch];
        Matrix* input_data = flatten_matrix(img->data, 0);    // Make it column
        Matrix* output_data = create_matrix(CATEGORIES, 1);
        fill_matrix(output_data, 0); //Set the initial valies to 0
        output_data->values[img->label][0] = 1;  // Set the value 
        train_network(nn, input_data, output_data);
        free_matrix(input_data);
        free_matrix(output_data);
    }
}

Matrix* predict_network(NeuralNetwork* nn, Matrix* input_data) {
    Matrix* hidden_inputs	= dot_matrices(nn->hidden_weights, input_data);
	Matrix* hidden_outputs = apply_function(sigmoid, hidden_inputs);
	Matrix* final_inputs = dot_matrices(nn->output_weights, hidden_outputs);
	Matrix* final_outputs = apply_function(sigmoid, final_inputs);
	Matrix* result = softmax(final_outputs);

	free_matrix(hidden_inputs);
	free_matrix(hidden_outputs);
	free_matrix(final_inputs);
	free_matrix(final_outputs);

	return result;
}

Matrix* predict_image(NeuralNetwork* nn, Image* img) {
    Matrix* input_data = flatten_matrix(img->data, 0);
    Matrix* res = predict_network(nn, input_data);
    free_matrix(input_data);

    return res;
}

double predict_images(NeuralNetwork* nn, Image** imgs, int num_images) {
    int correct_n = 0;
    for (int i = 0; i < num_images; i++) {
        Matrix* pred = predict_image(nn, imgs[i]);
        if (maxidx_matrix(pred) == imgs[i]->label) correct_n++;
        free_matrix(pred);
    }

    return 100.0 * (correct_n / num_images);
}

void free_network(NeuralNetwork *nn) {
	free_matrix(nn->hidden_weights);
	free_matrix(nn->output_weights);
	free(nn);
	nn = NULL;
}