/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 1
 * =================================================================
 *
 *  Problem E
 * ====================
 * Implement Quick Sort in sort() that sorts N numbers in an array
 * A[] and store the sorted array in B[]. Your implementation must run
 * in expected time O(N log N).
 *
 * The template is there to handle the input and output for you. If you
 * want to test your implementation, check out the Input and Output
 * sections below and the sample files.
 *
 * You are free to declare any auxilliary functions and variables but
 * the variables are restricted to int64_t and arrays of that.
 *
 * You are not allowed to use any preprocessor commands and library
 * functions that are not in the template.
 *
 * To compile, type (without $):
 * $ make E
 *
 *  Input
 * ====================
 * There will be:
 *
 * - One line containing the value N, the number of intergers you have
 *   to sort.
 * - One line containing a space separated list of N integers. Each
 *   integer A[i] indicates the value of an element in the array.
 *
 *  Output
 * ====================
 * Output one line containing a space separated list of the sorted
 * list of integers.
 *
 *  Limits
 * ====================
 * 1 <=   N  <= 100000
 * 0 <= A[i] <= 2^63 - 1, for 0 <= i < N
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

#define MAXN 100000

int64_t A[MAXN];
int64_t B[MAXN];
int64_t N;

// rand_pivot returns a random integer between 0 to M-1
int64_t rand_pivot(int64_t M) {
  return rand() % M;
}

int64_t partition(int64_t s, int64_t t){
	int64_t pindex = s+rand_pivot(t-s), i = 0, temp = 0;
	for(i = s; i <= t; i++){
		if(i < pindex){
			if(A[i]>A[pindex]){
				temp = A[i];
				A[i] = A[pindex];
				A[pindex] = temp;
				pindex = i;
			}
		} else {
			if(A[i] <= A[pindex]){
				temp = A[i];
                                A[i] = A[pindex];
                                A[pindex] = temp;
				pindex = i;
			}
		}	
	}
	return pindex;
		
}

void quicksort(int64_t s, int64_t t) {
	int64_t split = 0, pivot = 0;
	if(t-s>=1)
	{
		split = partition(s,t);
		quicksort(s,split);
		quicksort(split+1,t);
	}
}

void sort(int64_t s, int64_t t) {
        quicksort(s,t-1);
	for(int64_t i = 0; i< N; i++)B[i]=A[i];
}

int64_t main() {
  srand(time(NULL));
  scanf("%"PRId64, &N);
  for (int64_t i = 0; i < N; ++i)
    scanf("%"PRId64, &A[i]);
  sort(0, N);

  for (int64_t i = 0; i < N; ++i)
    printf(i == N-1 ? "%"PRId64 "\n" : "%"PRId64 " ", B[i]);
  return 0;
}
