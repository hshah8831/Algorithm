/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 2
 * =================================================================
 *
 *  Problem C
 * ====================
 * Implement closest_pair() that finds the closest pair of N points,
 * sorted by X-coordiates in array X[] and by Y-coordiates in array Y[]
 * , and store the pair of points in (P.x, P.y) and (Q.x, Q.y). Your
 * implementation must run in time O(N log N).
 *
 * The template is there to handle the input and output for you. If you
 * want to test your implementation, check out the Input and Output
 * sections below and the sample files.
 *
 * You are free to declare any auxilliary functions and variables but
 * the variables are restricted to int64_t, Pt and arrays of them.
 *
 * You are not allowed to use any preprocessor commands and library
 * functions that are not in the template.
 *
 * To compile, type (without $):
 * $ make C
 *
 *  Input
 * ====================
 * There will be:
 *
 * - One line containing the value N, the number of points.
 * - N lines containing a list of N pairs of integers, where
 *   each pair (X[i].x, X[i].y) indicates the position of the points
 *   sorted by X-coordinates.
 * - N lines containing the list of N pairs of integers, where
 *   each pair (Y[i].x, Y[i].y) indicates the position of the points
 *   sorted by Y-coordinates.
 *
 *  Output
 * ====================
 * Output one line containing 4 space separated integers P.x, P.y, Q.x
 * and Q.y, the closest pair of points (P.x, P.y) and (Q.x, Q.y).
 * 
 *
 * 
 *  Limits
 * ====================
 * 1 <=   N  <= 100000
 * -5000000 <= X[i].x <  5000000, for 0 <= i < N
 * -5000000 <= X[i].y <  5000000, for 0 <= i < N
 * -5000000 <= Y[i].x <  5000000, for 0 <= i < N
 * -5000000 <= Y[i].y <  5000000, for 0 <= i < N
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXN 100000

typedef struct {
  int64_t x, y;
} Pt;

int64_t N;
Pt X[MAXN];
Pt Y[MAXN];
Pt P, Q;

// is_closer_than(P1, P2, d) returns 1 if P1 and P2 are closer
// than sqrt(d), and 0 otherwise.
int64_t is_closer_than(Pt P1, Pt P2, int64_t d) {
  int64_t dx = P1.x - P2.x;
  int64_t dy = P1.y - P2.y;
  return dx*dx + dy*dy < d;
}

int64_t distance_square(Pt P1, Pt P2){
	int64_t dx = P1.x - P2.x;
	int64_t dy = P1.y - P2.y;
	return dx*dx + dy*dy;
}

void bruteforce(int64_t low, int64_t length){
	int64_t min = distance_square(X[low],X[low+1]),temp=0;
	for(int64_t i = low;i<(low+length);i++){
		for(int64_t j=i+1;j<(low+length);j++){
			temp = distance_square(X[i],X[j]);
			if(temp<min){
				min=temp;
				P = X[i];
				Q = X[j];
			}
		}
	}
}

void closest_pair(int64_t low, int64_t length){
//	printf("\nentered closest_pair with low = %"PRId64"length = %"PRId64,low,length);
	if(length == 2){
		P = X[low];
		Q = X[low+1];
		//return dist(X[low],X[low+1]) // base
	} else if(length==3){
		bruteforce(low,length);
	} else if(length>3){
//	printf("\nentered else");
	closest_pair(low,(length/2)); // divide
	Pt pL1 = P, pL2 = Q;
//	int64_t d1 = (pL2.x - pL1.x)*(pL2.x - pL1.x) + (pL2.y - pL1.y)*(pL2.y - pL1.y);
	int64_t d1 = distance_square(pL1,pL2);
//	printf("\ndL = %"PRId64,d1);
	closest_pair(low+length/2,(length/2) + (length%2));
	Pt pR1 = P, pR2 = Q;
//	int64_t d2 = (pR2.x - pR1.x)*(pR2.x - pR1.x) + (pR2.y - pR1.y)*(pR2.y - pR1.y);
	int64_t d2 = distance_square(pR1,pR2);
//	printf("\tdR = %"PRId64,d2);
	int64_t d = 0;
	if(d1<d2){
		d=d1;
		P = pL1;
		Q = pL2;
	} else {
		d=d2;
		P = pR1;
		Q = pR2;
	}
//	printf("\tdmin = %"PRId64,d);
	// Sy = points in Py within d of L // merge
	Pt Sy[length],mid;
	int64_t j =0;
	mid.x = X[length/2].x;
	mid.y = X[length/2].y;
	for(int64_t i = low;i<(low+length);i++){
		mid.y = X[i].x;
		if(is_closer_than(X[i],mid,d)){
			Sy[j++] = X[i];
		}
	} 
	//For i = 1,...,|Sy|:
	//For j = 1,...,15:
	//d = min( dist(Sy[i], Sy[j]), d )
	for(int64_t i = 0;i<j;i++){
		for(int64_t k = 0; k<15;k++){
			if(is_closer_than(Sy[i],Sy[k],d)){
				P = Sy[i];
				Q = Sy[k];
				int64_t temp = distance_square(Sy[k],Sy[i]);
				(temp<d)?(d=temp):(d=d);
			}
		}
	}
//	Return d
	}
//	printf("\t Px = %"PRId64",Py = %"PRId64,P.x,P.y);
//	printf(" Qx = %"PRId64",Qy = %"PRId64,Q.x,Q.y);
}


int64_t main() {
  scanf("%"PRId64, &N);
  for (int64_t i = 0; i < N; ++i)
    scanf("%"PRId64"%"PRId64, &X[i].x, &X[i].y);
  for (int64_t i = 0; i < N; ++i)
    scanf("%"PRId64"%"PRId64, &Y[i].x, &Y[i].y);
  closest_pair(0,N);
  printf("%"PRId64" %"PRId64" %"PRId64" %"PRId64"\n", P.x, P.y, Q.x, Q.y);
  return 0;
}
