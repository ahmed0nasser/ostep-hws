1- CPU Utilization=100%, because all intstructions have 100% chance of being non-I/O

2- 11 time slots

3- First process issues an I/O and being blocked, so cpu runs the other process.
Switching order matters as it increases cpu utilization and decreases overall time.

4- CPU utilization and overall time downgraded to Q2 scenario.

5- Same performance as Q3.

6- No, because p0 has to wait for every other process to complete before it executes another I/O inst.

7- This increases CPU utilization and decreases overall time (higher performance).
Re-running the process that issued an I/O after its I/O completed can be more fair as the process issueing an I/O never left abandoned,
and  better utilize cpu as it is always being busy while the I/O is being fulfilled.
