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
BSTInsert(T,z): Add z to BST T. Notice, insertion **should not break** the BST property.
Just like doing a search in T with key `z.key`. 
This search will fail and **end at a leaf** `y`. Insert z as left or right child of `y`.
![1760672161821](image/lec9/1760672161821.png)
Reach leaf 32 at last and as 36 larger than 32, add to right child of 32.

$O(h)$ where h is the height of the tree.

### Remove in BST
BSTRemove(T,z): Remove element z from T. Notice, removal should not break the BST property.

Case 1: z has no children.
Easily remove z by setting its parent's corresponding pointer to NULL, and delete z.

Case 2: z has one child.
Replace z with its child, and update its parent's pointer to point to its child.

Case 3: z has 2 children.
We must choose either its left or right subtree to replace z, or it would be not connected.
Choose z's successor(or predecessor) to replace z.
As it is a successor, the right subtree would be bigger than it if replace z with its successor.

But if z.right.left is empty? How to choose z's successor?
Just choose z.right as its successor! And replace z with z.right.

If z.right.left is not empty, find the left most node to replace z, and the children of the successor take over the original position of the successor.
![1760672689519](image/lec9/1760672689519.png)
![1760672701941](image/lec9/1760672701941.png)
Use BST to implement the Dictionary ADT.
![1760672726277](image/lec9/1760672726277.png)

### Height of BST
