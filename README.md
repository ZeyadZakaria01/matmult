# Matrix Multiplication

This code implements matrix multiplication using threads. There are two versions of the code:

* **matmult_v1** creates a thread for each element in the output matrix.
* **matmult_v2** creates a thread for each row in the output matrix.

The code takes four arguments:

* The pointers to the three matrices A, B, and C.
* The dimensions of the three matrices (l, m, and n).

To run the code, you can use the following command:

```
make
./lab6 A B C l m n
```

For example, to multiply two matrices of size 100x100, you would use the following command:

```
make
./lab6 A B C 100 100 100
```

The output of the code is the multiplied matrix C.


## Makefile Instructions

The Makefile contains the following instructions:

* `lab6`: This is the target that builds the executable file.
* `project.o`: This is the object file for the project.c file.
* `matmult.o`: This is the object file for the matmult.c file.
* `clean`: This target removes all of the object files and the executable file.

To build the executable file, you can use the following command:
```
make
```
To clean the directory, you can use the following command:

```
make clean
```
I hope this is helpful!

