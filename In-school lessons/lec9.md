# Lec9: Search Trees
## The Dictionary ADT
A **dictionary** is a collection of items where each item has a **key** that **uniquely identifies** it.
Each element has a `key` and a `value`.
Key must be unique, while values can be duplicated.

Operations:
- Search(S, key): Find an element with the given key.
- Insert(S, x): Insert element x into the dictionary.(If element with same key exists, replace it.)
- Delete(S, x): Delete element x from the dictionary.
- Remove(S, key): Delete the element with the given key.

Typically, keys are from an ordered set, such as integers.
- Min(S) and Max(S): Find the element with the minimum and maximum keys.
- Successor(S, x): Find the smallest element with the key greater than x's key.
- Predecessor(S, x): Find the largest element with the key smaller than x's key.

Implement dictionary.
![1760670659854](image/lec9/1760670659854.png)
BinaryHeap just need to improve its search operation to be $O(\log n)$.

## Binary Search Trees(BST)
A binary search tree (BST) is a binary tree in which each node stores an element, and satisfies the **binary-search-tree property** (BST property):
- For every node x in the tree, if y is a node in the left subtree of x, then $y.key \leq x.key$.
- For every node x in the tree, if y is a node in the right subtree of x, then $y.key \geq x.key$.

Use Inorder Traversal to visit all nodes, we would visit them in ascending order of their keys.

### Search in BST
Given a BST root x and key k, find an element with key k.
Reduce and Conquer:
- If x.key = k then return and we are done!
- If x.key > k then recurse into the BST rooted at x.left.
- If x.key < k then recurse into the BST rooted at x.right.
![1760671249059](image/lec9/1760671249059.png)

#### Complexity of Search in BST
needs $O(h)$ time where h is the height of the tree.
- Worst case: the BST is not balanced, turning into a linked list, and needs $O(n)$ time.
- Best case: the BST is well-balanced, and in this case, h = $\log n$, which means $O(\log n)$ for a balanced BST.

### Max and Min in BST
Minimum: Keep going left until we hit a node without a left child.
Maximum: Keep going right until we hit a node without a right child.
Time: $O(h)$ where h is the height of the tree.

### Successor in BST
`BSTSuccessor(x)`: Find the smallest element in the BST with key value larger than x.key
If the right subtree of x is not empty, then the successor is the minumum element in the right subtree.
So this takes $O(h)$ time.

If no right subtree?
Then the successor is the nearest ancestor of x whose left child is also an ancestor of x.
![1760671899345](image/lec9/1760671899345.png)

### Insert in BST

