# Lec2: Basics of Algorithm Analysis
## Algorithm Evaluation
There're many algorithms to solve a problem, which is better?
Implementation(language, compiler, hardware) and environment matters.
C is faster than most other languages.

## Model of Computation: Turing Machine
This is independent of previous factors.
1. There's a tape with infinite cells, each cell can store a symbol.
2. There's a head, which can read and write symbols on the tape.
3. There's a program, which is a finite set of instructions.
4. The program is executed by the head, and the head moves on the tape.
5. The head can move left or right or halt, and can read or write symbols.
6. The program can be stopped by a special symbol.

Disadvantages of Turing Machine
1. It's too slow.
2. It's too complex.

Running time: Number of steps.
Memory: Number of tape cells utilized.

## Random Access Machine (RAM)
One processor which executes instructions one by one.
There is one memory, whose cells support random access, each of limited size

Running time: Number of primitive operations.
Memory: Number of memory cells utilized.

## Correctness of Algorithm
Specification:
- Precondition(initial condition): specifies what is correct input data.
- Postcondition(final condition): specifies what is desired result.

![1757036212026](image/lec2/1757036212026.png)
### Total correctness
An algorithm is called totally correct for the given specification if and only if for any correct input data it:
1. halts.
2. returns the desired output.

Usually, while checking the correctness of an algorithm it is easier to separately:
- Check whether the algorithm stops
- Then check the remaining part — This remaining part of correctness is called “Partial Correctness” of algorithm

### Partial correctness
An algorithm is partially correct if satisfies the following condition: 
If the algorithm receiving correct input data stops then its result is correct
If doesn't stop, for any case it is partial correct.
![1757036595664](image/lec2/1757036595664.png)

