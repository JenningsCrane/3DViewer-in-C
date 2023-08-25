#include <check.h>
#include <stdbool.h>
#include <stdlib.h>

#include "../FilesOnC/parser.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define EPS 1e-5f
#define ERR_NONE 0

START_TEST(load_test_1) {
  int size_v = 0;
  int size_f = 0;

  float* v = NULL;
  unsigned int* f = NULL;

  int err = open_file("model/cube.obj", &v, &f, &size_v, &size_f);

  ck_assert_int_eq(err, ERR_NONE);

  ck_assert_ptr_ne(v, NULL);
  ck_assert_ptr_ne(f, NULL);
  ck_assert_int_eq(size_v, 24);
  ck_assert_int_eq(size_f, 72);
  float test_v[] = {1.0, -1.0,     -1.0, 1.0,  -1.0, 1.0,  -1.0,      -1.0,
                    1.0, -1.0,     -1.0, -1.0, 1.0,  1.0,  -0.999999, 0.999999,
                    1.0, 1.000001, -1.0, 1.0,  1.0,  -1.0, 1.0,       -1.0};
  unsigned int test_f[] = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
  for (int i = 0; i < 24; i++) ck_assert_float_eq_tol(v[i], test_v[i], EPS);

  for (int j = 0; j < 72; j++) ck_assert_float_eq_tol(f[j], test_f[j], EPS);

  if (v != NULL) free(v);
  if (f != NULL) free(f);
}
END_TEST

START_TEST(load_test_2) {
  int size_v = 0, size_f = 0;
  float* v = NULL;
  unsigned int* f = NULL;
  int err = open_file("model/Ball_OBJ.obj", &v, &f, &size_v, &size_f);

  ck_assert_int_eq(err, ERR_NONE);
  ck_assert_int_eq(size_v, 46986);
  ck_assert_int_eq(size_f, 182520);

  if (v != NULL) free(v);
  if (f != NULL) free(f);
}
END_TEST

START_TEST(load_test_3) {
  int size_v = 0, size_f = 0;
  float* v = NULL;
  unsigned int* f = NULL;
  int err = open_file("model/Datsun_280Z.obj", &v, &f, &size_v, &size_f);

  ck_assert_int_eq(err, ERR_NONE);
  ck_assert_int_eq(size_v, 177324);
  ck_assert_int_eq(size_f, 520016);

  if (v != NULL) free(v);
  if (f != NULL) free(f);
}
END_TEST

START_TEST(afin_test_1) {
  float x = -2.0f;
  float y = 0.0f;
  float z = 0.0f;
  float num_last_x = 0.0f;
  float num_last_y = 0.0f;
  float num_last_z = 0.0f;

  float v[] = {1.0f, 0.0f, 0.0f};
  int size_v = 3;

  translate(x, &num_last_x, y, &num_last_y, z, &num_last_z, size_v, v);

  ck_assert_float_eq_tol(v[0], -1.0f, EPS);
  ck_assert_float_eq_tol(v[1], 0.0f, EPS);
  ck_assert_float_eq_tol(v[2], 0.0f, EPS);
}
END_TEST

START_TEST(afin_test_2) {
  float y = 90.0f;
  float num_last_y = 0.0f;

  float v[] = {1.0, 0.0f, 0.0f};
  int size_v = 3;

  rotationOy(y, &num_last_y, size_v, v);

  ck_assert_float_eq_tol(v[0], -0.448074, EPS);
  ck_assert_float_eq_tol(v[1], 0.0, EPS);
  ck_assert_float_eq_tol(v[2], -0.893997, EPS);
}
END_TEST

START_TEST(afin_test_3) {
  float num = 2.0f;
  float num_last = 1.0f;

  float v[] = {1.0f, 0.0f, 0.0f};
  int size_v = 3;
  scale(num, &num_last, size_v, v);

  ck_assert_float_eq_tol(v[0], 2.0f, EPS);
  ck_assert_float_eq_tol(v[1], 0.0f, EPS);
  ck_assert_float_eq_tol(v[2], 0.0f, EPS);
}
END_TEST

START_TEST(afin_test_4) {
  int size_v = 0;
  int size_f = 0;
  float* v = NULL;
  unsigned int* f = NULL;
  int err = open_file("model/cube.obj", &v, &f, &size_v, &size_f);
  ck_assert_int_eq(err, ERR_NONE);
  float num = 1.5;
  float num_last = 1.2;
  rotationOx(num, &num_last, size_v, v);

  float test_v[] = {1.000000,  -0.659816, -1.250857, 1.000000,  -1.250857,
                    0.659816,  -1.000000, -1.250857, 0.659816,  -1.000000,
                    -0.659816, -1.250857, 1.000000,  1.250856,  -0.659815,
                    0.999999,  0.659816,  1.250858,  -1.000000, 0.659816,
                    1.250857,  -1.000000, 1.250857,  -0.659816};

  unsigned int test_f[] = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};

  for (int i = 0; i < size_v; i++) {
    ck_assert_float_eq_tol(v[i], test_v[i], EPS);
  }

  for (int j = 0; j < size_f; j++) {
    ck_assert_float_eq_tol(f[j], test_f[j], EPS);
  }
  if (v != NULL) free(v);
  if (f != NULL) free(f);
}
END_TEST

START_TEST(afin_test_5) {
  int size_v = 0;
  int size_f = 0;
  float* v = NULL;
  unsigned int* f = NULL;
  int err = open_file("model/cube.obj", &v, &f, &size_v, &size_f);
  ck_assert_int_eq(err, ERR_NONE);
  float num = 1.5;
  float num_last = 1.2;
  rotationOz(num, &num_last, size_v, v);

  float test_v[] = {1.250857,  -0.659816, -1.000000, 1.250857,  -0.659816,
                    1.000000,  -0.659816, -1.250857, 1.000000,  -0.659816,
                    -1.250857, -1.000000, 0.659816,  1.250857,  -0.999999,
                    0.659815,  1.250856,  1.000001,  -1.250857, 0.659816,
                    1.000000,  -1.250857, 0.659816,  -1.000000};

  unsigned int test_f[] = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};

  for (int i = 0; i < size_v; i++) {
    ck_assert_float_eq_tol(v[i], test_v[i], EPS);
  }

  for (int j = 0; j < size_f; j++) {
    ck_assert_float_eq_tol(f[j], test_f[j], EPS);
  }
  if (v != NULL) free(v);
  if (f != NULL) free(f);
}
END_TEST

START_TEST(afin_test_6) {
  int size_v = 0;
  int size_f = 0;
  float* v = NULL;
  unsigned int* f = NULL;
  int err = open_file("model/cube.obj", &v, &f, &size_v, &size_f);
  ck_assert_int_eq(err, ERR_NONE);
  float num = 1.5;
  float num_last = 1.2;
  rotationOz(num, &num_last, size_v, v);
  num -= 0.23;
  rotationOx(num, &num_last, size_v, v);
  num -= 0.2;
  rotationOz(num, &num_last, size_v, v);

  float max_x = 0, min_x = 0, max_y = 0, min_y = 0, max_z = 0, min_z = 0;

  center(size_v, v, &max_x, &min_x, &max_y, &min_y, &max_z, &min_z);

  float test_v[] = {
      1.052997,  -1.101575, -0.823244, 1.143582,  -0.654709, 1.124089,
      -0.843335, -0.839121, 1.258833,  -0.933919, -1.285988, -0.688500,
      0.843335,  0.839121,  -1.258833, 0.933918,  1.285988,  0.688500,
      -1.052997, 1.101575,  0.823242,  -1.143582, 0.654709,  -1.124090,
      1.052997,  -1.101575, -0.823243, 1.143582,  -0.654709, 1.124090,
      -0.843335, -0.839121, 1.258834,  -0.933919, -1.285988, -0.688499,
      0.843335,  0.839122,  -1.258833, 0.933918,  1.285988,  0.688500,
      -1.052997, 1.101575,  0.823243,  -1.143582, 0.654709,  -1.124090};

  unsigned int test_f[] = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};

  for (int i = 0; i < size_v; i++) {
    ck_assert_float_eq_tol(v[i], test_v[i], EPS);
  }

  for (int j = 0; j < size_f; j++) {
    ck_assert_float_eq_tol(f[j], test_f[j], EPS);
  }
  if (v != NULL) free(v);
  if (f != NULL) free(f);
}
END_TEST

START_TEST(afin_test_7) {
  int size_v = 0;
  int size_f = 0;
  float* v = NULL;
  unsigned int* f = NULL;
  int err = open_file("model/cube.obj", &v, &f, &size_v, &size_f);

  ck_assert_int_eq(err, ERR_NONE);
  float num = 1.5;
  float num_last = 1.2;
  rotationOz(num, &num_last, size_v, v);
  num -= 0.123;
  rotationOx(num, &num_last, size_v, v);
  num -= 10.0;
  rotationOz(num, &num_last, size_v, v);

  float max_x = 0, min_x = 0, max_y = 0, min_y = 0, max_z = 0, min_z = 0;
  objectReduct(size_v, v, &max_x, &min_x, &max_y, &min_y, &max_z, &min_z);

  float test_v[] = {-0.235042, 0.500000,  -0.341924, -0.285118, 0.422765,
                    0.402659,  0.435985,  0.217471,  0.429861,  0.486061,
                    0.294706,  -0.314721, -0.435985, -0.217471, -0.429860,
                    -0.486061, -0.294706, 0.314722,  0.235042,  -0.500000,
                    0.341924,  0.285118,  -0.422765, -0.402659};

  unsigned int test_f[] = {
      1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5,
      2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4,
      0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};

  for (int i = 0; i < size_v; i++) {
    ck_assert_float_eq_tol(v[i], test_v[i], EPS);
  }

  for (int j = 0; j < size_f; j++) {
    ck_assert_float_eq_tol(f[j], test_f[j], EPS);
  }
  if (v != NULL) free(v);
  if (f != NULL) free(f);
}
END_TEST

Suite* Viewer() {
  Suite* s = suite_create("UnrealTeam");
  TCase* tc_load = tcase_create("Load");
  TCase* tc_afin = tcase_create("Afin");

  tcase_add_test(tc_load, load_test_1);
  tcase_add_test(tc_load, load_test_2);
  tcase_add_test(tc_load, load_test_3);

  tcase_add_test(tc_afin, afin_test_1);
  tcase_add_test(tc_afin, afin_test_2);
  tcase_add_test(tc_afin, afin_test_3);
  tcase_add_test(tc_afin, afin_test_4);
  tcase_add_test(tc_afin, afin_test_5);
  tcase_add_test(tc_afin, afin_test_6);
  tcase_add_test(tc_afin, afin_test_7);

  suite_add_tcase(s, tc_load);
  suite_add_tcase(s, tc_afin);

  return s;
}

void run_testcase(Suite* testcase) {
  SRunner* sr = srunner_create(testcase);

  putchar('\n');

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
}

int main() {
  run_testcase(Viewer());

  return 0;
}