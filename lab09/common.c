#include <time.h>
#include <stdio.h>
#include <x86intrin.h>
#include "common.h"

/*conclusion
1. forgot the requirement of vals[i] >= 128 when dealing with marginal cases
	how I found out: reduce test case to marginal case
*/



long long int sum(unsigned int vals[NUM_ELEMS]) {
	clock_t start = clock();

	long long int sum = 0;
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for(unsigned int i = 0; i < NUM_ELEMS; i++) {
			if(vals[i] >= 128) {
				sum += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return sum;
}

long long int sum_unrolled(unsigned int vals[NUM_ELEMS]) {
	clock_t start = clock();
	long long int sum = 0;

	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		for(unsigned int i = 0; i < NUM_ELEMS / 4 * 4; i += 4) {
			if(vals[i] >= 128) sum += vals[i];
			if(vals[i + 1] >= 128) sum += vals[i + 1];
			if(vals[i + 2] >= 128) sum += vals[i + 2];
			if(vals[i + 3] >= 128) sum += vals[i + 3];
		}

		//This is what we call the TAIL CASE
		//For when NUM_ELEMS isn't a multiple of 4
		//NONTRIVIAL FACT: NUM_ELEMS / 4 * 4 is the largest multiple of 4 less than NUM_ELEMS
		for(unsigned int i = NUM_ELEMS / 4 * 4; i < NUM_ELEMS; i++) {
			if (vals[i] >= 128) {
				sum += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return sum;
}

long long int sum_simd(unsigned int vals[NUM_ELEMS]) {
	clock_t start = clock();
	__m128i _127 = _mm_set1_epi32(127);		// This is a vector with 127s in it... Why might you need this?
	long long int result = 0;				   // This is where you should put your final result!
	/* DO NOT DO NOT DO NOT DO NOT WRITE ANYTHING ABOVE THIS LINE. */
	int pace = 16;
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		/* YOUR CODE GOES HERE */
		__m128i tempRes = _mm_setzero_si128();
		for (unsigned int i = 0; i < NUM_ELEMS-NUM_ELEMS%pace; i+=4){
			//_mm_loadu_si128()
			__m128i val = _mm_loadu_si128(vals+i); //do we need to add sizeof(arr?)
			__m128i mask = _mm_cmpgt_epi32(val, _127);
			__m128i temp = _mm_and_si128(val, mask);
			tempRes = _mm_add_epi32(temp, tempRes);
		}
		int tempArr[4]; //not : int * tempArr[4]
		_mm_storeu_si128(tempArr, tempRes);
		result += tempArr[0] + tempArr[1] + tempArr[2] + tempArr[3];

		/* You'll need a tail case. */
		for (unsigned int i = NUM_ELEMS-NUM_ELEMS%pace; i < NUM_ELEMS; i ++) {
			if (vals[i]>= 128){
				result += vals[i];
			}
		}
	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return result;
}

long long int sum_simd_unrolled(unsigned int vals[NUM_ELEMS]) {
	clock_t start = clock();
	__m128i _127 = _mm_set1_epi32(127);
	long long int result = 0;
	for(unsigned int w = 0; w < OUTER_ITERATIONS; w++) {
		/* COPY AND PASTE YOUR sum_simd() HERE */
		/* MODIFY IT BY UNROLLING IT */
		__m128i tempRes = _mm_setzero_si128();
		for (unsigned int i = 0; i < NUM_ELEMS-NUM_ELEMS%16; i+=16){
			__m128i val = _mm_loadu_si128(vals+i); 
			__m128i mask = _mm_cmpgt_epi32(val, _127);
			__m128i temp = _mm_and_si128(val, mask);
			tempRes = _mm_add_epi32(temp, tempRes);

			val = _mm_loadu_si128(vals+i+4);
			mask = _mm_cmpgt_epi32(val, _127);
			temp = _mm_and_si128(val, mask);
			tempRes = _mm_add_epi32(temp, tempRes);

			val = _mm_loadu_si128(vals+i+8); 
			mask = _mm_cmpgt_epi32(val, _127);
			temp = _mm_and_si128(val, mask);
			tempRes = _mm_add_epi32(temp, tempRes);

			val = _mm_loadu_si128(vals+i+12); 
			mask = _mm_cmpgt_epi32(val, _127);
			temp = _mm_and_si128(val, mask);
			tempRes = _mm_add_epi32(temp, tempRes);
		}
		/* You'll need 1 or maybe 2 tail cases here. */
		for (unsigned int i = NUM_ELEMS-NUM_ELEMS%16; i < NUM_ELEMS-NUM_ELEMS%4; i += 4) {
			//printf("one time though second last case\n");
			__m128i val = _mm_loadu_si128(vals+i); //do we need to add sizeof(arr?)
			__m128i mask = _mm_cmpgt_epi32(val, _127);
			__m128i temp = _mm_and_si128(val, mask);
			tempRes = _mm_add_epi32(temp, tempRes); 
		}
		for (unsigned int i = NUM_ELEMS-NUM_ELEMS%4; i < NUM_ELEMS; i++) {
			//printf("one time through last case\n");
			if(vals[i] >= 128) {
				result += vals[i];
			}
		}

		int tempArr[4] = {}; //not : int * tempArr[4]
		_mm_storeu_si128(tempArr, tempRes);
		result = tempArr[0] + tempArr[1] + tempArr[2] + tempArr[3] + result;


	}
	clock_t end = clock();
	printf("Time taken: %Lf s\n", (long double)(end - start) / CLOCKS_PER_SEC);
	return result;
}