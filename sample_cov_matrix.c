#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

//Could be done simpler/shorter with blas, because it can add operators and constant to matrices when multiplying, in one line


int main(){
	printf("hello ha world\n");

	int n = 5;

	double samples_re[] = { 0,0,0,0,0,
				0,0,0,0,0,
				0,0,0,0,0,
				0,0,0,0,0,
				0,0,0,0,0
				}

	double samples_im[] = { 0,0,0,0,0,
				0,0,0,0,0,
				0,0,0,0,0,
				0,0,0,0,0,
				0,0,0,0,0
				}


	gsl_matrix* matrix_sample_re = gsl_matrix_alloc(5,5);
	gsl_matrix* matrix_sample_im = gsl_matrix_alloc(5,5);


	for (int i = 0; i < 5; i++) {
     	   for (int j = 0; j < 5; j++) {
        	
	   }
    	}

	gsl_matrix* matrix_hermit_re = gsl_matrix_alloc(5,5); 
	gsl_matrix_transpose_memcpy(matrix_hermit_re, matrix_sample_re); // Transpose real part

	gsl_matrix* matrix_hermit_im = gsl_matrix_alloc(5,5);
	gsl_matrix_transpose_memcpy(matrix_hermit_im, matrix_sample_im); //Transpose imaginary part
	gsl_matrix_scale(matrix_hermit_im, -1); //Flip imaginary part

	// d: type double, ge: general , mm: matrix multiplication. Result stored in 'C' (last argument)
	gsl_matrix* result_re = gsl_matrix_alloc(5,5); 
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, matrix_sample_re,matrix_hermit_re,0,result_re);

	//                                        subtract                             from previous
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, -1, matrix_sample_im,matrix_hermit_im,1,result_re);
	


	gsl_matrix* result_im = gsl_matrix_alloc(5,5);
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, matrix_sample_re,matrix_hermit_im,0,result_im);
	
	//                                        add                             to previous
	gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, matrix_sample_im,matrix_hermit_re,1,result_im);
		
	//Divide results by n: number of samples
	double scale = 1./n;
	gsl_matrix_scale(result_im, scale);
	gsl_matrix_scale(result_re, scale);



	
	return 1;

}


