#include <iostream>
#include<vector>
#include<queue>
#include<assert.h>

using namespace std;

class priorityqueue
{
private:
    int* key{ };
    int* value{ };
    int size{ };
    int capacity{1000};
    int left(int node)
    {
        int p=2*node+1;
        return p>=size ? -1 : p;
    }
    int right(int node)
    {
        int p=2*node+2;
        return (p>=size)? -1 : p;
    }
    int parent(int node)
    {
        return node==0 ? -1 : (node-1)/2;
    }
    void heapify_up(int child_pos)
    {
        int parent_pos=parent(child_pos);
        if(child_pos==0||key[parent_pos] > key[child_pos])
            return;
        swap(key[child_pos],key[parent_pos]);
        swap(value[child_pos],value[parent_pos]);
        heapify_up(parent_pos);
    }
    void heapify_dowen(int parent_pos=0)
    {
        int child_pos=left(parent_pos);
        int right_child=right(parent_pos);
        if(child_pos==-1)
            return;
        if(right_child!=-1 && key[right_child] > key[child_pos])
        {
            child_pos=right_child;
        }
        if(key[child_pos] > key[parent_pos])
        {
            swap(key[child_pos],key[parent_pos]);
            swap(value[child_pos],value[parent_pos]);
            heapify_dowen(child_pos);
        }
    }
public:
    priorityqueue()
    {
        key=new int[capacity]{ };
        value=new int[capacity]{ };
        size=0;
    }
    void enqueue(int val , int priority)
    {
        assert(size+1 <= capacity);
        value[size]=val;
        key[size++]=priority;
        heapify_up(size-1);
    }
    int dequeue()
    {

        assert(!isempty());
        int ret=value[0];
        key[0]=key[--size];
        value[0]=value[size];
        heapify_dowen(0);
        return ret;
    }
    bool isempty()
    {
        return size==0;
    }
    int top()
    {
        return value[0];
    }

};
int main()
{
    priorityqueue tasks;
	tasks.enqueue(1131, 1);
	tasks.enqueue(3111, 3);
	tasks.enqueue(2211, 2);
	tasks.enqueue(3161, 3);
	tasks.enqueue(7761, 7);
	while(!tasks.isempty())
    {
        cout<<tasks.dequeue()<<" ";
    }
    return 0;
}
