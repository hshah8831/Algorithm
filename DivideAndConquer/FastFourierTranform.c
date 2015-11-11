/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 2
 * =================================================================
 *
 *  Problem E
 * ====================
 * Implement Fast Fourier Transform in fft() that multiplies the
 * K-th Walsh-Hadamard matrix H with a vector x of length N = 2^k
 * that is stored in the array x[], and store the result Hx in the
 * array Hx[]. Your implementation must run in time O(N log N).
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
 * - One line containing the value K.
 * - One line containing a space separated list of N = 2^K integers. Each
 *   integer indicates the value at a position of the vector x.
 *
 *  Output
 * ====================
 * Output one line containing a space separated list of integers
 * indicating the values at positions of Hx[]
 *
 *  Limits
 * ====================
 * 1 <=   K  <= 20
 * -5000000 <= x[i] <= 5000000, for 0 <= i < 2^K
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXN 2000000

int64_t K, N;
int64_t x[MAXN];
int64_t Hx[MAXN];
int64_t B[MAXN];
int64_t FIRST_HALF[MAXN/2],SECOND_HALF[MAXN/2];

/*int64_t power(int64_t base, int64_t pow)
{
    int64_t temp;
    if( pow == 0)
        return 1;
    temp = power(base, pow/2);
    if (pow%2 == 0)
        return temp*temp;
    else
        return base*temp*temp;
}

void scalar_multiplication(int64_t x, int64_t row_low,int64_t col_low,  int64_t k){
	printf("scalar_multiplication(%"PRId64",%"PRId64",%"PRId64",%"PRId64")\n",x,row_low,col_low,k);
	int64_t i = row_low, j = col_low;
	for(i = row_low;i<row_low+k;i++){
		for(j=col_low;j<col_low+k;j++){
			HM[i][j] = x * HM[i][j];
			printf("%"PRId64,HM[i][j]);
		}
		printf("\n");
	}
	printf("end of scalar multiplcaition\n");
}

void make_hadamard_matrix(int64_t row_low,int64_t col_low,int64_t k){
	printf("make_hadamard_matrix(%"PRId64",%"PRId64",%"PRId64")\n",row_low,col_low,k);
	if(k == 1){
		HM[row_low][col_low] = 1;
		HM[row_low + 1][col_low] = 1;
		HM[row_low][col_low + 1] = 1;
		HM[row_low + 1][col_low + 1] = -1;
	} else {
		make_hadamard_matrix(row_low, col_low, k-1);
		make_hadamard_matrix(row_low + power(2,k-1), col_low, k-1);
		make_hadamard_matrix(row_low, col_low + power(2,k-1), k-1);
		make_hadamard_matrix(row_low + power(2,k-1), col_low + power(2,k-1), k-1);
		scalar_multiplication(-1, row_low + power(2,k-1), col_low + power(2,k-1), power(2,k-1));
	}
}

void display_HM(){
//	printf("\ndisplay_HM()-: k = %"PRId64,K);
//	printf("pow(2,K)=%"PRId64"\n",power(2,K));
	int64_t n = power(2,K);
//	printf("n=%"PRId64"\n",n);
	for(int64_t i=0;i<n;i++){
		for(int64_t j=0;j<n;j++){
			printf("%"PRId64,HM[i][j]);
		}
		printf("\n");
	}
}


void fft() {
	make_hadamard_matrix(0,0,K);
	int64_t n = power(2,K), res=0;
        for(int64_t i=0;i<n;i++){
		res=0;
                for(int64_t j=0;j<n;j++){
                        res= res + HM[i][j]*x[j];
                }
		Hx[i]=res;
        }	
}*/

//takes the low index and and length of the subarray of INDEX and groups even values
// in the first half of the array and the odd values in the second half
void groupOddEven(int64_t low, int64_t length){
        int64_t mid = length/2, j = 0;
        for(int64_t i = low; i < low + length; i++){
                ((i%2)==0)? (B[j++] = Hx[i]) : (B[j+mid-1] = Hx[i]);
        }
        j = 0;
        for(int64_t i = low; i < low + length; i++) Hx[i] = B[j++];
}

//reverts the INDEX array subarray from low of given length to the state
//before grouping by above procodure.
void ungroupOddEven(int64_t low, int64_t length){
        //int64_t FIRST_HALF[length/2],SECOND_HALF[length/2];
        for(int64_t i =0;i<MAXN/2;i++) FIRST_HALF[i]=SECOND_HALF[i]=0;
	for(int64_t i = 0; i < length/2; i++)FIRST_HALF[i] = Hx[low + i];

        for(int64_t i = 0; i < length/2; i++)SECOND_HALF[i] = Hx[length/2 + low + i];
        int64_t i = 0;
        for(int64_t j = 0, k = 0; j < length/2 || k < length/2; ) ((i%2)==0)? (Hx[low + i++] = FIRST_HALF[j++]) : (Hx[low + i++] = SECOND_HALF[k++]);
}


void fft(int64_t low, int64_t length){
	if(length == 2){
		int64_t a = Hx[low] + Hx[low+1];
		int64_t b = -Hx[low+1] + Hx[low];
		Hx[low] = a;
		Hx[low+1] = b;
	} else {
		groupOddEven(low,length);
		fft(low,length/2);
		fft(low+length/2,length/2);
		ungroupOddEven(low,length);
		for(int64_t i=low;i<low+length;i+=2){
			int64_t a = Hx[i] + Hx[i+1];
			int64_t b = -Hx[i+1] + Hx[i];
			Hx[i] = a;
			Hx[i+1] = b;
		}
	}
}

int64_t main() {
  scanf("%"PRId64, &K);
  N = (1 << K);
/*	printf("pow(2,K)=%"PRId64"\n",power(2,K));
	make_hadamard_matrix(0,0,K);
	display_HM();*/
  for (int64_t i = 0; i < N; ++i)
  scanf("%"PRId64, &x[i]);
	for (int64_t i = 0; i < N; ++i)
  		Hx[i]=x[i];
  fft(0,N);
  for (int64_t i = 0; i < N; ++i)
    printf(i == N-1 ? "%"PRId64 "\n" : "%"PRId64 " ", Hx[i]);
  return 0;
}
