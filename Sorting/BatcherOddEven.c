/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 2
 * =================================================================
 *
 *  Problem A
 * ====================
 * Implement Batcher's Odd-Even Sort in sort() that sorts N numbers
 * in an array A[] and store the sorted array in B[]. Your
 * implementation must run in time O(N log^2 N), and you are only
 * allowed to access the input via the provided compare_exchange().
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
 * 1 <=   N  <= 30000
 * 0 <= A[i] <  2^63 - 1, for 0 <= i < N
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXN 50000

int64_t A[MAXN];
int64_t B[MAXN];
int64_t INDEX[MAXN];
int64_t N;
int64_t FIRST_HALF[MAXN/2],SECOND_HALF[MAXN/2];

// compare_exchange(&x, &y) swaps x and y if and only if x > y.
void compare_exchange(int64_t *x, int64_t *y) {
  int64_t z = *x ^ *y;
  *x = *x < *y ? *x : *y;
  *y = z ^ *x;
}

//takes the low index and and length of the subarray of INDEX and groups even values
// in the first half of the array and the odd values in the second half
void groupOddEven(int64_t low, int64_t length){
	int64_t mid = length/2, j = 0;
	for(int64_t i = low; i < low + length; i++){
		((i%2)==0)? (B[j++] = INDEX[i]) : (B[j+mid-1] = INDEX[i]);
	}
	j = 0;
	for(int64_t i = low; i < low + length; i++) INDEX[i] = B[j++];
}

//reverts the INDEX array subarray from low of given length to the state 
//before grouping by above procodure.
void ungroupOddEven(int64_t low, int64_t length){
	for(int64_t i = 0;i<MAXN/2;i++)FIRST_HALF[i]=SECOND_HALF[i]=0;
	for(int64_t i = 0; i < length/2; i++)FIRST_HALF[i] = INDEX[low + i];

	for(int64_t i = 0; i < length/2; i++)SECOND_HALF[i] = INDEX[length/2 + low + i];
	int64_t i = 0;
	for(int64_t j = 0, k = 0; j < length/2 || k < length/2; ) ((i%2)==0)? (INDEX[low + i++] = FIRST_HALF[j++]) : (INDEX[low + i++] = SECOND_HALF[k++]);
}

//merges the first half and second half the subarray starting at low of length length 
//using the Batcher's Odd Even Algorithm.
void oddEvenMerge(int64_t low, int64_t length){
	int64_t mid = length/2;
	if(length == 2){
		compare_exchange(&A[INDEX[low]],&A[INDEX[low+1]]);
	} else if (length > 2){
		//groups the even indices and odd indices together
		groupOddEven(low, length);
		//branches out the first half for further merging
		oddEvenMerge(low,mid);
		//branches out the second half for further merging
		oddEvenMerge(low+mid,mid);
		//reverts the grouping done earlier
		ungroupOddEven(low,length);
		//runs compare-exchange on the merged subarray
		for(int64_t i = low + 1; i < low + length - 1; i+=2){
			compare_exchange(&A[INDEX[i]],&A[INDEX[i+1]]);
		}

	}
}

void oddEvenMergeSort(int64_t low, int64_t length){
	int64_t mid = 0;
	if(length>1){
		mid = length/2;
		//branches out to sort the first half
		oddEvenMergeSort(low,mid);
		//branches out to sort the second half
		oddEvenMergeSort(low+mid,mid);
		//merges the result
		oddEvenMerge(low,length);
	}
}

//returns the result of base raised to power.
int64_t power(int64_t base, int64_t power){
	int64_t k = 0, result = 0;
	if(power == 0){
		result = 1;
	} else if(power == 1){
		result = base;
	} else {
		result = base;
		for(k = 2; k <= power; k++) result*=base;
	}
	return result;
}

//calulates the nearest perfect square to given N and pads the extra 
//spaces in the array with a negative infinite value.
void sort() {

	int64_t negInf = -1;
	int64_t oldN = N, k = 0,j=0;
	for(k = 0; power(2,k) < N; k++);
	N = power(2,k);
	for(int64_t i = oldN; i < N; i++) A[i] = negInf;
	for(int64_t i = 0; i < N; i++) INDEX[i] = i;
	oddEvenMergeSort(0,N);
	for(int64_t i = 0; i < N;){
		if(A[i] == -1){
			i++;
		}else{
			 B[j++] = A[i++];
		}
	}
	N=j;
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
