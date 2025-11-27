#include "image.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define MAXCHAR 10000
#define IMAGE_ROWS 28
#define IMAGE_COLUMNS 28

Image** csv_to_images(char* file_location, int num_images) {
    FILE* file;
    Image** imgs = malloc(num_images * sizeof(Image*));
    char row[MAXCHAR];
    
    file = fopen(file_location, "r");
    fgets(row, MAXCHAR, file);
    int r = 0;
    while(feof(file) != 1 && r < num_images) {
        imgs[r] = malloc(sizeof(Image));

        int c = 0;
        fgets(row, MAXCHAR, file);
        char* token = strtok(row, ",");
        imgs[r]->data = create_matrix(IMAGE_ROWS,IMAGE_COLUMNS);
        while (token != NULL) {
            if (c == 0) imgs[r]->label = atoi(token);
            else imgs[r]->data->values[(c-1)/IMAGE_ROWS][(c-1)%IMAGE_COLUMNS] = atoi(token) / 256.0;
            token = strtok(NULL, ",");
            c++;
        }
        r++;
    }

    fclose(file);
    return imgs;
}

void print_image(Image* img) {
    printf("Image label: %d\n", img->label);
    print_matrix(img->data);
}

void free_image(Image* img) {
    free_matrix(img->data);
    free(img);
    img = NULL;
}

void free_images(Image** imgs, int num_images) {
    for (int idx = 0; idx < num_images; idx++)
        free_image(imgs[idx]);
    free(imgs);
    imgs = NULL;
}