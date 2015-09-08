/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 2
 * =================================================================
 *
 *  Problem D
 * ====================
 * Implement Karatsuba algorithm in multiply() that multiplies two
 * N-digit decimal integers in arrays A[] and B[], where A[i] and
 * B[i] are the i-th least significant digits of A and B respectively,
 * and store their product in array C[] and its number of digits in M.
 * Your implementation must run in time O(N^1.59).
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
 * - One line containing the value N, the number of digits in A and B.
 * - One line containing an N-digit decmial integer A.
 * - One line containing an N-digit decmial integer B.
 *
 *  Output
 * ====================
 * Output one line containing the integer C.
 *
 *  Limits
 * ====================
 * 1 <=   N <= 50000
 * 0 <= A[i] <= 9, for 0 <= i < N
 * 0 <= B[i] <= 9, for 0 <= i < N
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXN 50000

int64_t A[MAXN];
int64_t B[MAXN];
int64_t C[MAXN];
int64_t N, M;


// print the n-digit integer in array a[]
void print(int64_t *a, int64_t n) {
//	int64_t f = 0;
  for (int64_t i = n-1; i >= 0; --i) {
//    	if(a[i]>0){f=1;}
//	if(f == 1){
	printf("%"PRId64, a[i]);
//	}
  } puts("");
}

// add(a, b, n, c, &m) takes integers a and b, each of 
// at most n digits, computes a+b and stores the m-digit
// sum into c
void add(int64_t *a, int64_t *b, int64_t n, int64_t *c, int64_t *m) {
/*	printf("add(%"PRId64")",n);
        printf("A:  ");
        print(a,n);
        printf("B:  ");
        print(b, n);
	printf("Before  Addition C:  ");
        print(c, *m);*/
/*	if(n==1){
		int64_t sum = (*a + *b + *c);
		if(sum>9){
			*(c+1) = sum/10;
			*c = sum%10;
			*m = *m+1;
		}
		*m = *m+1;
	} else {
		add(a , b, n/2, c, m);
		add((a + n/2) , (b + n/2), n/2 + n%2, (c + n/2), m);
//		add(a , b, n/2 + n%2, c, m);
	}*/
	int64_t i=0,j=0,sum=0;
	for(i=0;i<n;i++){
		sum = *(a+i) + *(b+i) + *(c+i);
		if(sum>9){
			*(c+i+1) = sum/10;
		        *(c+i) = sum%10;
		} else {
			*(c+i) = sum;
		}	
		j++;
	}
	(*(c+j)>0&&*(c+j)<10)?(*m=j+1):(*m=j);
//	printf("End of Add() C:  ");
//      print(c, *m);
}

// subtract(a, b, n, c, &m) takes integers a and b, each of 
// at most n digits satisfying a >= b, computes a-b and
// stores the m-digit difference into c
void subtract(int64_t *a, int64_t *b, int64_t n, int64_t *c, int64_t *m) {
/*	printf("subtract(%"PRId64")",n);
        printf("A:  ");
        print(a,n);
        printf("B:  ");
        print(b, n);*/
	int64_t diff= 0,j=0,i=0;
/*	if(n==1){
		if(*a < *b){
			diff = *a + 10 - *b;
			*(a+1) = *(a+1) - 1;
		} else {
			diff = *a - *b;
		}
		*c = diff;
		*m = *m+1;
	} else {
		subtract(a , b, n/2, c, m);
                subtract((a + n/2) , (b + n/2), n/2 + n%2, (c + n/2), m);
	}*/
	for(i=0;i<n;i++){
		if(*(a+i) < *(b+i)){
		        diff = *(a+i) + 10 - *(b+i);
        		*(a+i+1) = *(a+i+1) - 1;
		} else {
	        	diff = *(a+i) - *(b+i);
    		}
	*(c+i) = diff;
	j++;
	}	
	*m=j;
}

// multiply(a, b, n, c, &m) takes integers a and b, each of
// at most n digits, computes a*b and stores the m-digit product 
// into c
void multiply(int64_t *a, int64_t *b, int64_t n, int64_t *c, int64_t *m) {
	int64_t mid = n/2,a1=0,b1=0,e1=0,temp1=0,temp2=0,temp3=0,i=0;
	int64_t A1[MAXN],B1[MAXN],E1[MAXN],TEMP1[MAXN],TEMP2[MAXN],TEMP3[MAXN];
/*	printf("multiply(%"PRId64")",n);
	printf("A:  ");
        print(a,n);
	printf("B:  ");
        print(b, n);*/
	if(n == 1){
		int64_t prod = *a * *b,i = 0;
		int64_t temp = prod;
		while(temp>0){
			temp = temp/10;i++; 
		}
		*m = *m+i;
		temp = prod;
		for(int64_t j = 0;j < *m;j++){
			*(c+j) = temp%10;temp = temp/10;
		}
	} else if(n>1){
/*		multiply((a + n/2) , (b + n/2), n/2, A1, &a1);
		printf("A1:  ");
		print(A1, a1);
		multiply(a , b, n/2 + n%2, B1, &b1);
		printf("B1:  ");
                print(B1, b1);*/
//		n=n+(n%2);
		if(n%2==1){
                	n = n + 1;
                	*(a+n-1)=*(b+n-1)=0;
        	}
		for(int64_t i=0;i<MAXN;i++)TEMP1[i]=TEMP2[i]=0;
                temp1=temp2=0;
		add(a, (a + n/2), n/2, TEMP1, &temp1);
/*		printf("TEMP1:  ");
                print(TEMP1, temp1);*/
		add(b , (b + n/2), n/2, TEMP2, &temp2);
//		printf("TEMP2:  ");
//		print(TEMP2, temp2);
//		printf("A1:  ");
//              print(A1, a1);
		if(temp1<temp2){
			for(i=temp1;i<temp2;i++)TEMP1[i]=0;
			temp1=temp2;
		} else if(temp1>temp2){
			for(i=temp2;i<temp1;i++)TEMP2[i]=0;
			temp2=temp1;
		}
//		printf("TEMP1:  ");
//              print(TEMP1, temp1);
//		printf("TEMP2:  ");
//              print(TEMP2, temp2);
		multiply(TEMP1 , TEMP2, temp1, TEMP3, &temp3);
//		printf("TEMP3:  ");
//              print(TEMP3, temp3);
		multiply((a + n/2) , (b + n/2), n/2, A1, &a1);
//		printf("A1:  ");
//              print(A1, a1);
//        	printf("TEMP3:  ");
//              print(TEMP3, temp3);
		for(int64_t i=0;i<MAXN;i++)TEMP1[i]=TEMP2[i]=0;
		temp1=temp2=0;
		if(temp3<a1){
			for(i=temp3;i<a1;i++)TEMP3[i]=0;
			temp3=a1;
		} else if(temp3>a1){
			for(i=a1;i<temp3;i++)A1[i]=0;
			a1=temp3;
		}
//		printf("TEMP3:  ");
//                print(TEMP3, temp3);
//		printf("A1:  ");
//                print(A1, a1);
		subtract(TEMP3 , A1, temp3, TEMP1, &temp1);
//		printf("TEMP1:  ");
//                print(TEMP1, temp1);
		multiply(a , b, n/2, B1, &b1);
		if(temp1<b1){
			for(i=temp1;i<b1;i++)TEMP1[i]=0;
			temp1=b1;
		} else if(temp1>b1){
			for(i=b1;i<temp1;i++)B1[i]=0;
			b1=temp1;
		}
//		printf("B1:  ");
//                print(B1, b1);
		for(int64_t i=0;i<MAXN;i++)E1[i]=0;
                e1=0;
		subtract(TEMP1 , B1, temp1, E1, &e1);
//		printf("E1:  ");
//                print(E1, e1);
		for(int64_t i=e1-1;i>=0;i--)E1[i+n/2]=E1[i];
		e1 = e1 + n/2;
		for(int64_t i=0;i<n/2;i++)E1[i]=0;
/*		printf("E1 after *10^n/2");
		printf("E1:  ");
                print(E1, e1);*/
		for(int64_t i=a1-1;i>=0;i--)A1[i+n]=A1[i];
		a1 = a1 + n;
		for(int64_t i=0;i<n;i++)A1[i]=0;
/*		printf("A1 after *10^n");
                printf("A1:  ");
                print(A1, a1);*/
		if(a1<b1){
			for(i=a1;i<b1;i++)A1[i]=0;
			a1=b1;
		} else if(a1>b1){
			for(i=b1;i<a1;i++)B1[i]=0;
			b1=a1;
		}
//		printf("A1:  ");
//                print(A1, a1);
//		printf("B1:  ");
//                print(B1, b1);
//		printf("TEMP2:  ");
//                print(TEMP2, a1);
		for(int64_t i=0;i<MAXN;i++)TEMP2[i]=0;
                temp2=0;
		add(A1, B1, a1, TEMP2, &temp2);
//		printf("TEMP2:  ");
//                print(TEMP2, temp2);
		if(temp2<e1){
			for(i=temp2;i<e1;i++)TEMP2[i]=0;
			temp2=e1;
		} else if(temp2>e1){
			for(i=e1;i<temp2;i++)E1[i]=0;
			e1=temp2;
		}
		for(int64_t i=0;i<MAXN;i++)*(c+i)=0;
                *m=0;
		add(TEMP2, E1, e1, c, m);
/*		printf("C:  ");
                print(c, *m);
		printf("/End of Multiplication");*/
		for (int64_t i = *m-1; i >= 0; --i) {
   			if(c[i]>0){*m = i+1;break;}
  		}
	}	
}

int64_t main() {
  scanf("%"PRId64, &N);
  char s[MAXN]; gets(s);
  gets(s);
  for (int64_t i = 0; i < N; ++i)
    A[N-1-i] = s[i] - '0';
  gets(s);
  for (int64_t i = 0; i < N; ++i)
    B[N-1-i] = s[i] - '0';
	if(N%2==1){
		N = N + 1;
		A[N-1]=B[N-1]=0;
	}
		
/*	int64_t *a = A;
	printf("*a = %"PRId64"*(a + sizeof(a)) = %"PRId64,*a,*a++);
	M = 0;
	int64_t SUBM = N;
  add(A, B, N, C, &M);
//  multiply(A, B, N, C, &M);
  printf("M=%"PRId64,M);
  print(C, M);
//	for(int64_t i = 0; i<SUBM;i++) C[i] = 0;
	M=0;
	subtract(A, B, N, C, &M);
	printf("M=%"PRId64,M);
	print(C,M);*/
  M=0;
  multiply(A, B, N, C, &M);
  print(C, M);
  return 0;
}
