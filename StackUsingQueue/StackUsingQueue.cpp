#include <bits/stdc++.h>

using namespace std;
class Queue
{
    int size{};
    int front{0};
    int rear{0};
    int added_elements{};
    int *array{};

public:
    Queue(int size) : size(size)
    {
        array = new int[size];
    }

    ~Queue()
    {
        delete[] array;
    }

    int next(int pos)
    {
        ++pos;
        if (pos == size)
            pos = 0;
        return pos;
    }

    void enqueue(int value)
    {
        assert(!isFull());
        array[rear] = value;
        rear = next(rear);
        added_elements++;
    }

    int dequeue()
    {
        assert(!isEmpty());
        int value = array[front];
        front = next(front);
        --added_elements;
        return value;
    }

    int front_val()
    {
        assert(!isEmpty());
        return array[front];
    }

    void display()
    {
        cout << "Front " << front << " - rear " << rear << "\t";
        if (isFull())
            cout << "full";
        else if (isEmpty())
        {
            cout << "empty\n\n";
            return;
        }
        cout << "\n";

        for (int cur = front, step = 0; step < added_elements; ++step, cur = next(cur))
            cout << array[cur] << " ";
        cout << "\n\n";
    }

    int isEmpty()
    {
        return added_elements == 0;
    }

    bool isFull()
    {
        return added_elements == size;
    }
};
class Stack
{
private:
    Queue q;
    int added_element{};
    void insert_front(int x)
    {
        int sz = added_element;
        q.enqueue(x);
        while (sz--)
        {
            q.enqueue(q.dequeue());
        }
        ++added_element;
    }

public:
    Stack(int size) : q(size) {}
    void push(int val)
    {
        insert_front(val);
    }
    int pop()
    {
        --added_element;
        return q.dequeue();
    }
    int peek()
    {
        return q.front_val();
    }
    void display()
    {
        q.display();
    }
};

int main()
{
    Stack s(3);
    s.push(1);
    s.push(2);
    s.push(3);
    s.pop();
    s.display();
    return 0;
}
