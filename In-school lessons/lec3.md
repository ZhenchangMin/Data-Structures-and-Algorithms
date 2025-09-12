# Lec3: Basic Data Structures
## Data Structure
A data structure is a way to store and organize data in order to facilitate access and modications.

## Abstract Data Type(ADT)
A data structure usually provides an interface, also called an ADT
An ADT speci es what a data structure "can do" and "should do", but not how to do them.
**Example:**
ADT: `List`, supports `get`, `set`, `remove`, `add` ...
Data Structure: `Linked List`, `Array List` ...
A data structure is a specific implementation of ADT
An ADT is a **logical description**, and a data structure is a **concrete implementation**.

### The Quene ADT
**Quene** ADT represents a collection of items in which we could `add` and `remove` them

#### FIFO Quene
The first-in-first-out Quene, items are removed in the same order as they're added.
- Add(x) or Enqueue(x): add x to the end of the queue
- Remove() or Dequeue(): remove the first item from the queue

#### LIFO Quene: Stack
The most recently adder item is the next to be removed.
- Add(x) or Push(x): add x to the top of the stack
- Remove() or Pop(): remove the item a the top of the stack

### The Deque ADT
Deque(Double-Ended Quene), represents a sequence of items with a front and a back, supporting:
- AddFirst(x): add x to the front of the queue
- AddLast(x): add x to the back of the queue.
- RemoveFirst(): remove the first item y from queue, return y.
- RemoveLast(): remove the last item y from queue, return y.

A Deque is a generalization of FIFO and LIFO Quene, and can implement both of them.

### The List ADT
A List is a sequence of items and keeping track on their index, supporting:
- Size(): return n, the length of the list
- Get(i): return xi
- Set(i,x): set xi = x
- Add(i,x): set xj+1 = xj for n ≥ j ≥ i, set xi = x, increase list size by 1
- Remove(i): set xj = xj+1 for n − 1 ≥ j ≥ i, decrease list size by 1

List can implement Deque.

#### Using Array to Implement List - Arraylist
- Size(): always $\Theta(1)$
- Get(i): always $\Theta(1)$
- Set(i, x): always $\Theta(1)$
- Add(i, x): $\Theta(1)$ to $\Theta(n)$
- Remove(i): $\Theta(1)$ to $\Theta(n)$

Queries and updates are fast, while modifications are fast at end, slow at front or middle.
So Arraylist is fast for Stack, slow for FIFO Quene.
