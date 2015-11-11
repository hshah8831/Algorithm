/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 7
 * =================================================================
 *
 *  Problem A
 * ====================
 * Implement Dijkstra's Algorithm using a heap in dijkstra(), which finds
 * the shortest distances from vertex S to all vertices in an weighted
 * directed graph with N vertices and M edges. The graph is represented
 * by the arrays A[][], W[][], and An[], where A[U][i] is the i-th
 * neighbor of vertex U, W[U][i] is the weight of the edge (U, A[U][i]),
 * and An[U] is the degree of U. Store the length of the shortest paths 
 * in the array D[], where D[U] is the distance from S to U. If there is
 * no path from S to U, store -1 in D[U]. Your implementation must run in
 * time O((N + M) log N).
 *
 * The template is there to handle the input and output for you. If you
 * want to test your implementation, check out the Input and Output
 * sections below and the sample files.
 * 
 * You are free to declare any auxilliary functions and variables but
 * the variables are restricted to Pair, int64_t and arrays of them.
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
 * - One line containing N, M and S.
 * - M lines containing the list of M space-separated triples (U, V, W),
 *   where (U, V) forms an edge in the graph and W is its weight.
 *
 *  Output
 * ====================
 * Output
 *
 * - One line containing the space-separated list of integers in D[]
 *
 *  Limits
 * ====================
 * 1 <= N <= 10000
 * 0 <= M <= 100000
 * 0 <= S, U, V < N
 * 1 <= W <= 1000000000
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXN 10000
#define INFINITY 1000000001

typedef struct {
  int64_t key, val;
} Pair;

int64_t N, M, S;
int64_t A[MAXN][MAXN], W[MAXN][MAXN];
int64_t An[MAXN] = {0};
int64_t D[MAXN];
Pair H[200000];
int64_t Hp[200000],col[200000];
int64_t Hn;

// your heap implementations here

void swapPair(int64_t i,int64_t j){
	Pair temp;
	temp.key = H[i].key;
	temp.val = H[i].val;
	H[i].key = H[j].key;
	H[i].val = H[j].val;
	H[j].key = temp.key;
    H[j].val = temp.val;
}

int64_t minimum(int64_t root,int64_t left,int64_t right){
	if(H[root].val<H[left].val && H[root].val<H[right].val){
		return root;
	} else if(H[left].val<H[root].val && H[left].val<H[right].val){
		return left;
	} else {
		return right;
	}
}

void minHeapify(int64_t i){
    int64_t left, right;
    right = (i+1) * 2;
	left = ((i+1) * 2) - 1;
	if(left < Hn){
        int64_t j = 0;
        if(right >= Hn){
            j = (H[left].val<H[i].val)?left:i;
        } else {
            j = minimum(i,left,right);
        }
        if(i != j){
            Hp[H[i].key] = j;
            Hp[H[j].key] = i;
            swapPair(i,j);
            minHeapify(j);
        }	
	}
}

void buildMinHeap(){
	int64_t i = Hn/2;
    for(i=Hn/2;i>=0;i--){
		minHeapify(i);
	}
}

Pair extractMinHeap(){
	Pair min;
    min.key = H[0].key;
    min.val = H[0].val;
    if(Hn>0){
        Hp[H[0].key] = -1;
        H[0] = H[Hn-1];
        Hn--;
        minHeapify(0);
    }
	return min;
}

void decreaseKey(int64_t key, int64_t newValue){
    int64_t index = Hp[key];
    int64_t parentIndex = (index - 1)/2;
    H[index].val = newValue;
    while (index >= 0 && H[parentIndex].val > H[index].val){
       swapPair(index, parentIndex);
       index = parentIndex;
       parentIndex = (index - 1)/2;
    }
}

void dijkstra() {
    int64_t i = 0;
	Hn = N;
	for(i=0;i<N;i++){
		D[i] = (i == S)?0:INFINITY;   //initializing all the other distances to INFINITY and source vertex to 0.
		H[i].key = i;                 //initializing heap.
		H[i].val = D[i];
		Hp[H[i].key] = i;
        col[i] = 0;
	}
	buildMinHeap();
	while(Hn){
		int64_t u = extractMinHeap().key;
		int64_t j = 0;
		for(j=0;j<An[u];j++){
			if(col[u] == 0){
	               	int64_t v = A[u][j];
        	       	int64_t oldDist = D[v], newDist = 0;
			if((D[u] + W[u][j]) < D[v]){
                    		newDist = (D[u] + W[u][j]);
	                } else {
        	            newDist = D[v];
                	}
                //newDist = (D[v]<(D[u] + W[u][v]))?D[v]:(D[u] + W[u][v]);
                	if(newDist < oldDist){
                  		D[v] = newDist;
	                    int64_t key = v;
        	            int64_t newValue = newDist;
                	    decreaseKey(key,newValue);
                	}
            		}
		}
        col[u] = 1;
	}
	for(i=0;i<N;i++){
		D[i] = (D[i] == INFINITY)? -1 : D[i];   
        }
}

int64_t main() {
  scanf("%"PRId64"%"PRId64"%"PRId64, &N, &M, &S);
  while (M--) {
    int64_t U, V, w;
    scanf("%"PRId64"%"PRId64"%"PRId64, &U, &V, &w);
    A[U][An[U]] = V;
    W[U][An[U]] = w;
    ++An[U];
  }
  dijkstra();
  for (int64_t i = 0; i < N; ++i)
    printf(i == N-1? "%"PRId64"\n" : "%"PRId64" ", D[i]);
  return 0;
}
