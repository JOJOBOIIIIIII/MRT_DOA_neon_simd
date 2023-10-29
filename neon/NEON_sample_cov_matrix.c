#include <ne10/NE10.h>
#include <stdio.h>
#include <time.h>


int init_rand_vector(ne10_vec4f_t* v){

		v->x = rand();
		v->y = rand();
		v->z = rand();
		v->w = rand();
		return 0;
}

int main (){

		const int rows=5;
		const int columns=2048;
		const int num_4vec=columns/4; 
		
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
//-->
		ne10_vec4f_t vector1[num_vectors];
		ne10_vec4f_t vector2[num_vectors];
		ne10_float32_t result_c[num_vectors];

		//Fills the components of each vector in the arrays with a random number
		for (int i=0;i<num_vectors;i++){
				init_rand_vector(&vector1[i]);
				init_rand_vector(&vector2[i]);
		}

		for (int i=0;i<n;i++){
		start_time = clock();
		ne10_dot_vec4f_neon(result_c, vector1, vector2, num_vectors);
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
