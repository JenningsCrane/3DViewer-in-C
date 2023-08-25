#include "parser.h"

void translate(float num_x, float *num_last_x, float num_y, float *num_last_y,
               float num_z, float *num_last_z, int size_v, float *v) {
  float dx = num_x - (*num_last_x);
  float dy = num_y - (*num_last_y);
  float dz = num_z - (*num_last_z);

  float matrixAff[] = {1, 0, 0, dx, 0, 1, 0, dy, 0, 0, 1, dz, 0, 0, 0, 1};

  for (int i = 0; i < size_v; i += 3) {
    v[i] = matrixAff[0] * v[i] + matrixAff[1] * v[i + 1] +
           matrixAff[2] * v[i + 2] + matrixAff[3] * 1;
    v[i + 1] = matrixAff[4] * v[i] + matrixAff[5] * v[i + 1] +
               matrixAff[6] * v[i + 2] + matrixAff[7] * 1;
    v[i + 2] = matrixAff[8] * v[i] + matrixAff[9] * v[i + 1] +
               matrixAff[10] * v[i + 2] + matrixAff[11] * 1;
  }

  *num_last_x = num_x;
  *num_last_y = num_y;
  *num_last_z = num_z;
}

void rotationOx(float num_x, float *num_last_x, int size_v, float *v) {
  float dx = num_x - (*num_last_x);
  float matrixX[] = {1, 0, 0, 0, cos(dx), -sin(dx), 0, sin(dx), cos(dx)};
  rotateArr(size_v, v, matrixX);
  *num_last_x = num_x;
}

void rotationOy(float num_y, float *num_last_y, int size_v, float *v) {
  float dy = num_y - (*num_last_y);
  float matrixY[] = {cos(dy), 0, sin(dy), 0, 1, 0, -sin(dy), 0, cos(dy)};
  rotateArr(size_v, v, matrixY);
  *num_last_y = num_y;
}

void rotationOz(float num_z, float *num_last_z, int size_v, float *v) {
  float dz = num_z - (*num_last_z);
  float matrixZ[] = {cos(dz), -sin(dz), 0, sin(dz), cos(dz), 0, 0, 0, 1};
  rotateArr(size_v, v, matrixZ);
  *num_last_z = num_z;
}

void rotateArr(int size_v, float *v, float matrix[]) {
  for (int i = 0; i < size_v; i += 3) {
    float tmp_x = v[i];
    float tmp_y = v[i + 1];
    float tmp_z = v[i + 2];
    v[i] = matrix[0] * tmp_x + matrix[1] * tmp_y + matrix[2] * tmp_z;
    v[i + 1] = matrix[3] * tmp_x + matrix[4] * tmp_y + matrix[5] * tmp_z;
    v[i + 2] = matrix[6] * tmp_x + matrix[7] * tmp_y + matrix[8] * tmp_z;
  }
}

void scale(float num, float *num_last, int size_v, float *v) {
  float tmp = num - (*num_last);
  for (int i = 0; i < size_v && tmp != 0; i++) v[i] *= tmp + 1;
  *num_last = num;
}

/* центрирование объекта*/
void center(int size_v, float *v, float *max_x, float *min_x, float *max_y,
            float *min_y, float *max_z, float *min_z) {
  maxMin(size_v, v, max_x, min_x, max_y, min_y, max_z, min_z);
  float center_x = *min_x + (*max_x - *min_x) / 2.0;
  float center_y = *min_y + (*max_y - *min_y) / 2.0;
  float center_z = *min_z + (*max_z - *min_z) / 2.0;

  for (int i = 0; i < size_v; i += 3) {
    v[i] -= center_x;
    v[i + 1] -= center_y;
    v[i + 2] -= center_z;
  }
}

void objectReduct(int size_v, float *v, float *max_x, float *min_x,
                  float *max_y, float *min_y, float *max_z, float *min_z) {
  maxMin(size_v, v, max_x, min_x, max_y, min_y, max_z, min_z);
  float max = fmax(fmax(*max_x - *min_x, *max_y - *min_y), *max_z - *min_z);
  float scale_obj = 1 / max;
  for (int i = 0; i < size_v; i++) v[i] *= scale_obj;
}

void maxMin(int size_v, float *v, float *max_x, float *min_x, float *max_y,
            float *min_y, float *max_z, float *min_z) {
  *max_x = 0.0, *min_x = 0.0, *max_y = 0.0, *min_y = 0.0, *max_z = 0.0,
  *min_z = 0.0;
  for (int i = 0; i < size_v; i += 3) {
    if (v[i] > *max_x)
      *max_x = v[i];
    else if (v[i] < *min_x)
      *min_x = v[i];

    if (v[i + 1] > *max_y)
      *max_y = v[i + 1];
    else if (v[i + 1] < *min_y)
      *min_y = v[i + 1];

    if (v[i + 2] > *max_z)
      *max_z = v[i + 2];
    else if (v[i + 2] < *min_z)
      *min_z = v[i + 2];
  }
}
