#include <ne10/NE10.h>
#include <stdio.h>
#include <time.h>

//Referring to example code of ne10 doxygen : matrix multiplication

//each vector 4f has x,y,z,w
//to initialize do vector.x = ...
//you can have an array of vector4f


int init_rand_vector(ne10_vec4f_t* v){

		v->x = rand();
		v->y = rand();
		v->z = rand();
		v->w = rand();
		return 0;
}

int main (){

		const int num_vectors=2560;
		
		const int n = 1000000;
		double c_time=0;
		double neon_time=0;

		clock_t start_time,end_time;
        double time;

		if (ne10_init() != NE10_OK ) {
				fprintf(stderr, "Failed to initialise Ne10.\n");
				return 1;
		}
		printf("success\n");

		ne10_vec4f_t vector1[num_vectors];
		ne10_vec4f_t vector2[num_vectors];
		ne10_float32_t result_c[num_vectors];

		//Fills the components of each vector in the arrays with a random number
		for (int i=0;i<num_vectors;i++){
				init_rand_vector(&vector1[i]);
				init_rand_vector(&vector2[i]);
		}

		for (int i=0;i<n;i++){
		start_time= clock();
		ne10_dot_vec4f_c(result_c, vector1, vector2, num_vectors);
		end_time= clock();
		time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; c_time += time;
		//printf("Result of vector dot product in C: %f in %f seconds\n", result_c,time);
		}
		for (int i=0;i<n;i++){
		start_time = clock();
		ne10_dot_vec4f_neon(result_c, vector1, vector2, num_vectors);
		end_time= clock();
		time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; neon_time += time;
		//printf("Result of vector dot product in NEON: %f in %f seconds\n", result_c,time);
		}
		
		c_time /= n;
		neon_time /= n;
		printf("C time average: %f seconds (%f ms) for %d 4fvectors, tested %d times\n", c_time,c_time*1000,num_vectors,n);
		printf("Neon time average: %f seconds (%f ms) for %d 4fvectors, tested %d times\n", neon_time,neon_time*1000,num_vectors,n);

//ASM not recognized
//		ne10_dot_vec4f_asm(&result_c, &vector1, &vector2, 1);
//		printf("Result of vector dot product in ASM: %f\n", result_c);

		return 0;
}
