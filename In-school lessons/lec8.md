# Lec8: Tree
## Tree
A **tree** is a connected, acyclic undirected graph.
- connected: there's a path between any two vertices.
- acyclic: there's no cycle.
- undirected: the edges have no direction.

In CS, we focus on **rooted** trees.

Recursive definition:
- A tree is empty, or
- A tree has a root node with zero or a list of non-empty subtrees.

Root of each subtree is a child of `r`, and `r` is their parent.
Nodes without children are called *leaves*.
Nodes with same parent are called *siblings*.

The path from `r` to `u` is unique, r being ancester of `u`, u being descendant of `r`.

The **depth** of a node `u` is the length of the path from root `r` to `u`.
The **height** of a node `u` is the length of the longest path from `u` to a leaf(longest path to one of its descendants).

Height of every non-leaf node is the maximum height of its children plus one.

A **binary tree** is a tree in which each node has at most two children, left and right.
A **full binary tree** is a binary tree in which every node has **either zero or two** children.