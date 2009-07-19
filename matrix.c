/* Matrix math. */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/* This could be reduced to a single malloc if it mattered. */
Matrix alloc_matrix(int rows, int cols) {
  Matrix m;
  m.rows = rows;
  m.cols = cols;
  m.data = (double**) malloc(sizeof(double*) * m.rows);
  for (int i = 0; i < m.rows; ++i) {
    m.data[i] = (double*) malloc(sizeof(double) * m.cols);
    assert(m.data[i]);
    for (int j = 0; j < m.cols; ++j) {
      m.data[i][j] = 0.0;
    }
  }
  return m;
}

void free_matrix(Matrix m) {
  for (int i = 0; i < m.rows; ++i) {
    free(m.data[i]);
  }
  free(m.data);
}

void copy_matrix(Matrix source, Matrix destination) {
  assert(source.rows == destination.rows);
  assert(source.cols == destination.cols);
  for (int i = 0; i < source.rows; ++i) {
    for (int j = 0; j < source.cols; ++j) {
      destination.data[i][j] = source.data[i][j];
    }
  }
}

void print_matrix(Matrix m) {
  for (int i = 0; i < m.rows; ++i) {
    for (int j = 0; j < m.cols; ++j) {
      if (j > 0) {
	printf(" ");
      }
      printf("%6.2f", m.data[i][j]);
    }
    printf("\n");
  }
}
