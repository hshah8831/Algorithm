/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 2
 * =================================================================
 *
 *  Problem B
 * ====================
 * Implement Hth_smallest() that returns the H-th smallest number in
 * an array A[] which consists of N numbers. Your implementation must
 * run in time O(N).
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
 * - One line containing the values N, the number of integers in A[],
 *   and H 
 * - One line containing a space separated list of N integers. Each
 *   integer A[i] indicates the value of an element in the array.
 *
 *  Output
 * ====================
 * Output one line containing the H-th smallest integer in A[].
 *
 *  Limits
 * ====================
 * 1 <=   N  <= 5000000
 * 1 <=   H  <= N
 * 0 <= A[i] <  5000000, for 0 <= i < N
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXN 5000000

int64_t A[MAXN];
int64_t N, H;

int64_t cieling_after_dividing(int64_t length){
	if(length%5 == 0){
		return length/5;
	} else {
		return (1 + length/5);
	}

}

int64_t position_of(int64_t val,int64_t low, int64_t length){
		for(int64_t i = low;i < (low+length);i++){
			if(A[i] == val){
				return i;
			}
		}
	return -1;
}

void sort(int64_t low, int64_t length) {
	int64_t i = 0;
	int64_t j = 0;
	int64_t temp = 0;
//	printf("from sort()\n");
//	printf("low=%"PRId64,low);
//	printf("length=%"PRId64,length);
	for (i = low+length-1; i >= low; i--)

	{
		for(j = low; j < i; j++)
		{
			if(A[j]>A[j+1])
			{
				temp = A[j];
				A[j] = A[j+1];
			 	A[j+1] = temp;	
			}
		}
	}
//	printf("\nend of sort()\n");
}

int64_t median(int64_t low, int64_t length){
	sort(low,length);
	if(length%2 == 0){
		return A[low+(length-1)/2];
	}else{
		return A[low+(length/2)];
	}
}

int64_t partition(int64_t low, int64_t length){
	int64_t med_array_length = cieling_after_dividing(length);
	int64_t MEDIAN[med_array_length];
	int64_t i = 0, mom = 0,j = 0, temp = 0;

//	printf("\n Median array length = %"PRId64,med_array_length);
	//populate the median array
	for(i=low;(i+4)<(low+length);i+=5){
		MEDIAN[j++] = median(i,5);
	}
	if(length%5>0){

	MEDIAN[med_array_length-1] = median(i,length%5);}
	//finding the median of median
	for (i = med_array_length - 1; i >= 0; i--)
	{
		for(j = 0; j < i; j++)
		{
			if(MEDIAN[j]>MEDIAN[j+1])
			{
				temp = MEDIAN[j];
				MEDIAN[j] = MEDIAN[j+1];
			 	MEDIAN[j+1] = temp;	
			}
		}
	}
//	printf("Median Array = ");
//	  for (int64_t i = 0; i < med_array_length; ++i)
//   		 printf(i == med_array_length-1 ? "%"PRId64 "\n" : "%"PRId64 " ", MEDIAN[i]);
	if(med_array_length%2 == 0){
                mom = MEDIAN[(med_array_length/2)-1];
        }else{
                mom = MEDIAN[med_array_length/2];
        }
//	printf("\n Median of Median = %"PRId64,mom);
	//ordering the array according to the partition found
	int64_t pindex = position_of(mom,low,length);
//	printf("\n  pindex before shuffling = %"PRId64,pindex);
//	for (int64_t i = 0; i < N; ++i)
//                 printf(i == N-1 ? "%"PRId64 "\n" : "%"PRId64 " ", A[i]);
	//moving the mom to the end of the subarray
	temp = A[low+ length - 1];
	A[low+ length - 1] = A[pindex];
	A[pindex] = temp;
	pindex = low+ length - 1;
	i = low;
    	for (int j = low; j <= low + length - 2; j++)
    	{
        	if (A[j] <= mom)
        	{
            	temp = A[i];
		A[i] = A[j];
		A[j] = temp;

            	i++;
        	}
    	}
	temp = A[i];
	A[i] = A[low+length-1];
	A[low+length-1] = temp;
	pindex = i;
	return pindex;
}

int64_t Hth_smallest(int64_t low, int64_t length) {
	if(H>low && H <= (low+length)){
                //deterministic partition and recursion
                int64_t split = partition(low,length);
                int64_t lower_half_len = split-low;
                int64_t higher_half_len = length-lower_half_len-1;
//                printf("\n Split = %"PRId64,split);
                if(split == (H - 1)){
                                 return A[split];
                } else if(split > (H - 1)){
                        return Hth_smallest(low,lower_half_len);
                } else {
                        return Hth_smallest(split + 1, higher_half_len);
                }
        }
}

int64_t main() {
  scanf("%"PRId64"%"PRId64, &N, &H);
  for (int64_t i = 0; i < N; ++i)
    scanf("%"PRId64, &A[i]);
	
/*	int64_t pindex = partition(0,N);
  	printf("pindex = %"PRId64,pindex);
	printf("\n A[pindex] = %"PRId64,A[pindex]);
//	sort(5,N-5);
	  for (int64_t i = 0; i < N; ++i)
		printf(i == N-1 ? "%"PRId64 "\n" : "%"PRId64 " ", A[i]); */
  printf("%"PRId64"\n", Hth_smallest(0,N)); 
  return 0;
}
