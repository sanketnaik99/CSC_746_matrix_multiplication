/*
* Name: Sanket Sanjay Naik
* Date: 09/14/2022
* Course: CSC 746
* Assignment: HW2
* SFSU ID: 922245139
*/

#include<iostream>

const char* dgemm_desc = "Blocked dgemm.";

/* This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are n-by-n matrices stored in column-major format.
 * On exit, A and B maintain their input values. */
void square_dgemm_blocked(int n, int block_size, double* A, double* B, double* C) 
{

   int n_blocks = n / block_size;

   for (int i = 0; i < n_blocks; i++){
      for (int j = 0; j < n_blocks; j++){
         for (int k = 0; k < n_blocks; k++){
            
            // mmul on blocks
            for (int a = i*block_size; a < i*block_size + block_size; a++){
               for (int b = j*block_size; b < j*block_size + block_size; b++){
                  for (int c = k*block_size; c < k*block_size + block_size; c++){
                     C[a + b*n] += A[a + c*n] * B[c + b*n];
                  }
               }
            }
         }
      }
   }
}