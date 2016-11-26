```
This program demonstrates the page fault problem. It initializes a global array of 20480 rows that are 4096 long: each row is a page in memory. This program will demonstrate that row operations on this array are much faster than column operations, despite each operation being the same Big O complexity.
```
