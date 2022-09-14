# mmul instructional test harness

This directory contains a benchmark harness for testing different implementations of
matrix multiply for varying problem sizes and, for the blocked mmul implmentation,
at varying block sizes.

The main code is benchmark.cpp, which sets up the problem, iterates over problem
(and block) sizes, sets up the matrices, executes the mmul call, and tests the
result for accuracy by comparing your result against a reference implementation (CBLAS).

Note that cmake needs to be able to find the CBLAS package. For CSC 746 Fall 2021,
this condition is true on Cori@NERSC and on the class VM. It is also true for some
other platforms, but you are on your own if using a platform other than Cori@NERSC
or the class VM.

# Build instructions - general

After downloading, cd into the main source directly, then:

% mkdir build  
% cd build  
% cmake ../  

When building on Cori, make sure you are on a KNL node when doing the compilation. The
Cori login nodes are *not* KNL nodes, the Cori login nodes have Intel Xeon E5-2698
processors, not the Intel Xeon Phi 7250 processors.  The simplest way to do this is
grab an interactive KNL node:
salloc --nodes 1 --qos interactive --time 01:00:00 --constraint knl --account m3930


Special instructions for MacOSX platforms:

On Prof. Bethel's laptop, which is an intel-based Macbook Pro running Big Sur, and
with Xcode installed, cmake can find the BLAS package, but then the build fails with
an error about not being able to find cblas.h.

The workaround is to tell cmake where cblas.h lives by using an environment variable:
export CXXFLAGS="-I /Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A/Headers/"
then clean your build directory (rm -rf * inside build) and run cmake again. 

Note you will need to "locate cblas.h" on your machine and replace the path to cblas.h
in the CXXFLAGS line above with the path on your specific machine.

# Adding your code

For timing:

You will need to modify the benchmark.cpp code to add timing instrumentation, to 
report FLOPs executed, and so forth.


For matrix multiplication:

There are stub routines inside degemm-basic.cpp and dgemm-blocked.cpp where you can
add your code for doing basic and blocked matrix multiply, respectively.

For blocked matrix multiply, in this implementation, the block size is being passed in as
a parameter from the main benchmark.cpp code. You should write your blocked matrix multiply
with the block size parameterized in this fashion (rather than being a hard-coded thing). 

# Results

## Basic

```bash
snaik@nid02389:~/CSC_746/CSC_746_matrix_multiplication/build> ./job-basic
Description:	Basic implementation, three-loop dgemm.

Working on problem size N=64 
 Elapsed time is : 0.00 
Working on problem size N=128 
 Elapsed time is : 0.01 
Working on problem size N=256 
 Elapsed time is : 0.22 
Working on problem size N=512 
 Elapsed time is : 3.34 
Working on problem size N=1024 
 Elapsed time is : 27.01 
snaik@nid02389:~/CSC_746/CSC_746_matrix_multiplication/build> 
```

## Blocked

```bash
snaik@nid02389:~/CSC_746/CSC_746_matrix_multiplication/build> chmod +x ./job-blocked
snaik@nid02389:~/CSC_746/CSC_746_matrix_multiplication/build> ./job-blocked
Description:	Blocked dgemm.

Working on problem size N=64 
Blocked DGEMM 
Block Size = 2
 Elapsed time is : 0.00 
Block Size = 16
 Elapsed time is : 0.00 
Block Size = 32
 Elapsed time is : 0.00 
Block Size = 64
 Elapsed time is : 0.00 
Working on problem size N=128 
Blocked DGEMM 
Block Size = 2
 Elapsed time is : 0.02 
Block Size = 16
 Elapsed time is : 0.01 
Block Size = 32
 Elapsed time is : 0.01 
Block Size = 64
 Elapsed time is : 0.01 
Working on problem size N=256 
Blocked DGEMM 
Block Size = 2
 Elapsed time is : 0.17 
Block Size = 16
 Elapsed time is : 0.16 
Block Size = 32
 Elapsed time is : 0.19 
Block Size = 64
 Elapsed time is : 0.23 
Working on problem size N=512 
Blocked DGEMM 
Block Size = 2
 Elapsed time is : 3.83 
Block Size = 16
 Elapsed time is : 2.34 
Block Size = 32
 Elapsed time is : 2.40 
Block Size = 64
 Elapsed time is : 2.36 
Working on problem size N=1024 
Blocked DGEMM 
Block Size = 2
 Elapsed time is : 31.22 
Block Size = 16
 Elapsed time is : 18.55 
Block Size = 32
 Elapsed time is : 18.30 
Block Size = 64
 Elapsed time is : 18.35 
```

## BLAS

```bash
snaik@nid02389:~/CSC_746/CSC_746_matrix_multiplication/build> chmod +x ./job-blas
snaik@nid02389:~/CSC_746/CSC_746_matrix_multiplication/build> ./job-blas
Description:	Reference dgemm.

Working on problem size N=64 
 Elapsed time is : 0.01 
Working on problem size N=128 
 Elapsed time is : 0.00 
Working on problem size N=256 
 Elapsed time is : 0.00 
Working on problem size N=512 
 Elapsed time is : 0.01 
Working on problem size N=1024 
 Elapsed time is : 0.08 
```