## Code Questions Solutions:

1-  
Q: What value is the variable in the child process?
A: 100
Q: What happens to the variable when both the child and parent change the value of x?
A: Each of them, parent and child, has its own address space and hence its own copy of variable x. Thus, change is private(isolated) to each process.

2-
Q: Can both the child and parent access the file descriptor returned by open()?
A: Yes.
Q: What happens when they are writing to the file concurrently, i.e., at the same time?
A: Parent and child's write is commited to the file without an issue.

6-
Q: When would waitpid() be useful?
A: In case of multiple child proccesses.

7-
Q: What happens if the child calls printf() to print some output after closing the descriptor?
A: Nothing is printed in the terminal (stdout).
