1-
```
./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0
```
ARG seed 0
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal: 492)
  VA  1: 0x00000061 (decimal:   97) --> SEGMENTATION VIOLATION (SEG1)
  VA  2: 0x00000035 (decimal:   53) --> SEGMENTATION VIOLATION (SEG0)
  VA  3: 0x00000021 (decimal:   33) --> SEGMENTATION VIOLATION (SEG0)
  VA  4: 0x00000041 (decimal:   65) --> SEGMENTATION VIOLATION (SEG0)

```
./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s -1
```
ARG seed -1
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x00000011 (decimal:   17) --> VALID in SEG0: 0x00000011 (decimal: 17)
  VA  1: 0x0000006c (decimal:  108) --> VALID in SEG1: 0x000001ec (decimal: 492)
  VA  2: 0x00000061 (decimal:   97) --> SEGMENTATION VIOLATION (SEG1)
  VA  3: 0x00000020 (decimal:   32) --> SEGMENTATION VIOLATION (SEG0)
  VA  4: 0x0000003f (decimal:   63) --> SEGMENTATION VIOLATION (SEG1)

```
./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 2
```
ARG seed 2
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x0000007a (decimal:  122) --> VALID in SEG1: 0x000001fa (decimal: 506)
  VA  1: 0x00000079 (decimal:  121) --> VALID in SEG1: 0x000001f9 (decimal: 505)
  VA  2: 0x00000007 (decimal:    7) --> VALID in SEG0: 0x00000007 (decimal: 7)
  VA  3: 0x0000000a (decimal:   10) --> VALID in SEG0: 0x0000000a (decimal: 10)
  VA  4: 0x0000006a (decimal:  106) --> SEGMENTATION VIOLATION (SEG1)

2-
Q: What is the highest legal virtual address in segment 0?
A: 0x00000013 (decimal 19)

Q: What about the lowest legal virtual address in segment 1?
A: 0x0000006c (decimal: 108)

Q: What are the lowest and highest illegal addresses in this entire address space?
A:
lowest illegal address  = 0x00000014 (decimal 20)
highest illegal address = 0x0000006b (decimal: 107)

Q: How would you run segmentation.py with the -A flag to test if you are right?
A: 
```
./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -A 20,107 -c
```

3-
```
./segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
```
**Solution:** --b0 0 --l0 2 --b1 16 --l1 2

4-
Q: How should you configure the simulator to do so?
A: Configure it such that sum of the two segments = 90% of the address space.
Ex.
```
./segmentation.py -a 100 -l 45 -L 45
```

Q: Which parameters are important to getting this outcome?
A: Limit registers of both segments.

5- Can you run the simulator such that no virtual addresses are valid? How?
Yes, by setting limit registers to zero.
Ex:
```
./segmentation.py -l 0 -L 0
```
