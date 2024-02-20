#include<iostream>
#include<queue>
#include<assert.h>
using namespace std;
class Queue
{
private:
	int* arr{ };
	int front{ };
	int rear{ };
	int added_element{ };
	int size{ };
	int next(int pos)
	{
		++pos;
		if (pos == size)
			return 0;
		return pos;
	  //return (pos + 1) % size;	//  Or shorter way
	}
public:
	Queue(int size) :size(size)
	{
		if (size <= 0)
			size = 1;
		arr = new int[size];
	}
	void enqueue(int val)
	{
		assert(!is_full());
		arr[rear] = val;
		rear = next(rear);
		added_element++;
	}
	int dequeue()
	{
		assert(!is_empty());
		int val = arr[front];
		front = next(front);
		added_element--;
		return val;
	}
	bool is_full()
	{
		return added_element == size ;
	}
	bool is_empty()
	{
		return added_element == 0;
	}
	void print()
	{
		for (int cur = front, step = 0; step < added_element; ++step, cur = next(cur))
			cout << arr[cur] << " ";
	}
	~Queue()
	{
		delete[]arr;
	}
};
class stack
{
private:
	Queue q;
	int added_element{ };
	void insert_front(int data)
	{
		q.enqueue(data);
		int sz = added_element;
		while (sz--)
		{
			q.enqueue(q.dequeue());
		}
		added_element++;
	}
public:
	stack(int size) :q(size)
	{

	}
	void push(int data)
	{
		insert_front(data);
	}
	void pop()
	{
		q.dequeue();
		added_element--;
	}
	void print()
	{
		q.print();
	}
};
class sum_last_k_num
{
private:
	int k;
	Queue q;
	int added_element{ };
	int sum = 0;
public:
	sum_last_k_num(int k) :k(k),q(k+1)
	{
	}
	int next(int new_num)
	{
		q.enqueue(new_num);
		sum += new_num;
		added_element++;
		if (added_element > k)
		{
			sum -= q.dequeue();
			added_element--;
		}
		return sum;
	}
};
int main()
{
	sum_last_k_num processor(4);

	int num;
	while (cin >> num)
		cout << processor.next(num) << "\n";

	return 0;
}