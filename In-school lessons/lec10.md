# Lec10: Hash Tables
## Hashing
Huge universe $U$ of possible keys.
Much smaller $n$ actual keys.

Design hash function $h: U\rightarrow [m]$
![1761874595312](image/lec10/1761874595312.png)
How to cope with collision?
![1761874611154](image/lec10/1761874611154.png)

### Chaining
![1761874634521](image/lec10/1761874634521.png)
Build a linked list to maintain the keys with same has values.
Each time we insert, insert into the front of the linked list, to make faster.
![1761874797108](image/lec10/1761874797108.png)
The remove calls search first, so reach $O(1)$, if not, should be $O(n)$

Mathcal analysis:

Optimistically assume:
- Each key is equally likely to be mapped to every bucket
- Keys are mapped independently
![1761875036236](image/lec10/1761875036236.png)
$\alpha$ is the size of the linked list in one bucket

So when m is roughly equal to n, hash table cost $O(n)$ space and $O(1)$ time

In reality, “Simple Uniform Hashing” does not hold!
Keys are not that random (they usually have **patterns**)

## Design Hash Functions
![1761876207593](image/lec10/1761876207593.png)
