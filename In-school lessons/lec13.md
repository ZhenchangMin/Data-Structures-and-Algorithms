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
Basic idea: start at source node $s$, and visit other nodes reachable from $s$ layer by layer.
![1763993977287](image/lec13/1763993977287.png)
![1763993986825](image/lec13/1763993986825.png)

#### Implementation of BFS
Use a FIFO queue to store nodes to visit.
Nodes have 3 status:
- undiscovered(WHITE): not in queue yet
- discovered but not visited(GRAY): in queue but not visited yet
- visited(BLACK): ejected from queue and visited(all its neighbors)
![1764051295715](image/lec13/1764051295715.png)
c refers to color, d refers to distance, and p refers to parent.
We keep the parent of each node to track the path from source node $s$ to any node $v$.
![1764051429209](image/lec13/1764051429209.png)
In this explanation of execution, we clearly see how the queue works, and the number of node refers to the distance from $s$(depth).

#### Performance of BFS
![1764051574424](image/lec13/1764051574424.png)
For adjacency list, the time complexity is $O(m+n)$.
We process $n$ nodes and $m$ edges and so the time complexity is $O(m+n)$.

If the graph is not connected, we just need to run BFS for each connected component.

### Depth-First Search(DFS)
![1764052464054](image/lec13/1764052464054.png)
![1764052724341](image/lec13/1764052724341.png)
![1764052742637](image/lec13/1764052742637.png)
![1764052789567](image/lec13/1764052789567.png)
Total runtime of DFS is $O(m+n)$.
