#include <iostream>
#include <vector>
using namespace std;


struct Node{
    int value;
    Node *parent;
    vector<Node*> children;
};
struct Tree{
    Node *root;
    vector<Node *> nodes;
};

class minHeap {
public:
    Tree heap;
    int size;
    minHeap(){
        this->size = 0;
    }
    minHeap(int size) {
        this->size = size;
        heap.nodes.resize(size);
    }
    void push(int val);
    int pop();
    int top();
    int size(){
        return size;
    }
    void decrease(int i, int k);
};

void minHeap::push(int val){

}

int minHeap::pop(){

}

int minHeap::top(){

}

void minHeap::decrease(int i, int k){

}