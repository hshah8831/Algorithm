/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 6
 * =================================================================
 *
 *  Problem A
 * ====================
 * Implement a dictionary data structure using A[] that supports the
 * following 3 operations in O(log N) time, where N is the total
 * number of elements in the data structure.
 *
 * - insert(int64_t x) inserts the value x to the dictionary
 * - delete(int64_t x) deletes the value x from the dictionary
 * - search(int64_t x) returns 1 if x is in the dictionary, and 0
 *   otherwise.
 *
 * You must not use any dynamic memory allocation function such as
 * malloc, realloc, calloc, or free.
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
 * - One line containing M
 * - M lines containing a list of pairs (O, V), where the value of O
 *   indicates the operation to perform on the value V:
 *     0 V : Insert V to the dictionary
 *     1 V : Delete V from the dictionary
 *     2 V : Search for V in the dictioary
 *
 *  Output
 * ====================
 * Output
 *
 * - For each Search operation, output a line containing its return value
 *   (i.e. 0 or 1)
 *
 *  Limits
 * ====================
 * 1 <= N <= 1000000
 * 1 <= M <= 2000000
 * 0 <= V <= 2^63 - 1
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

//#define MAXN 10000000

#define MAXN 100

int64_t T[MAXN] = {-1};
int64_t N = 0, M, BP = 0;

struct Node
{
   int64_t  key;
   int64_t  level;
   int64_t  right;
   int64_t  left;
   int64_t  parent;
};

struct Node A[MAXN] = {0};

void swap(int64_t *x, int64_t *y){
	int64_t temp = *x;
	*x = *y;
	*y = *x;
}

void swapNode(struct Node *x, struct Node *y){
        struct Node temp = *x;
        *x = *y;
        *y = temp;
}
/*
void rightRotation(int64_t x){
        int64_t root = x, left = A[x].left;
	A[A[x].left].parent = A[x].parent;
	A[x].parent = x;
        swapNode(&A[x], &A[A[x].left]);
        int64_t temp = A[x].right;
        //A[x].right = A[left].left;
	A[x].right = left;
        A[left].left = temp;
	//A[temp].parent=left;
}

void leftRotation(int64_t x){
        int64_t root = x, right = A[x].right;
	A[A[x].right].parent = A[x].parent;
        A[x].parent = x;
        swapNode(&A[x], &A[A[x].right]);
        int64_t temp = A[x].left;
        //A[x].left = A[right].right;
	A[x].left = right;
        A[right].right = temp;
}*/

void rightRotation(int64_t x){
        int64_t root = x, left = A[x].left;
        A[A[x].left].parent = A[x].parent;
        A[x].parent = x;
        A[A[left].left].parent = x;
        A[A[x].right].parent = left;
        swapNode(&A[x], &A[A[x].left]);
        int64_t temp = A[x].right;
        A[x].right = left;
        A[left].left = temp;
}

void leftRotation(int64_t x){
        int64_t root = x, right = A[x].right;
        A[A[x].right].parent = A[x].parent;
        A[x].parent = x;
        A[A[right].right].parent = x;
        A[A[x].left].parent = right;
        swapNode(&A[x], &A[A[x].right]);
        int64_t temp = A[x].left;
        A[x].left = right;
        A[right].right = temp;
}

void skew(int64_t x){
	if(A[A[x].left].level == A[x].level){
		rightRotation(x);
	}
}

void split(int64_t x){
	if(A[A[A[x].right].right].level == A[x].level){
		leftRotation(x);
		A[x].level++;
	}
}

void decreaseLevel(int64_t x){
	if(A[x].level - A[A[x].right].level >=2 || A[x].level - A[A[x].left].level >=2 ){
		A[x].level--;
	}
	if(A[A[x].right].level == A[x].level + 1){
		A[A[x].right].level--;
	}
}

int64_t search(int64_t x) {
	int64_t ret = 0;
        for(int64_t i = 0;i < N;i++){
                T[i]=-1;
        }
        int64_t j = 0;
        if(N == 0){
                ret = 0;
        }
        else{
                int64_t i = 0;
                do{
                        if(A[i].key == x){
                          T[j++] = i;
                          ret = 1;
			  break;
                        }
                        else if(x > A[i].key){
                          T[j++] = i;
                          i = A[i].right;
                        }
                        else if(x < A[i].key){
                          T[j++] = i;
                          i = A[i].left;
                        }
		}while(i != -1);
                BP = j;
        }
        return ret;
}

void insert(int64_t x) {
	if(search(x) == 0){
		A[N].key = x;
		A[N].level = 1;
		A[N].right = -1;
		A[N].left = -1;
		A[N].parent = T[BP-1];
		if(A[N].key > A[T[BP-1]].key && BP>0){
			A[T[BP-1]].right = N;
		} else if(A[N].key < A[T[BP-1]].key && BP>0){
			A[T[BP-1]].left = N;
		}
		N++;
		int64_t j = BP-1;
	        for(;j>=0;j--){
        	        skew(T[j]);
                	split(T[j]);
	        }
	}
}

/*void delete(int64_t x) {
	if(search(x)){
		int64_t i = BP - 1, delIndex = BP - 1;
		if(!(A[i].right == -1 && A[i].left == -1)){
			T[BP++] = A[i].right;
			i = A[i].right;
			while(!(A[i].right == -1 && A[i].left == -1)){
				T[BP++] = A[i].left;
				i = A[i].left;
			}
			swap(&A[T[delIndex]].key, &A[T[BP-1]].key);
			if(A[T[BP-1]].key > A[T[BP-2]].key ){
				A[T[BP-2]].right = -1;
			} else {
				A[T[BP-2]].left = -1;
			}
		} else {
			A[A[i].parent].left = -1;
			A[A[i].parent].right = -1;
		}
		int64_t j = BP-1;
		for(j = BP-1;j>=0;j--){
			decreaseLevel(T[j]);
			skew(T[j]);
			skew(A[T[j]].right);
			skew(A[A[T[j]].right].right);
			split(T[j]);
			split(A[T[j]].right);
		}
	}
}*/

void deFragment(int64_t i){
	swapNode(&A[i],&A[--N]);
        if(A[i].key > A[A[i].parent].key){
	        A[A[i].parent].right = i;
        } else {
        	A[A[i].parent].left = i;
        }
}

void delete(int64_t x) {
        if(search(x)){
                int64_t i = BP - 1, delIndex = BP - 1;
                if(!(A[i].right == -1 && A[i].left == -1)){
                        T[BP++] = A[i].right;
                        i = A[i].right;
                        while(!(A[i].right == -1 && A[i].left == -1)){
                                T[BP++] = A[i].left;
                                i = A[i].left;
                        }
                        swap(&A[T[delIndex]].key, &A[T[BP-1]].key);
                        if(A[T[BP-1]].key > A[T[BP-2]].key ){
                                A[T[BP-2]].right = -1;
                        } else {
                                A[T[BP-2]].left = -1;
                        }
                } else if( (A[i].right == -1 && A[i].left != -1) || (A[i].right != -1 && A[i].left == -1)) {
			if(A[i].right == -1 && A[i].left != -1){
				A[A[i].left].parent = A[i].parent;
				swapNode(&A[i],&A[A[i].left]);
			} else {
				A[A[i].right].parent = A[i].parent;
				swapNode(&A[i],&A[A[i].right]);
				
			}
			deFragment(i);
		} else {
           		if(A[i].key > A[A[i].parent].key){
         			A[A[i].parent].right = -1;
		        } else {
                		A[A[i].parent].left = -1;
		        }
			deFragment(i);
                }
                int64_t j = BP-1;
                for(j = BP-1;j>=0;j--){
                        decreaseLevel(T[j]);
                        skew(T[j]);
                        skew(A[T[j]].right);
                        skew(A[A[T[j]].right].right);
                        split(T[j]);
                        split(A[T[j]].right);
                }
        }
}


int64_t main() {
  scanf("%"PRId64, &M);
  while (M--) {
    int64_t O, V;
    scanf("%"PRId64"%"PRId64, &O, &V);
    if (O == 0) insert(V);
    else if (O == 1) delete(V);
    else if (O == 2) printf("%"PRId64"\n", search(V));
  }
  for(int64_t i = 0;i < N;i++){
	printf("%"PRId64"key: %"PRId64"parent: %"PRId64" left: %"PRId64" right: %"PRId64" level: %"PRId64"\n",i,A[i].key,A[i].parent,A[i].left,A[i].right,A[i].level);
  }
  printf("\n Path: ");
  for(int64_t i = 0;i < BP;i++)printf("\t %"PRId64,T[i]);
  printf("\n");
  return 0;
}
