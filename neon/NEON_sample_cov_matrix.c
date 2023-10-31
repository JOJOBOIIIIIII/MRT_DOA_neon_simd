#include <ne10/NE10.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


int init_rand_vector(ne10_vec4f_t*);
int arr_to_vec4(ne10_float32_t* arr,int size);

int main (){
		srand(time(NULL));
		const int rows=5;
		const int columns=2048;
		const int vec_columns=columns/4; 
		const double log4_vec = log(vec_columns) / log(4); // Avoids using recursion if using 'arr_to_vec4' method

		const int n = 1; //how many times to run the test
		
		double neon_time=0;
		clock_t start_time,end_time;
        double time;
		
		//Initialize a matrix of vec4:   Each row contains 'vec_columns' size array  of vec4 values
		ne10_vec4f_t matrix_re[rows][vec_columns];
		ne10_vec4f_t matrix_im[rows][vec_columns];

		ne10_float32_t result_re[rows][rows];
		ne10_float32_t result_im[rows][rows];

		//each entry contains an array of results of vector dot products
		ne10_float32_t temp_matrix_1[rows][rows][vec_columns]; 
		ne10_float32_t temp_matrix_2[rows][rows][vec_columns]; 

		//Fills the components of each vector in the matrix with a random number (should be samples from antennas)
		for (int i=0;i<rows;i++){
				for (int j=0;j<vec_columns;j++){
						init_rand_vector(&matrix_re[i][j]);
						init_rand_vector(&matrix_im[i][j]);
				}
		}

		for (int t=0;t<n;t++){ //loop n times for testing purposes
		start_time = clock();
		//Computing the real part of the matrix
		//Compute the dot product between every pair of row (0,0 0,1 0,2 0,3 0,4    1,1 1,2 1,3 1,4   2,2 2,3 2,4 )
		ne10_float32_t sum=0;
		for (int i=0;i<rows;i++) {
				for (int j = i;j<rows;j++){
								

						if (i==0 && j ==4){
								for (int a =0;a<vec_columns;a++){
										printf("%f\n", matrix_im[i][a].y);

								}
						
						}
						//Calculate pair of the real matrix
						ne10_dot_vec4f_neon(temp_matrix_1[i][j], matrix_re[i], matrix_re[j], vec_columns);

						//Calculate pairs of the imaginary matrix
						ne10_dot_vec4f_neon(temp_matrix_2[i][j], matrix_im[i], matrix_im[j], vec_columns);
				
						//Add both dot products. 
						//ne10_add_vec4f_neon(temp_matrix_1[i][j], temp_matrix_1[i][j], temp_matrix_2[i][j], vec_columns)

						//TODO Split array in two vec4f array and add them (instead of summing like below)
						//for (int k=0;k < log4_vec ;k++){	}
						//add up every 'sub' dot product result to get the final dot product
						for (int k=0;k<vec_columns;k++){
								sum+=temp_matrix_1[i][j][k];
								sum+=temp_matrix_2[i][j][k];
						}
						sum /= columns; //divide by n samples
						result_re[i][j]=sum;
						//diagonally symmetrical
						if (i!=j) result_re[i][j] = result_re[j][i]; 
				}
				
				//Computing the imaginary part of the matrix
				for (int j = 0 ; j<rows; j++){ 
						if (i==j) result_im[i][j]=0; //diagonal is 0 for imaginary part
						else {
								//Calculate pairs of imaginary matrix and real matrix (effectively   V_im dot (V_real)^T   )
								ne10_dot_vec4f_neon( temp_matrix_1[i][j], matrix_re[i], matrix_im[j],vec_columns);
						
								for (int k=0;k<vec_columns;k++){
										sum+=temp_matrix_1[i][j][k];
								}
								sum /= rows; //divide by n samples
								result_im[i][j] = sum;
						}
				}
				for (int j= i+1; j<rows ;j++){ //loop through upper triangle only (exclude diagonal)
						result_im[i][j] -= result_im[j][i]; //result upper triangle = upper triangle - transpose of the lower triangle 
						result_im[j][i] = -result_im[i][j]; //result lower triangle = negative transpose of upper triangle
				}
		}
		
		
		end_time= clock();
		time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; neon_time += time;
		//printf("Result of vector dot product in NEON: %f in %f seconds\n", result_c,time);
		//if (t%2000==0) printf("%f\% ",(float)100*t/n);
		}
		//printf("\n");
		neon_time /= n;

		for (int i=0;i<rows;i++){
				for (int j=0;j<rows;j++){
						printf("%e\t",result_re[i][j]);
				
				}	
				printf("\n\n");
		}
		

		printf("Neon time average: %f seconds (%f ms) for a %d by %d matrix, tested %d times\n", neon_time,neon_time*1000,rows,columns,n);


		return 0;
}
 







int init_rand_vector(ne10_vec4f_t* v){
		v->x = rand() % 10 - 5 ;
		v->y = rand()% 10 - 5;
		v->z = rand()% 10 - 5;
		v->w = rand()% 10 - 5;

		return 0;
}

//unused for now
int arr_to_vec4(ne10_float32_t* arr,int size){
		ne10_vec4f_t v;
		printf("t");
		for (int i=0; i< size/2; i++){
				
				//maybe later, see if it's after

		}
		
		return 0;
}
