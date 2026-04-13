1-
```
./mlfq.py -s 1 -n 2 -j 2 -m 5 -M 0
```
Job List:
  Job  0: startTime   0 - runTime   1 - ioFreq   0
  Job  1: startTime   0 - runTime   4 - ioFreq   0

Solution:
[ time 0 ] JOB BEGINS by JOB 0
[ time 0 ] JOB BEGINS by JOB 1
[ time 0 ] Run JOB 0 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 0 (of 1) ]
[ time 0 ] JOB 0 DONE
[ time 1 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 3 (of 4) ]
[ time 2 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 2 (of 4) ]
[ time 3 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 1 (of 4) ]
[ time 4 ] Run JOB 1 at PRIORITY 1 [ TICKS 9 ALLOT 1 TIME 0 (of 4) ]
[ time 4 ] JOB 1 DONE

2-
- Example 1: Figure 8.2
```
./mlfq.py -n 3 -l 0,50,0
```
- Example 2: Figure 8.3 (left)
```
./mlfq.py -n 3 -l 0,180,0:100,20,0
```
- Example 3: Figure 8.3 (right)
```
./mlfq.py -n 3 -S -i 1 -l 0,180,0:100,20,1
```
- Figure 8.4 (left)
```
./mlfq.py -n 3 -S -i 1 -l 0,180,0:100,50,1:100,50,1
```
- Figure 8.4 (right)
```
./mlfq.py -n 3 -S -i 1 -B 100 -l 0,180,0:100,50,1:100,50,1
```
- Figure 8.5 (left)
```
./mlfq.py -n 3 -S -i 1 -l 0,200,0:100,100,9
```
- Figure 8.5 (right)
```
./mlfq.py -n 3 -i 1 -l 0,200,0:100,100,9
```
- Figure 8.6
```
./mlfq.py -n 3 -Q 10,20,40 -l 0,100,0:0,100,0
```
3-
By making queue number = 1
```
./mlfq.py -n 1
```

4- 
At 100 < T <= 200:
Job 1 CPU usage >= 99%
```
./mlfq.py -n 2 -S -q 100 -i 1 -l 0,200,0:100,200,99
```
5-
Boost time = 200ms to achieve >= 5% CPU usage @ q = 10ms

6-
By enabling io bump i.e. -I flag, scheduler encourages I/O-bound jobs even more as it gives them the CPU as soon as their I/O completes.
```
./mlfq.py -n 2 -S -q  -i 1 -l 0,200,0:100,200,99
```
