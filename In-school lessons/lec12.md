# Lec12: Disjoint Sets (Union-Find)
## DisjointSet ADT
A **disjoint-set** ADT (also known as Union-Find ADT) maintains a collections of sets $S=\{S_1,S_2,\ldots,S_k\}$ that are disjoint and dynamic.
Each set $S_i$ is represented by "leader" element chosen from $S_i$.

DisjointSet ADT supports the following operations:
- MakeSet(x): Create a new set $S_i=\{x\}$ containing only element $x$ and add it to $S$.
- Union(x, y):  find the sets containing $x$ and $y$, say $S_x$ and $S_y$, respectively. Remove $S_x$ and $S_y$ from $S$ and add $S_x\cup S_y$ to $S$.
- Find(x): Return a pointer to the leader of the set containing $x$.

A typical application is to compute connected components in a graph.
![1763725440451](image/lec12/1763725440451.png)
What is a connected component?
```
// first connected component
A — B — C
     |
     D

// second connected component
E — F

// third connected component
G
```
Like in this graph we can see 3 connected components.
We can imagine splitting the graph into many connected parts and connected components are the largest connected parts.

### Linked-list implementation of DisjointSet
Basic idea: Use linked-list to represent and store each set $S_i$.

Every set object has two pointers:
- `head`: points to the head of the set.
- `tail`: points to the tail of the set.
The linked-list contains the elements in the set $S_i$.
Each element has a pointer pointing back to the set object, and the leader of a set is the first element in the linked-list.
![1763729495953](image/lec12/1763729495953.png)

Operation implementation:
- MakeSet(x): Create a linked list containing only $x$. $O(1)$
- Find(x): Follow pointer from $x$ back to the set object, then return pointer to the first element in the linked-list. $O(1)$
- Union(x,y): Append list of $S_y$ to the end of list of $S_x$.  $O(1)$
Update `tail` of $S_x$ to point to the last element of $S_y$ and update all pointer of elements in $S_y$ to point to $S_x$. Time depends on size of $S_y$.
![1763882819332](image/lec12/1763882819332.png)
And so, the time complexity of this sequence of operations is $O(n^2)$ cuz Union is so expensive!

To improve that, we use **Weighted-union heuristic** (or, union-by-size)
Basic idea is that we always append the smaller set to the larger set.
![1763882927408](image/lec12/1763882927408.png)
So that the time complexity of this sequence of operations drops to $O(n)$

How about the worst case?
With any sequence of $n+1$ MakeSet operations, and $n$ Union operations, what is the worst-case time complexity of this sequence of operations?
$O(n\log n)$
![1763883314289](image/lec12/1763883314289.png)

### Rooted-tree implementation of DisjointSet
