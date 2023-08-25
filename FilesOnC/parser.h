#ifndef PARSER_H
#define PARSER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int writing_data(FILE *file, float **v, unsigned int **f);
int read_file(FILE *file, float **v, unsigned int **f, int *size_v,
              int *size_f);
int open_file(const char *name_file, float **v, unsigned int **f, int *size_v,
              int *size_f);
void translate(float num_x, float *num_last_x, float num_y, float *num_last_y,
               float num_z, float *num_last_z, int size_v, float *v);

void rotationOx(float num_x, float *num_last_x, int size_v, float *v);
void rotationOy(float num_y, float *num_last_y, int size_v, float *v);
void rotationOz(float num_z, float *num_last_z, int size_v, float *v);
void rotateArr(int size_v, float *v, float matrix[]);

void scale(float num, float *num_last, int size_v, float *v);
void center(int size_v, float *v, float *max_x, float *min_x, float *max_y,
            float *min_y, float *max_z, float *min_z);
void objectReduct(int size_v, float *v, float *max_x, float *min_x,
                  float *max_y, float *min_y, float *max_z, float *min_z);
void maxMin(int size_v, float *v, float *max_x, float *min_x, float *max_y,
            float *min_y, float *max_z, float *min_z);

#endif  // PARSER_H
