#ifndef IMAGE_H
#define IMAGE_H

#include "matrix.h"

typedef struct {
    Matrix* data;
    int label;
} Image;

Image** csv_to_images(char* file_location, int num_images);
void print_image(Image* img);
void free_image(Image* img);
void free_images(Image** imgs, int num_images);

#endif //IMAGE_H