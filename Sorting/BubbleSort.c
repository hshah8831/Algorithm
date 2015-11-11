/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 1
 * =================================================================
 *
 *  Problem A
 * ====================
 * Implement Bubble Sort in sort() that sorts N numbers in an array
 * A[] and store the sorted array in B[]. Your implementation must run
 * in time O(N^2).
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
 * $ make A
 *
 *  Input
 * ====================
 * There will be:
 *
 * - One line containing the value N, the number of integers you have
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
 * 1 <=   N  <= 1000
 * 0 <= A[i] <  2^63 - 1, for 0 <= i < N
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXN 1000

int64_t A[MAXN];
int64_t B[MAXN];
int64_t N;

void sort() {
	int64_t i = 0;
	int64_t j = 0;
	int64_t temp = 0;

	for (i = N-1; i >= 0; i--)
	{
		for(j = 0; j < i; j++)
		{
			if(A[j]>A[j+1])
			{
				temp = A[j];
				A[j] = A[j+1];
			 	A[j+1] = temp;	
			}
		}
		B[i] = A[i];
	}
}

int64_t main() {
  scanf("%"PRId64, &N);
  for (int64_t i = 0; i < N; ++i)
    scanf("%"PRId64, &A[i]);
  sort();
  for (int64_t i = 0; i < N; ++i)
    printf(i == N-1 ? "%"PRId64 "\n" : "%"PRId64 " ", B[i]);
  return 0;
}
