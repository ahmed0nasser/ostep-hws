2-
Q: How should page-table size change as the address space grows?
A: Page-table size grows.

Q: As the page size grows?
A: Page-table size shrinks.

Q: Why not use big pages in general?
A: Because it can be inefficient and a waste of space (internal fragmentation).

3- What happens as you increase the percentage of pages that are allocated in each address space?
The higher the percentage of allocated pages, the more successful virtual address translations requests.

4- Which of these parameter combinations are unrealistic? Why?
- `-P 8 -a 32 -p 1024 -v -s 1`: unrealistically small address-space however, understandable compared to the size of physical memory.
- `-P 8k -a 32k -p 1m -v -s 2`: looks realistic, can support up to 4 different address-spaces.
- `-P 1m -a 256m -p 512m -v -s 3`: address-space seems to be very huge compared to physical memory.

5- Can you find the limits of where the program doesn’t work anymore?
- `-P 8 -a 1024 -p 1024`: physical memory size must be GREATER than address space size (for this simulation).
- `-P 8 -a 1023 -p 1024`: address space must be a multiple of the pagesize.
- page-size, address-space and physical memory size all must be non-zero.
