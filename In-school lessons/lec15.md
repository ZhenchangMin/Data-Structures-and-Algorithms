# Lec15: Minimal Spanning Tree
## Minimum Spanning Tree(MST)
Consider a connected, undirected, weighted graph $G = (V, E)$
A **spanning tree** of $G$ is a subgraph that is a tree and connects all the vertices together, and contains a subset of the edges of $G$.
A **minimum spanning tree** is a spanning tree with total weight less than or equal to the weight of every other spanning tree.

## Computing MST
Firstly, we consider a generic method:
- Start with all nodes and an empty set of edges $A$.
- Find some edges(safe edges) that can be added to $A$, maintaining the loop invariant that $A$ is a subset of some MST.
- Repeat until $A$ forms a spanning tree, that is, until it has $|V| - 1$ edges.

**How to find safe edges?**
