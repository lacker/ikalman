#ifndef __MATRIX_H__
#define __MATRIX_H__

/* The type we use for all math. */
typedef double Number;

/* Copy a m*n matrix. */
void m_copy(Number** source, Number** destination,
	    int m, int n);

/* Pretty-print a m*n matrix. */
void m_print(Number** matrix, int m, int n);

#endif
