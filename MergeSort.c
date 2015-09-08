/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 1
 * =================================================================
 *
 *  Problem D
 * ====================
 * Implement Merge Sort in sort() that sorts N numbers in an array
 * A[] and store the sorted array in B[]. Your implementation must run
 * in time O(N log N).
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
 * $ make D
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
 * 1 <=   N <= 100000
 * 0 <= A[i] <= 2^63 - 1, for 0 <= i < N
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXN 100000

int64_t A[MAXN];
int64_t B[MAXN];
int64_t N;

void merge(int64_t s, int64_t t) {
	int64_t i = 0,j = 0,b = 0,mid = 0,k = 0;
	mid = (t + s)/2;
	for(b = i = s,j = mid; i < mid && j < t;){
		if(A[i]<A[j])
			{B[b] = A[i];i++;}
		else if(A[i]>A[j])
			{B[b] = A[j];j++;}
		else
			{	B[b] = A[i];i++;b++;
				B[b] = A[j];j++;
			}

		b++;
	}
	while(i<mid){
		B[b] = A[i]; i++; b++;
	}	
	while(j<t){
		B[b] = A[j]; j++; b++;
	}
	for(k = s; k < t;k++) A[k] = B[k];
       
}

void mergesort(int64_t s, int64_t t) {
	int64_t mid =(t + s)/2;
	// printf("mid = %"PRId64" s = %"PRId64 " t = %"PRId64, mid,s,t);
	if(t-s > 1) 
	{
		mergesort(s,mid);
		mergesort(mid,t);
		merge(s,t);
	}

}

void sort(int64_t s, int64_t t){
	mergesort(0,N);
//	merge(0,N);
	for(int64_t k = s; k < t;k++) B[k] = A[k];
}

int64_t main() {
  scanf("%"PRId64, &N);
  for (int64_t i = 0; i < N; ++i)
    scanf("%"PRId64, &A[i]);
  sort(0, N);
  for (int64_t i = 0; i < N; ++i)
    printf(i == N-1 ? "%"PRId64 "\n" : "%"PRId64 " ", B[i]);
  return 0;
}
