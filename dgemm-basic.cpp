/*
* Name: Sanket Sanjay Naik
* Date: 09/14/2022
* Course: CSC 746
* Assignment: HW2
* SFSU ID: 922245139
*/

#include <iostream>

const char* dgemm_desc = "Basic implementation, three-loop dgemm.";

/*
 * This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are n-by-n matrices stored in column-major format.
 * On exit, A and B maintain their input values.
 */
void square_dgemm(int n, double* A, double* B, double* C) 
{
   // insert your code here: implementation of basic matrix multiple
   for (int i = 0; i < n; i++){
      for (int j = 0; j < n; j++){
         for (int k = 0; k < n; k++){
            C[i + j*n] += A[i + k*n] * B[k + j*n];
         }
      }
   }
}