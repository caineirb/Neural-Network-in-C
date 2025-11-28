/*
    Matrix structure and functions declaration.
*/

#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    double** values;
    int rows;
    int columns;
} Matrix;

Matrix* create_matrix(int rows, int columns);
void fill_matrix(Matrix* m, int n);
void free_matrix(Matrix* m);
void print_matrix(Matrix* m);
Matrix* copy_matrix(Matrix* m);
void save_matrix(Matrix* m, char* file_path);
Matrix* load_matrix(char* file_path);
void randomize_matrix(Matrix* m, int n);
Matrix* flatten_matrix(Matrix* m, int axis);
int maxidx_matrix(Matrix* m);

#endif //MATRIX_H