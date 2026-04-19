1-
```
./lottery.py -j 3 -s 1
```
ARG jlist 
ARG jobs 3
ARG maxlen 10
ARG maxticket 100
ARG quantum 1
ARG seed 1

Here is the job list, with the run time of each job: 
  Job 0 ( length = 1, tickets = 84 )
  Job 1 ( length = 7, tickets = 25 )
  Job 2 ( length = 4, tickets = 44 )


Here is the set of random numbers you will need (at most):
Random 651593
Random 788724
Random 93859
Random 28347
Random 835765
Random 432767
Random 762280
Random 2106
Random 445387
Random 721540
Random 228762
Random 945271

**Solution**
Random 651593 -> Winning ticket 119 (of 153) -> Run 2
  Jobs:  ( job:0 timeleft:1 tix:84 ) ( job:1 timeleft:7 tix:25 ) (* job:2 timeleft:4 tix:44 )
Random 788724 -> Winning ticket 9 (of 153) -> Run 0
  Jobs:  (* job:0 timeleft:1 tix:84 ) ( job:1 timeleft:7 tix:25 ) ( job:2 timeleft:3 tix:44 )
--> JOB 0 DONE at time 2
Random 93859 -> Winning ticket 19 (of 69) -> Run 1
  Jobs:  (* job:1 timeleft:7 tix:25 ) ( job:2 timeleft:3 tix:44 )
Random 28347 -> Winning ticket 57 (of 69) -> Run 2
  Jobs:  ( job:1 timeleft:6 tix:25 ) (* job:2 timeleft:3 tix:44 )
Random 835765 -> Winning ticket 37 (of 69) -> Run 2
  Jobs:  ( job:1 timeleft:6 tix:25 ) (* job:2 timeleft:2 tix:44 )
Random 432767 -> Winning ticket 68 (of 69) -> Run 2
  Jobs:  ( job:1 timeleft:6 tix:25 ) (* job:2 timeleft:1 tix:44 )
--> JOB 2 DONE at time 6
Random 762280 -> Winning ticket 5 (of 25) -> Run 1
  Jobs:  (* job:1 timeleft:6 tix:25 )
Random 2106 -> Winning ticket 6 (of 25) -> Run 1
  Jobs:  (* job:1 timeleft:5 tix:25 )
Random 445387 -> Winning ticket 12 (of 25) -> Run 1
  Jobs:  (* job:1 timeleft:4 tix:25 )
Random 721540 -> Winning ticket 15 (of 25) -> Run 1
  Jobs:  (* job:1 timeleft:3 tix:25 )
Random 228762 -> Winning ticket 12 (of 25) -> Run 1
  Jobs:  (* job:1 timeleft:2 tix:25 )
Random 945271 -> Winning ticket 21 (of 25) -> Run 1
  Jobs:  (* job:1 timeleft:1 tix:25 )
--> JOB 1 DONE at time 12

2-
- What happens when the number of tickets is so imbalanced?
The job with more tickets seemingly always dominates.

- Will job 0 ever run before job 1 completes? How often?
P(job 0 ever runs before job 1 completes) = P(job 0 runs at least once in the first 10 runs)
Thus by complementary,
P(Job 0 runs at least once) = 1 − P(Job 0 never wins before Job 1 gets 10 wins)
P(Job 0 never runs) = P(Job 1 gets 10 consecutive wins) = (100/101)^10
P(Job 0 runs at least once) = 1 − (100/101)^10 = 0.09471304530701674

- In general, what does such a ticket imbalance do to the behavior of lottery scheduling?
It leads to job 1 dominating CPU usage and starvation of job 0, which extremely destroys lottery scheduler's proporitonal fairness guarantee.

3- When running with two jobs of length 100 and equal ticket allocations of 100, how unfair is the scheduler?
```
./lottery.py -s 1 -l 10:100,10:100 -c
```
seed=1: Job 0->20, Job 1->16. unfairness=0.8
seed=2: Job 0->19, Job 1->20. unfairness=0.95
seed=3: Job 0->20, Job 1->19. unfairness=0.95
seed=4: Job 0->19, Job 1->20. unfairness=0.95
seed=5: Job 0->20, Job 1->16. unfairness=0.8
seed=6: Job 0->18, Job 1->20. unfairness=0.9
seed=7: Job 0->14, Job 1->20. unfairness=0.7
seed=8: Job 0->20, Job 1->15. unfairness=0.75
=> Unfairness is gaussian distribution with mean=1

4- How does your answer to the previous question change as the quantum size (-q) gets larger?
Mean does not change, yet variance increases i.e. the larger the quantum size the wider the distribution.
