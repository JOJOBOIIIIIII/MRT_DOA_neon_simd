#include <ne10/NE10.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int init_rand_vector(ne10_vec4f_t* v){

		v->x = rand();
		v->y = rand();
		v->z = rand();
		v->w = rand();
		return 0;
}

int to_vec4(ne_10_float32_t* arr, size){
		ne10_vec4f_t v;

		v.x=arr[0]

		
		return
}

int main (){

		const int rows=5;
		const int columns=2048;
		const int vec_columns=columns/4; 
		const double log4_vec = log(vec_columns) / log(4) // Avoids using recursion

		const int n = 1; //how many times to run the test
		
		double neon_time=0;
		clock_t start_time,end_time;
        double time;
		
		//initialize ne10 library
		if (ne10_init() != NE10_OK ) {
				fprintf(stderr, "Failed to initialise Ne10.\n");
				return 1;
		}
		printf("success\n");

		//Initialize a matrix of vec4:   Each row contains 'vec_columns' size array  of vec4 values
		ne10_vec4f_t matrix_re[rows][vec_columns];
		ne10_vec4f_t matrix_im[rows][vec_columns];

		ne10_float32_t result_re[rows][rows];
		ne10_float32_t result_im[rows][rows];
		ne10_float32_t temp_matrix[rows][rows]; //for 2-steps calculations


		//Fills the components of each vector in the matrix with a random number (should be samples from antennas)
		for (int i=0;i<rows;i++){
				for (int j=0,j<vec_columns;j++){
						init_rand_vector(&matrix_re[i][j]);
						init_rand_vector(&matrix_im[i][j]);
				}
		}

		for (int t=0;i<n;t++){ //loop n times for testing purposes
		start_time = clock();
		
		//Computing the real part of the matrix
		//Compute the dot product between every pair of row (0,0 0,1 0,2 0,3 0,4    1,1 1,2 1,3 1,4   2,2 2,3 2,4 )
		sum_arr
		for (int i=0;i<rows;i++) {
				for (int j = i;j<rows;i++){
						//Calculate pair for real matrix
						ne10_dot_vec4f_neon(result_re[i][j], matrix_re[i], matrix_re[j], num_vectors);

						//Calculate pair for imaginary matrix
						ne10_dot_vec4f_neon(temp_matrix[i][j], matrix_im[i], matrix_im[j], num_vectors);
						
						//Add both dot products. 
						ne10_add_vec4f_neon(sum_arr, result_re[i][j], temp_matrix[i][j], num_vectors)

						//Split array in two vec4f array and add them
						for (int k=0;k < log4_vec ;k++){
								
								ne10_setc_vec4f_neon(sum_arr);
								
						
						}
						
						//diagonally symmetrical
						if (i!=j) result[i][j] = result[j][i]; 
				}
		}
		
		
		end_time= clock();
		time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; neon_time += time;
		//printf("Result of vector dot product in NEON: %f in %f seconds\n", result_c,time);
		}
		
		neon_time /= n;
		printf("Neon time average: %f seconds (%f ms) for %d 4fvectors, tested %d times\n", neon_time,neon_time*1000,num_vectors,n);

//ASM not recognized
//		ne10_dot_vec4f_asm(&result_c, &vector1, &vector2, 1);
//		printf("Result of vector dot product in ASM: %f\n", result_c);

		return 0;
}




int 







