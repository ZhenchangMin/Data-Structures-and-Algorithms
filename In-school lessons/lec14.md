# Lec14: Some application of DFS
## Directed Acyclic Graphs (DAG)
A graph **without cycles** is called acyclic.
A directed graph **without cycles** is a directed acyclic graph (DAG).
![1764335261428](image/lec14/1764335261428.png)
DAGs are good for modeling relations such as: causalities, hierarchies, and temporal dependencies.
![1764335712488](image/lec14/1764335712488.png)

## Topological Sort
A topological sort of a DAG $G$ is a linear ordering of **its vertices** such that if $G$ contains an edge $(u, v)$ then $u$ appears before $v$ in the ordering.

$E(G)$ defines a partial order over the vertices of $G$, a topological sort gives a total order over the vertices satisfying the partial order defined by $E(G)$.

Can refer to t1 in assignment hw09 as an example of topological sort.

Topological sort is **impossible** if the graph **contains a cycle**.
A given graph may have multiple different valid topological orderings, and how to generate one?

