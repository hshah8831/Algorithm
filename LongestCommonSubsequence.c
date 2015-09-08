/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 3
 * =================================================================
 *
 *  Problem A
 * ====================
 * Use Dynamic Programming to implement lcs(), which finds a longest 
 * common subsequence in two strings in arrays S[] and T[] of length
 * Sn and Tn respectively, and store the subsequence in W[] and its
 * length in Wn. Your implementation must run in time O(Sn Tn).
 *
 * The template is there to handle the input and output for you. If you
 * want to test your implementation, check out the Input and Output
 * sections below and the sample files.
 * 
 * You are free to declare any auxilliary functions and variables but
 * the variables are restricted to char and int64_t, and arrays of them.
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
 * - One line containing the string S[]
 * - One line containing the string T[]
 *
 *  Output
 * ====================
 * Output
 *
 * - One line containing the integer Wn
 * - One line containing the string W[]
 *
 *  Limits
 * ====================
 * 1 <= Sn, Tn <= 5000
 * S[i] is a upper case letter, 0 <= i < Sn
 * T[i] is a upper case letter, 0 <= i < Tn
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXN 5001

char S[MAXN], T[MAXN], W[MAXN];
int64_t Sn = 0, Tn = 0, Wn = 0;
int64_t ST[MAXN][MAXN];


void lcs() {
	if((Sn-1)==-1||(Tn-1)==-1){
		return;
	} else if(S[Sn-1]==T[Tn-1]) {
		W[Wn++]=S[Sn-1];Sn--;Tn--;lcs();
	} else if(S[Sn-1]!=T[Tn-1]){
		if(ST[Sn-1][Tn-0]>=ST[Sn-0][Tn-1]){
			Sn--;lcs();
			
		} else {
			Tn--;lcs();
		}
	}
}

void lcslength(){
	int64_t i=0,j=0;
	
	for(i=0;i<=Sn;i++){
		ST[i][0]=0;
	}
	
	for(i=0;i<=Tn;i++){
		ST[0][i]=0;
	}
	
	for(i=1;i<=Sn;i++){
		for(j=1;j<=Tn;j++){
			if(S[i-1] == T[j-1]){
				ST[i][j]=ST[i-1][j-1]+1;
			} else {
				(ST[i][j-1]>ST[i-1][j])?(ST[i][j]=ST[i][j-1]):(ST[i][j]=ST[i-1][j]);
			}
		}
	}
	//for(i=0;i<=Sn;i++){printf("\n"); for(j=0;j<Tn;j++)printf("%"PRId64,ST[i][j]);}
}

int64_t main() {
  gets(S);
  gets(T);
  while (S[Sn]) ++Sn;
  while (T[Tn]) ++Tn;
  lcslength();
  lcs();
  printf("%"PRId64"\n", Wn);
  for (int64_t i = Wn-1; i >= 0; --i) {
    printf("%c", W[i]);
  } puts("");
  return 0;
}
