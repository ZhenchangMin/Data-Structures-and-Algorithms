# Lec4: Divide and Conquer
## The Divide-and-Conquer Approach
- Divide the given problem into a number of **subproblems** that are smaller instances of the same problem.
- Conquer the subproblems by solving them **recursively**.
- Use brute-force to solve one subproblem if it is small enough.
- Combine the solutions of subproblems to obtain the solution for the original one.

Use (strong) mathematical induction to prove the correctness of the approach.

## Merge Sort
![mergesort](image/lec4/1.png)
How to merge?
Use two indices, Aindex and Bindex, put the one smaller into the result array, and move the index forward(only the chosen one).
When one index meets the end, copy the rest of the another array into the result and finished.
![merge routine](image/lec4/2.png)
Divide the original array and recursively sort, when meet base case then return and merge.

### Time Complexity of Merge Sort
For subroutine `Merge`: 
![merge time](image/lec4/4.png)
![total time](image/lec4/3.png)
![total time](image/lec4/5.png)
Use iteration to implement merge sort
![total time](image/lec4/6.png)

## Matrix Multiplication
Suppose we wanna multiply two $n\times n$ matrices $X$ and $Y$
