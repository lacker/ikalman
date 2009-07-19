#ifndef __MATRIX_H__
#define __MATRIX_H__

typedef struct {
  /* Dimensions */
  int rows;
  int cols;

  /* Contents of the matrix */
  double** data;
} Matrix;

/* Allocate memory for a new matrix.
   Zeros out the matrix.
   Assert-fails if we are out of memory.
*/
Matrix alloc_matrix(int rows, int cols);

/* Free memory for a matrix. */
void free_matrix(Matrix m);

/* Copy a matrix. */
void copy_matrix(Matrix source, Matrix destination);

/* Pretty-print a matrix. */
void print_matrix(Matrix m);

#endif
