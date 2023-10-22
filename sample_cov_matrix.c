#include <stdio.h>
#include <gsl/gsl_matrix.h>

typedef gsl_matrix mat;

int main(){
	printf("hello world\n");

	int n = 5;
	int re_samples[5]={10,20,30,155,1000};
	int im_samples[5]={15,54,100,200,124};

	mat *matrix = gsl_matrix_alloc(3,3);
	double value = gsl_matrix_get(matrix,1,1);
	printf("value is %.1f", value);

	gsl_matrix_free(matrix);
		
	
	return 0;

}


