#include <bits/stdc++.h>

using namespace std;
class Deque
{
private:
    int *arr{ };
    int size{ };
    int rear{0};
    int front{0};
    int add_element{ };
    int next(int pos)
    {
        return (pos+1)%size;
    }
    int prev(int pos)
    {
        --pos;
        if(pos==-1)
        {
            pos==size-1;
        }
        return pos;
    }
public:
    Deque(int size):size(size)
    {
        if(size<0)
            size=1;
        arr=new int [size];
    }
    bool is_full()
    {
        return size==add_element;
    }
    bool is_Empty()
    {
        return add_element==0;
    }
    void enqueue_rear(int value)
    {
        assert(!is_full());
        arr[rear]=value;
        rear=next(rear);
        add_element++;
    }
    void enqueue_front(int value)
    {
         assert(!is_full());
         front=prev(front);
         arr[front]=value;
         add_element++;
    }
    int dequeue_front()
    {
        assert(!is_Empty());
        int value=arr[front];
        front=next(front);
        add_element--;
        return value;
    }
    int dequeue_back()
    {
        assert(!is_Empty());
        int value=arr[rear];
        rear=prev(rear);
        add_element--;
        return value;
    }
    void display()
    {
        for(int cur=front,step=0 ; step<add_element;++step,cur=next(cur))
        {
            cout<<arr[cur]<<" ";
        }
        cout<<endl;
    }
    ~Deque()
    {
        delete[]arr;
    }
};
void MOUST()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}
int main()
{
    MOUST();
    Deque s(3);
    s.enqueue_rear(1);
    s.enqueue_rear(2);
    s.enqueue_front(0);
    s.dequeue_front();
    s.enqueue_front(3);
    s.dequeue_back();
    s.display();
    return 0;
}
