# Lec1 Intro
## What is *Algorithm*
Any **well-defined** computational procedure that takes some value(s) as **input** and produces some value(s) as **output**.
Another perspective: we can also see an algorithm as a tool/method for 
solving a well-specified computational problem
### Well-defined means?
Problem specified, like sorting a list of numbers, and the procedures should be **clear** and **unambiguous**
**Ill-defined**, like "find the best move in chess", "write a good novel"
A particular input of a problem is called an **instance** of the problem

## What is a *data structure*
A data structure is a way to **store** and **organize** data in order to facilitate **access** and **modifications**.
Picking one appropriate data structure can make a big difference in the efficiency of an algorithm.

## Algorithms and Data Structures are closely related
- An algorithm applies a data structure to solve a problem
- An algorithm needs data structures to work as intended

## Goal of Algorithm Design
- Does it work(correctness)? For every input instance, does it produce the correct output?
- Can I do better(efficiency)? Time and memory usage

## An Introductory Example: Integer Multiplication
Two n-digit nonnegative integers x and y
### The "Grade School" Algorithm
Multiply multiplicand x by each digit of the multiplier y, and add up the results, including carries.
Pseudocode Syntax:
- if and end if to form a block
- for and end for to form a loop
- := for assignment
- = for equality test
```
Procedure GradeMult(x, y)
In: two n-digit positive integers x, y
Out: the product p := x · y
A := split x into an array of its digits // e.g., 1235 -> [1, 2, 3, 5]
B := split y into an array of its digits
product := [1…2n]
for i := 1 to n: 
    carry := 0
    for j := 1 to n: 
        temp := product [i + j - 1] + carry + A[i] * B[j] 
        product [i + j - 1] := temp mod 10
        carry := temp / 10
    end for
    product[i + n] := carry
end for
p := transform the product to integer
return p
```
#### Complexity Analysis
- At most $n^{2}$ multiplications
- Then at most $n^{2}$ additions
- Time complexity: $O(n^{2})$ Two iterations of n

### Use recursion
If n is even, split x and y into two n/2-digit numbers, x -> a b, y -> c d.
if n is odd, one use floor, one use ceil.
$x × y = 10^{n} × (a × c) + 10^{n/2} × (a × d + b × c) + b × d (EQ1)$
Then recursively solve $a × c, a × d, b × c, b × d$

### Karatsuba Algorithm
Do we really need $a × d$ and $b × c$ separately?
‣ No, we only need their sum, that is $a × d + b × c$
Then the question is how can we get a × d + b × c, without the results of a × d and b × c?

Notice that we can get it by: $a × d + b × c = (a + b) × (c + d) - a × c - b × d$
This algorithm reduces multiplication, thus greatly improves the time complexity.
Addition increases but doesn't cost much.

### More Advanced Results
Excluded.

## An Incorrect Algorithm
An *incorrect* algorithm might not be useless.
Correct(perfect) algorithm might not actually exist, and imperfect algorithms may be good enough to produce answers, and can handle 99% cases.
In some cases, we can't even find a correct algorithm.