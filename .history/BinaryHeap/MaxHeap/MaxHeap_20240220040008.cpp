#include <bits/stdc++.h>

using namespace std;
#define hp heap.push
class max_heap
{
private:
    int *arr{};
    int size{};
    int capacity{1000};
    int left(int node)
    {
        int p = 2 * node + 1;
        return (p >= size) ? -1 : p;
    }
    int right(int node)
    {
        int p = 2 * node + 2;
        return (p >= size) ? -1 : p;
    }
    int parent(int node)
    {
        return (node == 0) ? -1 : (node - 1) / 2;
    }
    void heapify_up(int child_pos)
    {
        int parent_pos = parent(child_pos);
        if (child_pos == -1 || arr[parent_pos] >= arr[child_pos])
            return;
        swap(arr[parent_pos], arr[child_pos]);
        heapify_up(parent_pos);
    }
    void heapify_dowen(int parent_pos)
    {
        int child_pos = left(parent_pos);
        int right_child = right(parent_pos);
        if (child_pos == -1)
            return;
        if (right_child != -1 && arr[child_pos] < arr[right_child])
            child_pos = right_child;
        if (arr[parent_pos] < arr[child_pos])
        {
            swap(arr[parent_pos], arr[child_pos]);
            heapify_dowen(child_pos);
        }
    }

public:
    max_heap()
    {
        arr = new int[capacity];
        size = 0;
    }

    bool isempty()
    {
        return size == 0;
    }
    int top()
    {
        return arr[0];
    }
    void push(int val)
    {
        assert(size + 1 <= capacity);
        arr[size++] = val;
        heapify_up(size - 1);
    }

    void pop()
    {
        assert(!isempty());
        arr[0] = arr[--size];
        heapify_dowen(0);
    }
    int sz()
    {
        return size;
    }
};

void create_heap(vector<int> &v)
{
    max_heap heap;
    for (int i = 0; i < (int)v.size(); i++)
    {
        heap.push(v[i]);
    }
    while (!heap.isempty())
    {
        cout << heap.top() << " ";
        heap.pop();
    }
}
class kth_smallest
{
private:
    max_heap q;
    int k{};

public:
    kth_smallest(int k) : k(k) {}
    int next(int new_num)
    {
        if (k != q.sz())
        {
            q.push(new_num);
        }
        else if (q.top() > new_num)
        {
            q.pop();
            q.push(new_num);
        }
        return q.top();
    }
};
int main()
{

    return 0;
}
