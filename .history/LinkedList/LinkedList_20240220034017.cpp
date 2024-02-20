#include <iostream>

using namespace std;
#define endl '\n'
//static array created in stack but dynamic created in heap
struct Node
{
    int data{ };
    Node* next{ };
    Node(int data) :data(data) { }
};
class Linked_list
{
private:
    Node* head{ };
    Node* tail{ };
    int size{ };
    Node* get_nth(int idx)
    {
        int count = 0;
        for (Node* cur = head; cur; cur = cur->next)
        {
            if (++count == idx)
                return cur;
        }
        return nullptr;

    }
    void delete_duplicate(Node* node)
    {
        Node* is_deleted = node->next;
        bool is_tail = is_deleted == tail;
        node->next = is_deleted->next;
        if (is_tail)
        {
            tail = node;
        }
        free(is_deleted);
    }
public:
    void insert_end(int val)
    {
        Node* item = new Node(val);
        if (!head)
            head = tail = item;
        else
        {
            tail->next = item;
            tail = item;
        }
        size++;
    }
    void insert_front(int val)
    {
        Node* item = new Node(val);
        if (!head)
            head = tail = item;
        else
        {
            item->next = head;
            head = item;
        }
        size++;
    }

    void delete_front()
    {
        if (head)
        {
            Node* cur = head;
            head = head->next;
            free(cur);
            if (!head)
                tail = nullptr;
        }
        size--;
    }
    void delete_back()
    {
        if (size <= 1)
        {
            delete_front();
        }
        else
        {
            Node* prev = get_nth(size - 1);
            free(tail);
            tail = prev;
            tail->next = nullptr;
            size--;
        }
    }
    void delete_nth(int idx)
    {
        if (idx == 1)
            delete_front();
        else
        {
            int count{ };
            Node* prev{ };
            for (Node* cur = head; cur; cur = cur->next)
            {
                if (idx == ++count)
                {
                    Node* temp = cur->next;
                    prev->next = cur->next;
                    cur = temp;
                    if (!tail)
                        tail->next = nullptr;
                    size--;
                    break;
                }
                prev = cur;
            }
        }
    }
    void delete_with_key(int key)
    {
        if (key == head->data)
            delete_front();
        else
        {
            Node* prev{ };
            for (Node* cur = head; cur; cur = cur->next)
            {
                if (key == cur->data)
                {
                    Node* temp = cur->next;
                    prev->next = cur->next;
                    cur = temp;
                    if (!tail)
                        tail->next = nullptr;
                    size--;
                    break;
                }
                prev = cur;
            }
        }
    }
    void print()
    {
        for (Node* cur = head; cur; cur = cur->next)
        {
            cout << cur->data << " ";
        }
    }
    bool is_same(Linked_list l)
    {
        if (l.size != size)
            return false;
        Node* cur1 = l.head;
        for (Node* cur = head; cur; cur = cur->next, cur1 = cur1->next)
        {
            if (cur->data != cur1->data)
                return false;
        }
        return true;
    }
    void swap_each_pair()
    {
        for (Node* cur = head; cur; cur = cur->next)
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
        Node* prev = nullptr;
        Node* cur = head;
        Node* next = nullptr;
        tail = head;
        while (cur)
        {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        head = prev;

    }
    void insert_sorted(int value)
    {
        if (!size || head->data >= value)
            insert_front(value);
        else if (tail->data <= value)
            insert_end(value);
        else
        {
            size++;
            Node* item = new Node(value);
            Node* prev{ };
            for (Node* cur = head; cur; cur = cur->next)
            {
                if (cur->data >= value)
                {
                    prev->next = item;
                    item->next = cur;
                }
                prev = cur;
            }
        }
    }
    void left_rotate(int idx)
    {
        Node* cur{ };
        while (idx--)
        {
            cur = head;
            head = head->next;
            tail->next = cur;
            tail = cur;
            tail->next = nullptr;
        }
    }
    void remove_duplicate()
    {
        for (Node* cur = head; cur; cur = cur->next)
        {
            Node* prev{ };
            for (Node* cur2 = cur->next, *prev = cur; cur2; )
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
    void remove_last_occourance(int key)
    {
        Node* prev{ }, * prev2{ }, * to_delete{ };
        for (Node* cur = head; cur; cur = cur->next)
        {
            if (cur->data == key)
            {
                to_delete = cur;
                prev = prev2;
            }
            prev2 = cur;
        }
        if (to_delete == head)
            delete_front();
        else
        {
            delete_duplicate(prev);
        }
    }
    ~Linked_list()
    {
        while (head)
        {
            Node* temp = head->next;
            delete head;
            head = temp;
        }
    }
};
int main()
{
    Linked_list l;
    l.insert_end(1), l.insert_end(1), l.insert_end(2), l.insert_end(4), l.insert_end(1),l.insert_end(2),l.insert_end(3);
    l.remove_last_occourance(2);
    l.print();
    return 0;
}
