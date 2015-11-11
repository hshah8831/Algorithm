/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 5
 * =================================================================
 *
 *  Problem A
 * ====================
 * Implement the Ford--Fulkerson algorithm in FF(), which finds the 
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
 * run in time O(|E| max|f|).
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
int64_t St[20000], top = -1;
int64_t C[10000];

int64_t min(int64_t x, int64_t y) { return x < y ? x : y; }

void add(int u, int v, int uc, int vc) {
  E[En].v = v; E[En].c = uc; E[En].n = cur[u]; cur[u] = En++;
  E[En].v = u; E[En].c = vc; E[En].n = cur[v]; cur[v] = En++;
}

// adjacency_list(u) lists all the neighbors of u
int64_t adjacency_list(int64_t u) {
  for (int64_t i = cur[u]; i != -1; i = E[i].n) {
    printf("%"PRId64"\t", E[i].v);
  }
  printf("\n");
  for (int64_t i = cur[u]; i != -1; i = E[i].n) {
  	printf("%"PRId64"\t", E[i].c);
  }
  printf("\n");
  for (int64_t i = cur[u]; i != -1; i = E[i].n) {
    printf("%"PRId64"\t", E[i].n);
  }
  printf("\n");
  printf("\n");
}

void push(int64_t v) {
        St[++top] = v;
}

int64_t pop() {
        return St[top--];
}

int64_t isStackEmpty() {
        return top<0;
}

int64_t allNeighVisited(int64_t u){
        int64_t temp = 1;
        int64_t i;
        for(i = cur[u]; i != -1; i = E[i].n){
        				int64_t v = E[i].v;
        				temp = temp && ((E[i].c==0) || C[v]);
        }
        return temp;
}

int64_t dfs() {
		int64_t i;
        for(i=0;i<N;i++){
                C[i]=0;
        }
        push(S);
        int64_t j=0;
        C[S]=1;
        while(!isStackEmpty()){
                int64_t u = St[top]; //pop();
                if(u==T){ 
                	return 1;
                }
                if(allNeighVisited(u)){
            		pop();
            		//printf("POP=%"PRId64,pop());
            	} else {
                		int64_t i;
                        for(i = cur[u]; i != -1; i = E[i].n){
                                j=E[i].v;
                                if(C[j]==0 && E[i].c>0){
                                        C[j]=1;
                                        push(j);
                                        break;
                                }
                       }
                }
        }
        return 0;
}

int64_t capacity(int64_t u, int64_t v){
	for(int64_t i = cur[u]; i != -1; i = E[i].n){
		if(E[i].v == v){
			return E[i].c;
		}
	}
}

int64_t bottleneck(){
        int64_t min = capacity(St[0],St[1]),temp=0;
        int64_t i = 0;
        for(i = 0;i <= top;i++){
                temp = capacity(St[i],St[i+1]);
                min = min<temp?min:temp;
        }
        return min;
}

void updateGraph(int64_t min){
        int64_t u,v;
        u = St[0];
        v = St[1];
        int64_t i;
        for(i = 0;i < top;i++){
                u = St[i];
                v = St[i+1];
                int64_t j = cur[u];
                for(j = cur[u]; j != -1; j = E[j].n){
                        if(E[j].v == v){
                                E[j].c = E[j].c - min;
                        }
                }
                u = St[i+1];
                v = St[i];
                for(j = cur[u]; j != -1; j = E[j].n){
                        if(E[j].v == v){
                                E[j].c = E[j].c + min;
                        }
                }
        }
}

void FF() {
        S = 0;
        T = N-1;
        while(dfs()){
            int64_t min = bottleneck();
            //update the capacity of the path
            updateGraph(min);
            //add in the min flow
            F+=min;
            top = -1;
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
  FF();
  printf("%"PRId64"\n", F);
  return 0;
}
