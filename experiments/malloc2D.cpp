#include <stdlib.h>
#include "malloc2D.h"

double **malloc2D(int jmax, int imax)
{
    // j = number of rows, i = number of columns
    // Implementation from Parallel and High Performance Computing (Listing 4.3)
    double **x = (double **)malloc(jmax * sizeof(double *) + jmax * imax * sizeof(double));
    x[0] = (double *)x + jmax;

    for (int j = 1; j < jmax; j++)
        x[j] = x[j - 1] + imax;

    return x;
}