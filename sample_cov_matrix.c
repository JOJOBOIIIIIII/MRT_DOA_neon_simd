#include <stdio.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

#define I(x,y) (gsl_complex_rect(x,y))

int main(){
	printf("hello world\n");

	int n = 5;
	gsl_complex samples[]={ I(0,0), I(0,0) ,I(0,0), I(0,0) ,I(0,0), 
				I(0,0), I(0,0), I(0,0), I(0,0), I(0,0),
				I(0,0), I(0,0), I(0,0), I(0,0) ,I(0,0),
				I(0,0), I(0,0), I(0,0), I(0,0), I(0,0),
				I(0,0), I(0,0), I(0,0), I(0,0), I(0,0)};


	gsl_matrix_complex* matrix = gsl_matrix_complex_alloc(5,5);
		
	for (int i = 0; i < 5; i++) {
     	   for (int j = 0; j < 5; j++) {
        	    gsl_matrix_complex_set(matrix, i, j, samples[i * 5 + j]);
        	}
    	}
	
	gsl_matrix_complex* matrix_result = gsl_matrix_complex_alloc(5,5);

	//This takes the conjugate transpose according to ChatGPT
	gsl_matrix_complex *identity = gsl_matrix_complex_alloc(5, 5);
    	gsl_matrix_complex_set_identity(identity);
	gsl_blas_zgerc(gsl_complex_rect(1.0, 0.0), matrix, matrix, identity);
	
	gsl_matrix_complex *matrix_hermit = identity;

	// Complex Double (z), General (ge), Matrix Multiplication (mm)
	gsl_blas_zgemm(CblasNoTrans, CblasNoTrans, gsl_complex_rect(1.0, 0.0), matrix, matrix_hermit, gsl_complex_rect(0.0, 0.0), matrix_result);
	
//	for (int i = 0; i < n; i++)  /* OUT OF RANGE ERROR */
  //  		for (int j = 0; j < n; j++)
    //  			printf ("m(%f,%f) = \n",i,j);

	gsl_matrix_complex_free(matrix);
	gsl_matrix_complex_free(matrix_result);
	gsl_matrix_complex_free(matrix_hermit);
		
	
	return 0;

}


