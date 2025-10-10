#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int pushId = 1;

class minHeap
{
public:
    vector<pair<int, int>> heap;
    vector<int> pos; // hash set, pos[pushId] is the index of pushId in heap
    int size;
    minHeap()
    {
        this->size = 0;
        heap.push_back({0, 0});
        pos.push_back(0); // To make indices start from 1
    }
    minHeap(int size)
    {
        this->size = size;
        heap.resize(size);
    }
    void push(int val);
    int pop();
    int top();
    int getSize()
    {
        return size;
    }
    void decrease(int i, int k);

private:
    void heap_swap(int a, int b);
};

void minHeap::heap_swap(int a, int b)
{
    swap(heap[a], heap[b]);
    pos[heap[a].second] = a;
    pos[heap[b].second] = b;
}

void minHeap::push(int val)
{
    heap.push_back({val, pushId});
    if (pos.size() <= pushId)
    {
        pos.resize(pushId + 1, -1);
    }
    pos[pushId] = size + 1;
    this->size++;
    pushId++;
    int index = size;
    while (index > 1 && heap[index].first < heap[index / 2].first)
    {
        heap_swap(index, index / 2);
        index /= 2;
    }
}

int minHeap::pop()
{
    if (size == 0)
        return -1;

    int result = heap[1].first;
    pos[heap[1].second] = -1;

    if (size == 1)
    {
        heap.pop_back();
        size--;
        return result;
    }
    heap_swap(1, size);
    heap.pop_back();
    size--;

    int index = 1;
    while (index * 2 <= size)
    {
        int left = index * 2;
        int right = index * 2 + 1;
        int smaller = left;
        if (right <= size && heap[right].first < heap[left].first)
        {
            smaller = right;
        }
        if (heap[index].first <= heap[smaller].first)
        {
            break;
        }
        heap_swap(index, smaller);
        index = smaller;
    }
    return result;
}

int minHeap::top()
{
    if (size == 0)
        return -1;
    return heap[1].first;
}

void minHeap::decrease(int i, int k) // must maintain a hash table to store pushId or would get TLE
{
    if (i >= pos.size() || pos[i] == -1)
        return;

    int index = pos[i];
    heap[index].first = k;

    while (index > 1 && heap[index].first < heap[index / 2].first)
    {
        heap_swap(index, index / 2);
        index /= 2;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    minHeap heap = minHeap();
    string op;
    while (cin >> op)
    {
        if (op == "push")
        {
            int val;
            cin >> val;
            heap.push(val);
        }
        else if (op == "pop")
        {
            heap.pop();
        }
        else if (op == "top")
        {
            cout << heap.top() << '\n';
        }
        else if (op == "size")
        {
            cout << heap.getSize() << '\n';
        }
        else if (op == "decrease")
        {
            int index, newVal;
            cin >> index >> newVal;
            heap.decrease(index, newVal);
        }
    }
    return 0;
}