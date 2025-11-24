# Lec13: Graphs and Graph Traversal
## Represent Graphs in Computer
### Adjacency Matrix
For the Adjacency Matrix $A=\{a_{ij}\}_{n\times n}$ of a graph $G=(V,E)$, $a_{ij}=1$ if $(i,j)\in E$, otherwise $a_{ij}=0$.
The matrix would be symmetric if $G$ is undirected.
And the matrix costs $O(n^2)$ space, regardless of $m$.
![1763972742214](image/lec13/1763972742214.png)

### Adjacency List
The Adjacency List of $G=(V,E)$ is a collection of $n$ lists, one for each vertex $v\in V$.
In the list for $v$, we store all vertices $w$ such that $(v,w)\in E$.
The space cost is $O(m+n)$.
![1763972815419](image/lec13/1763972815419.png)

### Adjacency Matrix vs. Adjacency List
![1763972854315](image/lec13/1763972854315.png)
If $m$ is much smaller than $n^2$, then the adjacency list is more space-efficient.

## Search in Graphs(Graph Traversal)
Goal: Start at source node $s$ and find some node $t$ in $G$.
Or visit all nodes in $G$ reachable from $s$.

Two basic strategies for graph traversal:
- Breadth-First Search(BFS)
- Depth-First Search(DFS)
Usually use adjacency list to represent graphs in BFS and DFS.

### Breadth-First Search(BFS)
