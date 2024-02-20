#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int data{};
    Node *prev{};
    Node *next{};
    Node(int data) : data(data) {}
};
class double_link
{
private:
    Node *head{};
    Node *tail{};
    int size{};
    void link(Node *first, Node *second)
    {
        if (first)
        {
            first->next = second;
        }
        if (second)
        {
            second->prev = first;
        }
    }
    Node *delete_and_link(Node *cur)
    {
        Node *ret = cur->prev;
        link(cur->prev, cur->next);
        free(cur);
        return ret;
    }

public:
    void insert_end(int val)
    {
        Node *item = new Node(val);
        if (!head)
            head = tail = item;
        else
        {
            link(tail, item);
            tail = item;
        }
        size++;
    }
    void insert_front(int val)
    {
        Node *item = new Node(val);
        if (!head)
            head = tail = item;
        else
        {
            link(item, head);
            head = item;
        }
        size++;
    }
    void insert_sorted(int val)
    {
        if (!size || head->data >= val)
            insert_front(val);
        else if (tail->data <= val)
            insert_end(val);
        else
        {
            Node *item = new Node(val);
            for (Node *cur = head; cur; cur = cur->next)
            {
                if (cur->data >= val)
                {
                    Node *p = cur->prev;
                    p->next = item;
                    item->prev = p;
                    item->next = cur;
                    cur->prev = item;
                    break;
                }
            }
            size++;
        }
    }
    void delete_front()
    {
        if (!head)
            return;
        Node *temp = head->next;
        free(head);
        head = temp;
        size--;
        if (head)
            head->prev = nullptr;
        if (!size)
            tail = nullptr;
    }
    void delete_back()
    {
        if (!head)
            return;
        Node *temp = tail->prev;
        free(tail);
        tail = temp;
        size--;
        if (tail)
            tail->next = nullptr;
        if (!size)
            head = nullptr;
    }
    void delete_with_key(int key)
    {
        if (head->data == key)
            delete_front();
        else
        {
            for (Node *cur = head; cur; cur = cur->next)
            {
                if (cur->data == key)
                {
                    bool is_tail = cur == tail;
                    cur = delete_and_link(cur);
                    if (is_tail)
                    {
                        tail = cur;
                        tail->next = nullptr;
                    }
                    size--;
                    break;
                }
            }
        }
    }
    void delete_all_Node_with_key(int key)
    {
        insert_front(-key);
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->data == key)
            {
                bool is_tail = cur == tail;
                cur = delete_and_link(cur);
                if (is_tail)
                {
                    tail = cur;
                    tail->next = nullptr;
                }
                size--;
            }
        }
        delete_front();
    }
    void delete_even_pos()
    {
        int count = 0;
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (++count % 2 == 0)
            {
                bool is_tail = cur == tail;
                cur = delete_and_link(cur);
                if (is_tail)
                {
                    tail = cur;
                    tail->next = nullptr;
                }
                size--;
            }
        }
    }
    void delete_odd_pos()
    {
        insert_front(-1);
        delete_even_pos();
        delete_front();
    }
    bool is_palindrome()
    {
        Node *front = head, *back = tail;
        while (front != back)
        {
            if (front->data != back->data)
                return false;
            front = front->next;
            back = back->prev;
        }
        return true;
    }
    void find_middle()
    {
        int idx = size / 2 + size % 2;
        int count = 0;
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (++count == idx)
            {
                cout << cur->data << endl;
                break;
            }
        }
    }
    void reverse()
    {
        Node *p = head;
        Node *cur = head->next;
        p->next = nullptr;
        p->prev = cur;
        while (cur->next)
        {
            Node *temp = cur;
            cur = cur->next;
            temp->next = p;
            p->prev = temp;
            p = temp;
        }
        cur->next = p;
        p->prev = cur;
        swap(head, tail);
    }
    void merge_2sorted_lists(double_link &other)
    { // O(n+m)
        if (!other.head)
            return;

        if (head)
        {
            Node *cur1 = head;
            Node *cur2 = other.head;
            Node *last{};
            head = nullptr;

            while (cur1 && cur2)
            {
                Node *next{};
                if (cur1->data <= cur2->data)
                {
                    next = cur1;
                    cur1 = cur1->next;
                }
                else
                {
                    next = cur2;
                    cur2 = cur2->next;
                }
                link(last, next);
                last = next;
                if (!head)
                    head = last;
            }
            if (cur2)
            {
                tail = other.tail;
                link(last, cur2);
            }
            else if (cur1)
            {
                link(last, cur1);
            }
        }
        else
        {
            head = other.head;
            tail = other.tail;
        }
    }
    void traverse()
    {
        if (!size)
            return;
        for (Node *cur = head; cur; cur = cur->next)
        {
            cout << cur->data << " ";
        }
        cout << endl;
    }
};
int main()
{
    double_link d;
    d.insert_end(1), d.insert_end(2), d.insert_end(3);
    d.reverse();
    d.traverse();
    return 0;
}