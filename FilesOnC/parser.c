#include "parser.h"

int writing_data(FILE *file, float **v, unsigned int **f) {
  int fail = 0, count_v = 0, count_f = 0, poly = 0, temp = 0, i = 0;
  char tline[256] = {0};
  char *token = NULL;
  float x = 0, y = 0, z = 0;
  while (fail == 0 && fgets(tline, sizeof(tline), file)) {
    if (tline[0] == 'v' && tline[1] == ' ') {
      x = y = z = 0;
      sscanf(tline, "v %f %f %f", &x, &y, &z);
      (*v)[count_v] = x;
      (*v)[count_v + 1] = y;
      (*v)[count_v + 2] = z;
      count_v += 3;
    } else if (tline[0] == 'f') {
      temp = 0;
      poly = 0;
      tline[0] = ' ';
      token = strtok(tline, " ");
      for (i = 0; token != NULL; i++) {
        if (tline[3] == '/') {
          sscanf(token, "%d/%*d/%*d", &poly);
        } else {
          sscanf(token, "%d", &poly);
        }
        if ((token = strtok(NULL, " ")) == 0) {
          (*f)[count_f] = poly - 1;
          (*f)[count_f + 1] = poly - 1;
          (*f)[count_f + 2] = temp - 1;
          count_f += 3;
        } else if (i == 0) {
          (*f)[count_f] = poly - 1;
          count_f++;
          temp = poly;
        } else if (strcmp(token, "\n") != 0) {
          (*f)[count_f] = poly - 1;
          (*f)[count_f + 1] = poly - 1;
          count_f += 2;
        }
      }
    }
  }
  return 0;
}

int read_file(FILE *file, float **v, unsigned int **f, int *size_v,
              int *size_f) {
  int fail = 0, i = 0;
  char tline[256] = {0};
  char *token = NULL;
  *size_v = 0;
  *size_f = 0;
  while (fgets(tline, sizeof(tline), file)) {
    if (tline[0] == 'v' && tline[1] == ' ') {
      (*size_v) += 3;
    } else if (tline[0] == 'f') {
      tline[0] = ' ';
      token = strtok(tline, " ");
      for (i = 0; token != NULL; i++) {
        if (tline[3] == '/')
          sscanf(token, "%*d/%*d/%*d");
        else
          sscanf(token, "%*d");
        if (strcmp(token, "\n") != 0) (*size_f) += 2;
        token = strtok(NULL, " ");
      }
    }
  }
  rewind(file);
  *v = (float *)malloc(*size_v * sizeof(float));
  *f = (unsigned int *)malloc(*size_f * sizeof(unsigned int));
  if ((*v) == NULL || (*f) == NULL) {
    fail = 1;
    fprintf(stderr, "Error 1.2: Memmory not allocated!\n");
  } else {
    fail = writing_data(file, v, f);
  }

  return fail;
}

int open_file(const char *name_file, float **v, unsigned int **f, int *size_v,
              int *size_f) {
  int fail = 0;
  FILE *file = fopen(name_file, "r");
  if (!file) {
    fail = 1;
  } else {
    if (*v) free(*v);
    if (*f) free(*f);
    fail = read_file(file, v, f, size_v, size_f);
  }
  fclose(file);

  return fail;
}
