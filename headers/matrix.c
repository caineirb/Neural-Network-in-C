#include "matrix.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 100

Matrix* create_matrix(int rows, int columns) {
    Matrix* matrix = malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->columns = columns;
    
    matrix->values = malloc(rows * sizeof(double*));
    for (int row = 0; row < rows; row++) 
        matrix->values[row] = malloc(columns * sizeof(double));

    return matrix;
}

void fill_matrix(Matrix* m, int n) {
    for (int row = 0; row < m->rows; row++) 
        for (int column = 0; column < m->columns; column++) 
            m->values[row][column] = n;  
}

void free_matrix(Matrix* m) {
    printf("Freeing the matrix...");
    for (int row = 0; row < m->rows; row++)
        free(m->values[row]);
    free(m->values);
    free(m);
    m = NULL;
    printf("Done freeing the matrix.");
}

void print_matrix(Matrix* m) {
    printf("Matrix dimensions: (%d, %d)\n", m->rows, m->columns);
    for (int row = 0; row < m->rows; row++) {
        for (int column = 0; column < m->columns; column++) 
            printf("%.4f ", m->values[row][column]);
        printf("\n");
    }
}

Matrix* copy_matrix(Matrix* m) {
    Matrix* new_m = create_matrix(m->rows, m->columns);

    for (int row = 0; row < new_m->rows; row++) 
        for (int column = 0; column < new_m->columns; column++) 
            new_m->values[row][column] = m->values[row][column];
            
    return new_m;
}

void save_matrix(Matrix* m, char* file_location) {
    FILE* save_file = fopen(file_location, "w");
    
    fprintf(save_file, "%d\n", m->rows);
    fprintf(save_file, "%d\n", m->columns);
    for (int row = 0; row < m->rows; row++) 
        for (int column = 0; column < m->columns; column++) 
            fprintf(save_file, "%.10f", m->values[row][column]);
    
    printf("Matrix successfully saved to: %s.\n", file_location);
    fclose(save_file);
}

Matrix* load_matrix(char* file_location) {
    FILE* load_file = fopen(file_location, "r");
    char line[MAXCHAR];
    fgets(line, MAXCHAR, load_file);
    int rows = atoi(line);
    fgets(line, MAXCHAR, load_file);
    int columns = atoi(line);

    Matrix* m = create_matrix(rows, columns);
    for (int row = 0; row < m->rows; row++)
        for (int column = 0; column < m->columns; column++) {
            fgets(line, MAXCHAR, load_file);
            m->values[row][column] = strtod(line, NULL);
        }
    
    printf("Matrix successfully loaded from %s.\n", file_location);
    fclose(load_file);
    return m;
}


double uniform_distribution(double low, double high) {
    double diff = high - low;
    int scale = 1000;
    int scale_diff = (int)(diff * scale);
    return low + (1.0 * (rand() % scale_diff) / scale);
}

void randomize_matrix(Matrix* m, int n) {
    double min = -1.0 / sqrt(n);
    double max = 1.0 / sqrt(n);

    for (int row = 0; row < m->rows; row++) 
        for (int column = 0; column < m->columns; column++) 
            m->values[row][column] = uniform_distribution(min, max);
}

/*
* 0 for (rows*columns, 1)
* 1 for (1, rows*columns)
*/
Matrix* flatten_matrix(Matrix* m, int axis) {
    Matrix* flat_m;

    if (axis > 1 || axis < 0) {
        printf("Arguement axis must be either 0 or 1.\n Matrix flatting failed, returning original matrix.");
        exit(EXIT_FAILURE);
    }
    flat_m = (axis == 0) ? create_matrix(m->rows*m->columns, 1) : create_matrix(1, m->rows*m->columns);

    for (int row = 0; row < m->rows; row++) {
        for (int column = 0; column < m->columns; column++) {
            if (axis == 0) flat_m->values[(m->columns * row) + column][0] = m->values[row][column];
            else flat_m->values[0][(m->columns * row) + column] = m->values[row][column];
        }
    }

    return flat_m;
}

/*
    Use the flattened matrix.
*/
int maxidx_matrix(Matrix* m) {
    int maxidx = 0;
    int matrix_size = (m->columns == 1) ? m->rows : m->columns;

    for (int idx = 0; idx < matrix_size; idx++) {
        if (m->values[idx] > m->values[maxidx]) {
            maxidx = idx;
        }
    }

    return maxidx;
}