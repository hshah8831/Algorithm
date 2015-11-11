/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 4
 * =================================================================
 *
 *  Problem A
 * ====================
 * Use Breadth First Search to implement bfs(), which finds the unique
 * shortest path from vertex S to vertex T in an unweighted graph with
 * N vertices and M edges. The graph is represented by an adjacency
 * list A[][] and An[], where A[U][i] is the i-th neighbor of vertex U,
 * and An[U] is the degree of U. Store the vertices on the shortest path
 * and its length in P[] and K, where P[0] = S and P[K] = T. Your
 * implementation must run in time O(N + M).
 *
 * The template is there to handle the input and output for you. If you
 * want to test your implementation, check out the Input and Output
 * sections below and the sample files.
 * 
 * You are free to declare any auxilliary functions and variables but
 * the variables are restricted to int64_t and arrays of them.
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
 * - One line containing N and M.
 *   One line containing S and T.
 * - M lines containing the list of M pairs of vertices, where
 *   each pair forms an edge (U, V) in the graph.
 *
 *  Output
 * ====================
 * Output
 *
 * - One line containing the integer K
 * - One line containing P[], the vertices on the shortest path from
 *   S to T
 *
 *  Limits
 * ====================
 * 1 <= N <= 10000
 * 0 <= M <= N(N-1)/2
 * 0 <= S, T, U, V < N
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXN 10000

int64_t N, M;
int64_t A[MAXN][MAXN], An[MAXN] = {0};
int64_t S, T;
int64_t Q[MAXN*2], Qh = 0, Qt = 0;
int64_t C[MAXN];
int64_t D[MAXN];
int64_t E[MAXN];
int64_t P[MAXN];
int64_t K;

void enqueue(int64_t v) {
	Q[Qt++] = v;
}

int64_t dequeue() {
	return Q[Qh++];
}

int64_t isQueueEmpty() {
	return Qh>=Qt;
}

void contruct_path(){
	int64_t temp = T;
        for (int64_t i = 0; i <= K; ++i) {
                E[i] = temp;//P[temp];
                temp = P[temp];
        }

	for (int64_t i = 0; i <= K; ++i) {
                P[i] = E[K-i];
        }
}

void bfs() {
	for(int64_t i=0;i<N;i++){
		C[i]=0;
	}
	enqueue(S);
	int64_t j=0;
	while(!isQueueEmpty()){
		int64_t u =  dequeue();
		if(u==T){ K=D[u];contruct_path(); return;} 
		for(int64_t i=0;i<An[u];i++){
			j=A[u][i];
			if(C[j]==0){
				C[j]=1;
				D[j]=D[u]+1;
				P[j]=u;
				enqueue(j);
			}
		}
		C[u]=2;
	}

}

int64_t main() {
  scanf("%"PRId64"%"PRId64, &N, &M);
  scanf("%"PRId64"%"PRId64, &S, &T);
  while (M--) {
    int64_t U, V;
    scanf("%"PRId64"%"PRId64, &U, &V);
    A[U][An[U]++] = V;
  }
  bfs();
  printf("%"PRId64"\n", K);
  for (int64_t i = 0; i <= K; ++i) {
    printf(i == K ? "%"PRId64"\n" : "%"PRId64" ", P[i]);
  }
  return 0;
}
