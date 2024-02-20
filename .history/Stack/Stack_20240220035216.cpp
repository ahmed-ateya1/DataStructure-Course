#include <bits/stdc++.h>

using namespace std;
class Stack
{
private:
    int size{ };
    int top{ };
    int *arr{ };
public:
    Stack(int size):size(size),top(-1)
    {
        if(size<1)
            size=0;
        arr=new int [size];
    }
    void push(int val)
    {
        assert(!is_full());
        arr[++top]=val;
    }
    int pop()
    {
        assert(!is_Empty());
        return arr[top--];
    }
    int peek()
    {
        assert(!is_Empty());
        return arr[top];
    }
    int is_full()
    {
        return top==size-1;
    }
    int is_Empty()
    {
        return top==-1;
    }
    void display()
    {
        for(int i=top; i>=0; i--)
            cout<<arr[i]<<" ";
    }
    void insert_at_bottom(int x)
    {
        if(is_Empty())
        {
            push(x);
        }
        else
        {
            int cur=pop();
            insert_at_bottom(x);
            push(cur);
        }

    }
    void reverse()
    {
        if(is_Empty())
        {
            return;
        }
        int cur=pop();
        reverse();
        insert_at_bottom(cur);
    }
    ~Stack()
    {
        delete[]arr;
    }

};
string rev_subword(string l)
{
    string result;
    l+=' ';
    stack<char>s;
    for(int i=0; i<(int)l.size(); i++)
    {
        if(l[i]==' ')
        {
            while(!s.empty())
            {
                result+=s.top();
                s.pop();
            }
            result+=' ';
        }
        else
        {
            s.push(l[i]);
        }
    }
    return result;
}
int rev_num(int num)
{
    int res=0;
    stack<int>s;
    while(num!=0)
    {
        s.push(num%10);
        num=num/10;
        res=res*10+s.top();
        s.pop();
    }
    return res;
}
bool valid_parentheses(string p)
{
    stack<char>s;
    for(int i=0; i<(int)p.size(); i++)
    {
        if(p[i]=='(' || p[i]=='['||p[i]=='{')
        {
            s.push(p[i]);
        }
        else
        {
            if((s.empty())|| (p[i]==')'&&s.top()!='(')||(p[i]==']'&&s.top()!='[')||(p[i]=='}'&&s.top()!='{'))
            {
                return false;
            }
            else
            {
                s.pop();
            }
        }
    }
    return s.empty();
}
string remove_duplicate(string str)
{
    stack<char>s;
    for(int i=0; i<(int)str.size(); i++)
    {
        if(s.empty())
            s.push(str[i]);
        else
        {
            if(str[i]!=s.top())
                s.push(str[i]);
            else
                s.pop();
        }
    }
    str="";
    while(!s.empty())
    {
        str=s.top()+str;
        s.pop();
    }
    return str;
}
void astoried(int arr[],int n)
{
    stack<int>s;
    for(int i=0; i<n; i++)
    {
        bool x=false;
        while(!s.empty() && arr[i]<0 && s.top()>0)
        {

            if(s.top() < -arr[i])
            {
                s.pop();
                continue;
            }
            else if(s.top() == -arr[i])
            {
                s.pop();
            }
            x=true;
            break;
        }
        if(!x)
            s.push(arr[i]);
    }
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
}
void MOUST()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}
int main()
{
    MOUST();
    Stack s(4);
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.reverse();
    s.display();
    return 0;
}
