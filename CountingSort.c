/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 1
 * =================================================================
 *
 *  Problem B
 * ====================
 * Implement Counting Sort in sort() that sorts N numbers in an array
 * A[] and store the sorted array in B[]. Your implementation must run
 * in time O(N).
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
 * $ make B
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
 * 1 <=   N  <= 5000000
 * 0 <= A[i] <  5000000, for 0 <= i < N
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXN 5000000

int64_t A[MAXN];
int64_t B[MAXN];
int64_t C[MAXN];
int64_t N;

void sort() {
	int64_t i = 0;
	
	//counts the occurences of each member of A
	for(i = 0; i < N; i++) C[A[i]]++;
	//counts the number of elements less the the current index
	for(i = 1; i < MAXN; i++) C[i] = C[i] + C[i-1];
	//sorts the elements and puts in B
	for(i = 0; i < N; i++) 
	{
		B[C[A[i]]-1] = A[i];
		--C[A[i]];
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
