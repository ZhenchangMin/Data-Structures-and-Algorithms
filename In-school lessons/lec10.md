# Lec10: Hash Tables
## Search/Insert/Remove in $O(1)$ time
If keys are all distinct integers from universe $U=\{0, 1, \dots, m-1\}$
Just allocate an array of size $m=|U|$
So that the three operations can be done in $O(1)$ time
![1761880529252](image/lec10/1761880529252.png)
We can call this **direct-address tables**

But issues arose.
The universe can be extremely large, and so the **space complexity** is unacceptable.

## Hashing
Huge universe $U$ of possible keys.
Much smaller $n$ actual keys.
So only spend $n$ space, much smaller than $U$

Design hash function $h: U\rightarrow [m]$
$h(k)$ decides the index of slot in the table for storing $k$
![1761874595312](image/lec10/1761874595312.png)
![1761874611154](image/lec10/1761874611154.png)
How to cope with collision?
Use chaining.

### Chaining
![1761874634521](image/lec10/1761874634521.png)
Build a linked list to maintain the keys with same has values.
Each time we insert, insert into the front of the linked list, to make faster.
![1761874797108](image/lec10/1761874797108.png)
The remove calls search first, so reach $O(1)$, if not, should be $O(n)$

Mathcal analysis:
**Simple Uniform Hashing** Assumption
- Each key is equally likely to be mapped to every bucket
- Keys are mapped independently
![1761875036236](image/lec10/1761875036236.png)
$\alpha$ is the size of the linked list in one bucket

So when m is roughly equal to n, hash table cost $O(n)$ space and $O(1)$ time

In reality, “Simple Uniform Hashing” does not hold!
Keys are not that random (they usually have **patterns**)

## Design Hash Functions
![1761876207593](image/lec10/1761876207593.png)

### The Division Method
Common technique when designing hash functions

Example:
Hash function: h(k) = k mod m
Two keys collide if k1 ≡ k2 (mod m)
How to select m?
![1761876698770](image/lec10/1761876698770.png)
![1761876774051](image/lec10/1761876774051.png)

### The Multiplication Method



### Universal Hashing
Once hash function is **fixed and known**, there must exist a set of “bad” keys that hash to the same value.
Such **adversarial input** will result in poor performance!

Use randomization!
Pick a **random** hash function $h$ when the hash table is first built.
Universal Hash Family
A collection of hash functions $\mathcal{H}$ 



## Open Addressing
No linked lists, all items store in the table, one item per bucket.
Probe a sequence of buckets until an empty one if found, to avoid collision.
![1761877939049](image/lec10/1761877939049.png)

But how the probe sequence is determined?
![1761877971027](image/lec10/1761877971027.png)
Re-define the hash function, with 2 inputs.
![1761879774819](image/lec10/1761879774819.png)
`j` refers to the next table index in the probe sequence.
Why this remove is wrong?
After remove 245, we can't find 321!
![1761878515660](image/lec10/1761878515660.png)
Pseudacode are shown as above, and need to mention the remove operation is special.

### Linear Probing


### Quadratic Probing


### Double Hashing
