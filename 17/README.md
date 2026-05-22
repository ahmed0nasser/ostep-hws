1-
```
./malloc.py -n 10 -H 0 -p BEST -s 0
```
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy BEST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList 
compute False

ptr[0] = Alloc(3) returned 1000 (searched 1 elements)
Free List [ Size 1 ]:  [ addr:1003 sz:97 ]

Free(ptr[0]) returned 0
Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:97 ]

ptr[1] = Alloc(5) returned 1003 (searched 2 elements)
Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:92 ]

Free(ptr[1]) returned 0
Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:92 ]

ptr[2] = Alloc(8) returned 1008 (searched 3 elements)
Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1016 sz:84 ]

Free(ptr[2]) returned 0
Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

ptr[3] = Alloc(8) returned 1008 (searched 4 elements)
Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1016 sz:84 ]
 
Free(ptr[3]) returned 0
Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

ptr[4] = Alloc(2) returned 1000 (searched 4 elements)
Free List [ Size 4 ]:  [ addr:1002 sz:1 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

ptr[5] = Alloc(7) returned 1008 (searched 4 elements)
Free List [ Size 4 ]:  [ addr:1002 sz:1 ] [ addr:1003 sz:5 ] [ addr:1015 sz:1 ] [ addr:1016 sz:84 ]

**Note about free list:** it often increases and fragmented as there are no coalescing.

2-
Same as BEST except for ptr[3], ptr[4], and ptr[5] allocations:

ptr[3] = Alloc(8) returned 1016 (searched 4 elements)
Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1024 sz:76 ]

Free(ptr[3]) returned 0
Free List [ Size 5 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:8 ] [ addr:1016 sz:84 ]

ptr[4] = Alloc(2) returned 1024 (searched 5 elements)
Free List [ Size 5 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:8 ] [ addr:1026 sz:74 ]

ptr[5] = Alloc(7) returned 1026 (searched 5 elements)
Free List [ Size 5 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:8 ] [ addr:1033 sz:67 ]

3-
Same as BEST however, allocations of ptr[3], ptr[4], and ptr[5] would speed up as free list is not being exhaustively traversed.

4-
- BEST & WORST do not depend on free list order as they traverse the whole list nevertheless.
- FIRST is sped up when using SIZESORT- ordering as all it always splits the largest free chunk in front of the list, SIZESORT+ performs the same as ADDRSORT in this example.

5-
```
./malloc.py -n 1000 -H 0 -p BEST -s 0
```
Q: What happens to larger allocation requests over time?
A: They get failed often without coalescing and Alloc returns -1.
WORST, FIRST, BEST is the order of policies by number of request failures descendingly without coalescing, with coalescing they are very similar.

Q: How big is the free list over time in each case?
A: Free list tends to be much bigger without coalescing in all policies.
WORST, FIRST, BEST is the order of policies by average free list length descendingly without coalescing, again, with coalescing they are very similar.

Q: Does the ordering of the list matter in this case?
A: It depends on the adopted policy, BEST and WORST results do not change with list ordering, however, for FIRST list ordering matter a lot: SIZESORT+ gives the least amount of failed requests and shorter average free list, ADDRSORT comes after and SIZESORT- is the worst sort according to results.

6-
Q: What happens when you change the percent allocated fraction -P to higher than 50?
A: Average free list length and number of search reduces in all policies.

Q: What happens to allocations as it nears 100?
A: Free list always has one element, there are no difference between policies any more.

Q: What about as the percent nears 0?
A: Free list is fragmented to small chunks accumulated at the front of the list on FIRST & BEST policies, with WORST policy fragmentation is even worse, there are more small fragments now ditributed along the list leading to longer free lists in general.
Noteworthy, with coalescing all these fragmentation problems dissappear when adapting any policy.

6- What kind of specific requests can you make to generate a highly-fragmented free space? see how different policies and options change the organization of the free list. 
We can create workloads that leads to highly-fragmented free list no matter which policy or list ordering are used when alloc size increases in every subsequent request.
- Without coalescing: alloc rate -> 0% (alloc, free) e.g. -A +1,-0,+2,-1,+3,-2.
- With coalescing: alloc rate -> 66.667% (alloc0, alloc1, free0) e.g. -A +1,+2,-0,+3,+4,-2,+5,+6,-4
