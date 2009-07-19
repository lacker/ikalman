/* Matrix math. */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

void m_copy(Number** source, Number** destination,
	    int m, int n) {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      destination[i][j] = source[i][j];
    }
  }
}

void m_print(Number** matrix, int m, int n) {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j > 0) {
	printf(" ");
      }
      printf("6.2f", matrix[i][j]);
    }
    printf("\n");
  }
}
