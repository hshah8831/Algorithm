/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 5
 * =================================================================
 *
 *  Problem B
 * ====================
 * Implement the Edmonds--Karp algorithm in EK(), which finds the 
 * maximum flow from vertex 0 to vertex N-1 in a directed graph with
 * N vertices and M edges. You are given the residual network induced
 * by the zero flow f = 0. The residual network is represented by the
 * following data structure:
 *
 *  E[] is an array containg the following information of each edge (u,v)
 *    - E[i].v = v
 *    - E[i].c = c_f(u,v), the residual capacity of (u,v) induced by f
 *    - E[i].n is pointing to the index of next edge (u,w) in the linked
 *    list containing all edges going out from u (see below)
 *
 *  If i is even and E[i] is the edge (u,v), then E[i+1] is always the
 *  backward edge (v,u).
 *
 *  In addition to the edge list E[], each vertex u has a linked list
 *  storing the indices of edges of the form (u,*). The index of the
 *  first edge is stored in cur[i], the index of the next edge is stored
 *  in E[cur[i]].n, and so on. The last edge E[m] in the list has
 *  E[m].n = -1. As an example, adjacency_list(int64d u) shows you how to
 *  enumerate all the neighbors of u.
 *
 * Store the value of the maximum flow in F. Your implementation must
 * run in time O(|V| |E|^2).
 *
 * For this problem, you are NOT allowed to modify main() and add().
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
 * - M lines containing a list of M triples (U, V, C), where (U,V) is
 *   an edge of the directed graph and C is the capacity of the edge (U,V)
 *
 *  Output
 * ====================
 * Output
 *
 * - One line containing the integer F
 *
 *  Limits
 * ====================
 * 1 <= N <= 10000
 * 0 <= M <= 10000000
 * 0 <= U, V < N
 * 0 <= C <= 10000
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

typedef struct {
  int64_t v, c, n;
} Edge;

Edge E[10000000];
int64_t cur[10000];
int64_t En;
int64_t N, M;
int64_t En;
int64_t F;
int64_t S,T,K;
int64_t Q[10000*2], Qh = 0, Qt = 0;
int64_t C[10000];
int64_t D[10000];
int64_t A[10000];
int64_t P[10000];

int64_t min(int64_t x, int64_t y) { return x < y ? x : y; }

void add(int u, int v, int uc, int vc) {
  E[En].v = v; E[En].c = uc; E[En].n = cur[u]; cur[u] = En++;
  E[En].v = u; E[En].c = vc; E[En].n = cur[v]; cur[v] = En++;
}

// adjacency_list(u) lists all the neighbors of u
int64_t adjacency_list(int64_t u) {
  for (int64_t i = cur[u]; i != -1; i = E[i].n) {
    printf("%"PRId64"\n", E[i].v);
  }
}
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
        int64_t i = 0;
        for (i = 0; i <= K; ++i) {
                A[i] = temp;//P[temp];
                temp = P[temp];
        }

        for (i = 0; i <= K; ++i) {
                P[i] = A[K-i];
  
        }
}

int64_t bfs() {
		int64_t i=0;
        for(i=0;i<N;i++){
                D[i]=C[i]=0;
                P[i]=-1;
        }
        Qh =  Qt = 0;
        enqueue(0);
        int64_t j=0;
        while(!isQueueEmpty()){
                int64_t u =  dequeue();
                if(u==(N-1)){ K=D[u];contruct_path(); return 1;}
                for(i = cur[u]; i != -1; i = E[i].n){
                        j=E[i].v;
                        if(C[j]==0 && E[i].c>0){
                                C[j]=1;
                                D[j]=D[u]+1;
                                P[j]=u;
                                enqueue(j);
                        }
                }
                C[u]=2;
        }
		return 0;

}

int64_t capacity(int64_t u, int64_t v){
	int64_t i;
        for( i = cur[u]; i != -1; i = E[i].n){
                if(E[i].v == v){
                        return E[i].c;
                }
        }
}

int64_t bottleneck(){
        int64_t min = capacity(P[0],P[1]),temp=0;
        int64_t i = 0;
        for(i = 0;i < K;i++){
                temp = capacity(P[i],P[i+1]);
                min = min<temp?min:temp;
        }
        return min;
}

void updateGraph(int64_t min){
        int64_t u,v;
        u = P[0];
        v = P[1];
        int64_t i;
        for(i = 0;i < K;i++){
                u = P[i];
                v = P[i+1];
                int64_t j = cur[u];
                for(j = cur[u]; j != -1; j = E[j].n){
                        if(E[j].v == v){
                                E[j].c = E[j].c - min;
                        }
                }
                u = P[i+1];
                v = P[i];
                for(j = cur[u]; j != -1; j = E[j].n){
                        if(E[j].v == v){
                                E[j].c = E[j].c + min;
                        }
                }
        }
}
int64_t EK() {
	S = 0;
        T = N-1;
        F=0;
        while(bfs()){
            int64_t min = bottleneck();

            //update the capacity of the path
            updateGraph(min);
            //add in the min flow
            F+=min;
        }
}

int64_t main() {
  scanf("%"PRId64"%"PRId64, &N, &M);
  for (int64_t i = 0; i < N; ++i) cur[i] = -1;
  En = 0;
  for (int64_t i = 0; i < M; ++i) {
    int64_t x, y, c;
    scanf("%"PRId64"%"PRId64"%"PRId64, &x, &y, &c);
    add(x, y, c, 0);
  }
  EK();
  printf("%"PRId64"\n", F);
  return 0;
}
