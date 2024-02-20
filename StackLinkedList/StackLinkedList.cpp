#include <bits/stdc++.h>

using namespace std;
struct Node
{
    int data;
    Node *Next = nullptr;
    Node(int data) : data(data) {}
};
class Stack_link
{
private:
    Node *head = nullptr;

public:
    void push(int val)
    {
        Node *item = new Node(val);
        item->Next = head;
        head = item;
    }
    int pop()
    {
        assert(!is_Empty());
        int val = head->data;
        Node *temp = head;
        head = head->Next;
        free(temp);
        return val;
    }
    int peek()
    {
        assert(!is_Empty());
        int elm = head->data;
        return elm;
    }
    int is_Empty()
    {
        return head == nullptr;
    }
    void print()
    {
        for (Node *cur = head; cur; cur = cur->Next)
        {
            cout << cur->data << " ";
        }
        cout << endl;
    }
};
int main()
{
    Stack_link s;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int val;
        cin >> val;
        s.push(val);
    }
    s.print();
    s.pop();
    s.pop();
    cout << s.peek();

    return 0;
}
