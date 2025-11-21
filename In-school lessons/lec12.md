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
