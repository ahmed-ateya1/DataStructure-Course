#include <bits/stdc++.h>

using namespace std;
#define hp heap.push
class min_heap
{
private:
    int *arr{};
    int size{};
    int capacity{1000};
    void heapify_down(int parent_pos)
    {
        int child_pos = left(parent_pos);
        int right_child = right(parent_pos);
        if (child_pos == -1)
            return;
        if (right_child != -1 && arr[right_child] < arr[child_pos])
        {
            child_pos = right_child;
        }
        if (arr[child_pos] < arr[parent_pos])
            swap(arr[parent_pos], arr[child_pos]);
        heapify_down(child_pos);
    }
    int left(int node)
    {
        int p = 2 * node + 1;
        return p >= size ? -1 : p;
    }
    int right(int node)
    {
        int p = 2 * node + 2;
        return p >= size ? -1 : p;
    }
    int parent(int node)
    {
        return node == 0 ? -1 : (node - 1) / 2;
    }
    void heapify_up(int child_pos)
    {
        int par_pos = parent(child_pos);
        if (child_pos == 0 || arr[par_pos] < arr[child_pos])
            return;
        swap(arr[par_pos], arr[child_pos]);
        heapify_up(par_pos);
    }
    bool is_heap(int parent_pos = 0)
    {
        if (parent_pos == -1)
            return true;
        int left_child = left(parent_pos);
        int right_child = right(parent_pos);
        if (left_child != -1 && arr[left_child] < arr[parent_pos])
            return false;
        if (right_child != -1 && arr[right_child] < arr[parent_pos])
            return false;
        return is_heap(left_child) && is_heap(right_child);
    }
    void heapify() // O(n)
    {
        for (int i = size / 2 - 1; i >= 0; --i)
            heapify_down(i);

        assert(is_heap(0));
    }

public:
    min_heap()
    {
        arr = new int[capacity]{};
        size = 0;
    }

    void push(int val) // O(n log n)
    {
        assert(size + 1 <= capacity);
        arr[size++] = val;
        heapify_up(size - 1);
    }

    void pop() // O(n log n)
    {
        assert(!isempty());
        arr[0] = arr[--size];
        heapify_down(0);
    }
    bool isempty()
    {
        return size == 0;
    }
    int top()
    {
        return arr[0];
    }
    void print_less_than(int val, int parent_pos = 0)
    {
        if (parent_pos == -1 || arr[parent_pos] >= val)
            return;
        cout << arr[parent_pos] << " ";
        print_less_than(val, left(parent_pos));
        print_less_than(val, right(parent_pos));
    }
    bool is_heap_array(int *p, int n)
    {
        int *old_array = arr;
        int old_size = size;

        arr = p;
        size = n;
        bool res = is_heap();

        arr = old_array;
        size = old_size;
        return res;
    }
    int sz()
    {
        return size;
    }
    ~min_heap()
    {
        delete[] arr;
        arr = nullptr;
    }
};
class kth_smallest_number
{
private:
    priority_queue<int> q;
    int k{};

public:
    kth_smallest_number(int k) : k(k) {}
    int next(int new_num)
    {
        if (q.size() != k)
        {
            q.push(new_num);
        }
        else if (new_num < q.top())
        {
            q.pop();
            q.push(new_num);
        }
        return q.top();
    }
};

void create_heap(vector<int> &v) // O(n log n)
{
    min_heap heap;
    for (int i = 0; i < (int)v.size(); i++)
        heap.push(v[i]);
    while (!heap.isempty())
    {
        cout << heap.top() << " ";
        heap.pop();
    } // print sorted
}

int main()
{
    kth_smallest_number p(4);
    int num;
    while (cin >> num)
    {
        cout << p.next(num) << endl;
    }
    return 0;
}
