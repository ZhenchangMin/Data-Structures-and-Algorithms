# Lec17: All-Pairs Shortest Path
## All-Pairs Shortest Path(APSP) Problem
Given a graph $G=(V,E)$ with weights $w:E\to\mathbb{R}$. Find the shortest path between all pairs of vertices $(u,v)\in V\times V$.

Straightforward solution for APSP: For each $u\in V$, execute SSSP algorithm once!
![1764785215021](image/lec17/1764785215021.png)
In this way, we solve arbitrary graphs with Bellman-Ford algorithm in $O(n^4)$ time.
Can we do better?
Intuition: modify edge weights **without** changing shortest path, so that Dijkstra's algorithm can work.
![1764929937241](image/lec17/1764929937241.png)
