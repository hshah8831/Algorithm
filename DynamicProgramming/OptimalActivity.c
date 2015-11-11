/* ------------------------------------------------------------------
 * CS5800: Algorithms, Summer 2015
 * Homework 3
 * =================================================================
 *
 *  Problem B
 * ====================
 * Given two arrays S[] and T[] of size N, where [S[i], T[i]) is the
 * time interval of the i-th out of N activity, implement
 * activity_select() that computes the maximum-size subset of the
 * mutally compatible activities and store the indexes of the subset,
 * ordered by their intervals, in array A[] and the size of the subset
 * in M. Your implementation must run in time O(N log N).
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
 * - One line containing the value N, the number of activities.
 * - N lines containing a list of N pairs of integers, where each pair
 *   (S[i], T[i]) indicates the time interval of an activity.
 *
 *  Output
 * ====================
 * Output
 *
 * - One line containing M.
 * - A space separated list of M integers, the indexes of the
 *   maximum-size subset of the mutally compatible activities, sorted
 *   by their time intervals.
 *
 *  Limits
 * ====================
 * 1 <=   N  <= 100000
 * 1 <=  S[i], T[i] <= 2^63-1, for 0 <= i < N
 *
 ------------------------------------------------------------------ */
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define MAXN 100000

int64_t S[MAXN], T[MAXN], A[MAXN];
int64_t N, M;

int64_t activity_select() {
}

int64_t main() {
  scanf("%"PRId64, &N);
  for (int64_t i = 0; i < N; ++i)
    scanf("%"PRId64"%"PRId64, &S[i], &T[i]);
  activity_select();
  printf("%"PRId64"\n", M);
  for (int64_t i = 0; i < M; ++i)
    printf(i == M-1 ? "%"PRId64"\n" : "%"PRId64" ", A[i]);
  return 0;
}
