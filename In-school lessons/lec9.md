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

## Binary Search Trees(BST)
