#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>

//Code inspired by the GSL documentation section 'eigensystems', in examples
//Modified to use hermitian matrices and compute eigen vectors

gsl_matrix_complex compute_eigen_vector(gsl_matrix_complex* src, gsl_matrix_complex* dest,  int size){

 //Matrix where the eigen vectors will be stored
 gsl_matrix_complex* evec = gsl_matrix_complex_alloc(size,size);
 //Vector where the eigen values will be stored
 gsl_vector_complex* eval = gsl_vector_complex_alloc(size)

 //hermv : 'herm' for hermitian. 'v' for vectors (compute eigen vectors, not just eigen values))
 gsl_eigen_hermv_workspace* w =gsl_eigen_herm_alloc (size);
 gsl_eigen_hermv(&m.matrix, eval, evec, w); //This computes the eigen values & vectors
 gsl_eigen_hermv_free (w);
  
 //sort in ascending order, according to vector magnitude (last one is biggest and will be removed))
 // use VAL instead of ABS to use eigen values 
 gsl_eigen_hermv_sort(eval, evec, GSL_EIGEN_SORT_ABS_ASC)

 //Print eigen value and eigen vector for each
 for (int i = 0; i < size; i++) {
        double eval_i = gsl_vector_get (eval, i);
        gsl_vector_view evec_i = gsl_matrix_column (evec, i);

        printf ("eigenvalue = %g\n", eval_i);
        printf ("eigenvector = \n");
        gsl_vector_fprintf (stdout, &evec_i.vector, "%g");
 }

 //TODO remove last colums or rows, which is the biggest vector and our noise signal

 gsl_vector_free (eval);
 gsl_matrix_free (evec);

 return 0;
}

