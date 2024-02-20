#include <bits/stdc++.h>
using namespace std;

class trie
{
private:
    // map<int, trie*> child;
    static const int MAX_CHAR = 26;
    trie *child[MAX_CHAR];
    bool is_leaf{};

public:
    trie()
    {
        memset(child, 0, sizeof(child));
    }
    void insert(string str, int idx = 0)
    {
        if (idx == (int)str.size())
            is_leaf = 1;
        else
        {
            int cur = str[idx] - 'a';
            if (child[cur] == 0)
                child[cur] = new trie();
            child[cur]->insert(str, idx + 1);
        }
    }
    void insert_iterative(string str)
    {
        trie *cur = this;
        for (int i = 0; i < (int)str.size(); i++)
        {
            int ch = str[i] - 'a';
            if (!cur->child[ch])
                cur->child[ch] = new trie();
            cur = cur->child[ch];
        }
        cur->is_leaf = 1;
    }
    bool word_exist(string str, int idx = 0)
    {
        if (idx == (int)str.size())
            return is_leaf;
        int cur = str[idx] - 'a';
        if (!child[cur])
            return false;
        return child[cur]->word_exist(str, idx + 1);
    }
    bool prefix_exist(string str, int idx = 0)
    {
        if (idx == (int)str.size())
            return true;

        int cur = str[idx] - 'a';
        if (!child[cur])
            return false;

        return child[cur]->prefix_exist(str, idx + 1);
    }
    bool word_exist_iterative(string str)
    {
        trie *cur = this;
        for (int i = 0; i < (int)str.size(); i++)
        {
            int ch = str[i] - 'a';
            if (!cur->child[ch])
                return false;
            cur = cur->child[ch];
        }
        return cur->is_leaf;
    }
    string first_word(string &str) // by me
    {
        if (str.size() == 1)
            return "Not Exist";
        trie *cur = this;
        string s;
        for (int i = 0; i < (int)str.size(); i++)
        {
            int ch = str[i] - 'a';
            s += str[i];
            if (cur->is_leaf || !cur->child[ch])
            {
                s.pop_back();
                return s;
            }
            cur = cur->child[ch];
        }
    }
    string first_word_prefix(const string &str)
    { // mostafa saad
        trie *cur = this;

        for (int idx = 0; idx < (int)str.size(); ++idx)
        {
            int ch = str[idx] - 'a';
            if (!cur->child[ch])
                break;

            if (cur->child[ch]->is_leaf)
                return str.substr(0, idx + 1);
            cur = cur->child[ch];
        }
        return str;
    }
    void insert_vec(vector<string> &path, int idx = 0)
    {
        if (idx == (int)path.size())
            return;
        trie *cur = this;
        for (int i = 0; i < (int)path[idx].size(); i++)
        {
            int ch = path[idx][i] - 'a';
            if (!cur->child[ch])
                cur->child[ch] = new trie();
            cur = cur->child[ch];
        }
        cur->is_leaf = true;
        insert_vec(path, idx + 1);
    }
    bool is_exist_vec(vector<string> &path, int idx = 0)
    {
        if (idx == path.size())
            return true;
        trie *cur = this;
        for (int i = 0; i < (int)path[idx].size(); i++)
        {
            int ch = path[idx][i] - 'a';
            if (!cur->child[ch])
                return false;
            cur = cur->child[ch];
        }
        return is_exist_vec(path, idx + 1);
    }
    void get_all_string(vector<string> &res, string str = " ")
    {
        if (is_leaf)
            res.push_back(str);

        for (int i = 0; i < MAX_CHAR; ++i)
            if (child[i])
                child[i]->get_all_string(res, str + (char)(i + 'a'));
    }
};
int main()
{
    trie tree;
    tree.insert("abcd");
    tree.insert("xyz");
    tree.insert("a");
    tree.insert("ab");
    tree.insert("xyzw");
    tree.insert("bcd");

    vector<string> res;
    tree.get_all_string(res);
    for (int i = 0; i < (int)res.size(); ++i)
        cout << res[i] << "\n";
    return 0;
}