#include <iostream>
#include <algorithm>
using namespace std;
#define sp cout << endl;
struct Node
{
    int data{};
    Node *next{};
    Node(int data) : data(data) {}
};
class linked_list
{
private:
    Node *head{};
    Node *tail{};
    int sz{};
    Node *gth(int idx)
    {
        int cnt = 0;
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (++cnt == idx)
            {
                return cur;
            }
        }
        return nullptr;
    }
    void delete_duplicate(Node *node)
    {
        Node *is_deleted = node->next;
        bool is_tail = is_deleted == tail;
        node->next = is_deleted->next;
        if (is_tail)
        {
            tail = node;
        }
        free(is_deleted);
    }

public:
    void insert_end(int data)
    {
        Node *item = new Node(data);
        if (!head)
            head = tail = item;
        else
        {
            tail->next = item;
            tail = item;
        }
        sz++;
    }
    void insert_front(int data)
    {
        Node *item = new Node(data);
        if (!head)
            head = tail = item;
        else
        {
            item->next = head;
            head = item;
        }
        sz++;
    }
    void delete_front()
    {
        if (head)
        {
            Node *temp = head;
            head = head->next;
            free(temp);
            if (!head)
                tail = nullptr;
        }
        sz--;
    }
    void delete_back()
    {
        if (sz == 1)
        {
            delete_front();
        }
        else
        {
            Node *temp = gth(sz - 1);
            free(tail);
            tail = temp;
            tail->next = nullptr;
        }
        sz--;
    }
    void delete_end()
    {
        if (sz == 1)
        {
            delete_front();
        }
        else
        {
            Node *temp{};
            for (Node *cur = head; cur; cur = cur->next)
            {
                if (cur->next == nullptr)
                {
                    free(tail);
                    tail = temp;
                    if (tail)
                    {
                        tail->next = nullptr;
                    }
                    break;
                }
                temp = cur;
            }
        }
    }
    void get_nth_back(int index) // BY ME
    {
        if (index > sz)
            return;
        index--;
        int new_indx = sz - index;
        int count = 0;
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (++count == new_indx)
            {
                cout << cur->data << endl;
                break;
            }
        }
    }
    void delete_nth(int idx)
    {
        if (idx > sz)
            return;
        else if (idx == sz)
            delete_end();
        else if (idx == 1)
            delete_front();
        else
        {
            Node *prev = gth(idx - 1);
            Node *cur = prev->next;
            Node *Next = cur->next;
            prev->next = Next;
            free(cur);
        }
        sz--;
    }
    void get_nth_back_V2(int idx)
    {
        if (idx > sz)
            return;
        else
        {
            Node *temp = gth(sz - idx + 1);
            cout << temp->data << endl;
        }
    }
    void delete_with_key(int key)
    {
        if (key == head->data)
            delete_front();
        else
        {
            Node *prev{};
            for (Node *cur = head; cur; cur = cur->next)
            {
                if (key == cur->data)
                {
                    Node *temp = cur;
                    bool istail = cur == tail;
                    prev->next = cur->next;
                    if (istail)
                        tail = prev;
                    free(temp);
                    break;
                }
                prev = cur;
            }
        }
        sz--;
    }
    void delete_even_pos()
    {
        int cnt = 0;
        Node *prev{};
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (++cnt % 2 == 0)
            {
                Node *temp = cur;
                bool is_tail = cur == tail;
                prev->next = cur->next;
                free(temp);
                if (is_tail)
                {
                    tail = prev;
                    tail->next = nullptr;
                }
                cur = prev;
            }
            prev = cur;
        }
    }
    void swap_pair()
    {
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->next)
            {
                swap(cur->data, cur->next->data);
                cur = cur->next;
            }
        }
    }
    void reverse()
    {
        Node *prev = head;
        Node *cur = head->next;
        prev->next = nullptr;
        while (cur->next)
        {
            Node *temp = cur;
            cur = cur->next;
            temp->next = prev;
            prev = temp;
        }
        cur->next = prev;
        swap(head, tail);
    }
    void inserted_sort(int val)
    {
        if (!sz || head->data >= val)
        {
            insert_front(val);
        }
        else if (tail->data <= val)
        {
            insert_end(val);
        }
        else
        {
            sz++;
            Node *item = new Node(val);
            Node *prev{};
            for (Node *cur = head; cur; cur = cur->next)
            {
                if (cur->data >= val)
                {
                    prev->next = item;
                    item->next = cur;
                    break;
                }
                prev = cur;
            }
        }
    }
    void left_rotate(int k)
    {
        if (!k)
            return;
        left_rotate(k - 1);
        Node *temp = head;
        head = head->next;
        tail->next = temp;
        temp->next = nullptr;
        tail = temp;
    }
    void remove_duplicate()
    {
        for (Node *cur = head; cur; cur = cur->next)
        {
            Node *prev{};
            for (Node *cur2 = cur->next, *prev = cur; cur2;)
            {
                if (cur->data == cur2->data)
                {
                    delete_duplicate(prev);
                    cur2 = prev->next;
                }
                else
                {
                    prev = cur2;
                    cur2 = cur2->next;
                }
            }
        }
    }
    void traverse()
    {
        if (sz == 0)
            return;
        for (Node *cur = head; cur; cur = cur->next)
        {
            cout << cur->data << " ";
        }
        cout << endl;
    }
    void remove_last_occourance(int key)
    {
        Node *prev{}, *prev2{}, *last{};
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->data == key)
            {
                prev2 = prev;
                last = cur;
            }
            prev = cur;
        }
        if (last == tail)
            delete_back();
        else if (last == head)
            delete_front();
        else
        {
            prev2->next = last->next;
            free(last);
        }
    }
    ~linked_list()
    {
        while (head)
        {
            Node *temp = head->next;
            delete head;
            head = temp;
        }
        cout << "Done" << endl;
    }
};
int main()
{
    linked_list l;
    l.insert_end(1), l.insert_end(1), l.insert_end(3), l.insert_end(1), l.insert_end(4); // , l.insert_end(4);
    l.remove_last_occourance(1);
    l.traverse();
    return 0;
};