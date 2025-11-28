#include "headers/matrix.h"
#include "headers/matrix_operations.h"
#include "headers/image.h"
#include "headers/activation_functions.h"
#include "headers/neural_network.h"
#include "stdio.h"

void main(void) {
    //TRAINING
	int number_imgs = 10000;
	Image** imgs = csv_to_images("./data/mnist_test.csv", number_imgs);
	NeuralNetwork* net = create_network(784, 300, 10, 0.1);
	train_images(net, imgs, number_imgs);
	// network_save(net, "testing_net");

	// PREDICTING
	int pnumber_imgs = 3000;
	Image** pimgs = csv_to_images("data/mnist_test.csv", pnumber_imgs);
	// NeuralNetwork* net = network_load("testing_net");
	double score = predict_images(net, pimgs, 1000);
	printf("Score: %1.5f\n", score);

	free_images(imgs, number_imgs);
    free_images(pimgs, pnumber_imgs);
	free_network(net);
}