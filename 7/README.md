1-
SJF:
- response time = (0 + 200 + 400) / 3 = 200
- turnaround time = (200 + 400 + 600) / 3 = 400
FIFO:
- response time = (0 + 200 + 400) / 3 = 200
- turnaround time = (200 + 400 + 600) / 3 = 400

2-
SJF:
- response time = (0 + 100 + 300) / 3 = 133.333
- turnaround time = (100 + 300 + 600) / 3 = 333.333
FIFO:
- response time = (0 + 100 + 300) / 3 = 133.333
- turnaround time = (100 + 300 + 600) / 3 = 333.333

3-
- response time = (0 + 1 + 2) / 3 = 1
- turnaround time = (298 + 499 + 600) / 3 = 465.666

4-
- equal jobs workload
- ascendingly ordered jobs workload

5-
equal jobs & quantum slice = job -> response time in both SJF & RR is equal

6-
increase in response time = sum_i(job_i increase * (#jobs - i)/#jobs)

7-
- N = #jobs
- response time @ q < min job
= (0 + q + 2q + ... + (N-1) * q) / N
= (1 + 2 + ... + (N-1)) * q/N
- Notice that when q > second max job, response time is no longer increasing with q:
increase in response time = (N-1) * delte_q/N < 1
- Worst-case response time is when q > second max job, it can not increase more i.e. the worst.
