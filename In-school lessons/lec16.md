# Lec16: Single-Source Shortest Path
## The Shortest Path Problem
Consider a graph $G=(V,E)$ and a weight function that associates a real-valued weight $w(u,v)$ to each edge $(u, v)$. Given $s$ and $t$ in $V$, what’s the **min weight path** from $s$ to $t$?

Weight are not always lengths. They can represent costs, times, capacities, etc.
The graph can be **directed**, thus $w(u,v)$ is not necessarily equal to $w(v,u)$.
Negative edge weight allowed.
Negative cycle not allowed.

## Single-Source Shortest Path (SSSP)
The SSSP problem: Given a graph $G=(V,E)$ and a weight function $w(u,v)$ for each edge $(u,v)$, given a source node $s$ in $V$, find a shortest path from $s$ to every node $v$ in $V$.

Consider directed graphs without negative cycle.
Case 1: Unit weight
Case 2: Arbitrary positive weight
Case 3: Arbitrary weight without cycle
Case 4: Arbitrary weight

### Case 1: Unit weight
How to solve SSSP in an unit weight graph?
‣ That is, a graph in which each edge is of weight $1$.
"Traverse by layer" in an unweighted graph:
Visit all distance $d$ nodes before visiting any distance $d+1$ nodes, just like BFS.