#include <stdio.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <time.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>

double main(int argc, char* argv[]){
	
	int do_print=1;
	if (argc > 1) { //if an argument is passed, dont print (for the python script)
        	do_print=0;
    	}

	clock_t start_time,end_time;
	double elapsed_time;

	if (do_print) printf("Computing the covariance matrix...\n");
		
		//GSL random number generator
		gsl_rng_env_setup();
		const gsl_rng_type *T = gsl_rng_default;
		gsl_rng *r = gsl_rng_alloc(T);
		gsl_rng_set(r, time(NULL));

	int num_samples=5;
	int data_per_sample=2048;
/*
	double samples_re[] = { 0,0,3,0,0,
				0,0,0,0,-2,
				0,0,54,0,3,
				0,0,0,0,0,
				43,0,1,0,4
				};

	double samples_im[] = { 0,0,22,0,0,
				-5,0,110,0,0,
				0,0,-3,0,0,
				0,0,0,0,33,
				0,0,32,0,0
				};
*/
	gsl_matrix* matrix_sample_re = gsl_matrix_alloc(num_samples,data_per_sample);
	gsl_matrix* matrix_sample_im = gsl_matrix_alloc(num_samples,data_per_sample);

	//Set the values in the martix accoring to the samples in the array
	for (int i = 0; i < num_samples; i++) {
     	   for (int j = 0; j < data_per_sample; j++) {
				double random_value = gsl_ran_flat(r, -5, 5);
				 gsl_matrix_set(matrix_sample_re, i, j, random_value);
				random_value = gsl_ran_flat(r,-5 , 5);
				 gsl_matrix_set(matrix_sample_im, i, j, random_value);
	   }
    	}
	gsl_matrix* result_re = gsl_matrix_alloc(num_samples,num_samples); 
	gsl_matrix* result_im = gsl_matrix_alloc(num_samples,num_samples);

	start_time=clock();
	// d: type double, ge: general , mm: matrix multiplication. Result stored in 'C' (last argument)
	//
	//
	//             Real        hermitian of real  add                                  result not initialized, dont add it
	gsl_blas_dgemm(CblasNoTrans, CblasConjTrans, 1, matrix_sample_re,matrix_sample_re,0,result_re);
	//               Im      Hermitian of im   subtract                             from previous results
	gsl_blas_dgemm(CblasNoTrans, CblasConjTrans, 1, matrix_sample_im,matrix_sample_im,1,result_re);
	
	//                real      hermitian of im                    			  dont add: result not initialized
	gsl_blas_dgemm(CblasNoTrans, CblasConjTrans, -1, matrix_sample_re,matrix_sample_im,0,result_im);
	
	//                 im    hermitian of real  add                                to previous result
	gsl_blas_dgemm(CblasNoTrans, CblasConjTrans, 1, matrix_sample_im,matrix_sample_re,1,result_im);
		
	//Divide results by n: number of samples
	double scale = 1./data_per_sample;
	gsl_matrix_scale(result_im, scale);
	gsl_matrix_scale(result_re, scale);

	end_time=clock();
	elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

	//Print the matrix if do_print is true
	
	if (do_print){
	printf("Matrix result:\n");
	for (int i = 0; i < num_samples; i++) {
    		for (int j = 0; j < num_samples; j++) {
        		double num_re = gsl_matrix_get(result_re, i, j);
        		double num_im = gsl_matrix_get(result_im, i, j);
        		printf("%f ", num_re);
			printf("%f", num_im);
			printf("i\t");


    		}
    	printf("\n"); // Move to the next row
	}
	
	printf("\nElapsed time: %f seconds\n", elapsed_time);
	} //end of do_print if

	FILE* file = fopen("times.txt","a");
	if (file == NULL) return 1;
	fprintf(file,"%lf\n",elapsed_time);
	fclose(file);

		gsl_matrix_free(matrix_sample_re);
		gsl_matrix_free(matrix_sample_im);
		gsl_matrix_free(result_im);
		gsl_matrix_free(result_re);
		gsl_rng_free(r);
	return 0;

}


