1- Program exits with segmentation fault error.

2- gdb shows segmentation fault error as well.

3- valgrind reports that there is an invalid read, not stacked or malloced or freed, of size 4 bytes and specify its location in null.c file.

4- gdb cannot find the memory leak problem, but valgrind can.

5-
Program runs and terminates silently, seemingly correct. 
However, when run it using valgrind and analyze it with  memcheck, it catches the invalid write bug.
The program is not correct as it tries to write in unallocated memory.

6- Program runs and prints data[5]=0. valgrind catches and reports the invalid read bug.

7- 
Compiler warning + when run, gives "free(): invalid pointer" error. no need for valgrind to catch this.
