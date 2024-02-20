#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;

int string_hashing(string str, int n = 65407)
{
    long long n1 = n, sum = 0;
    for (int i = 0; i < (int)str.size(); i++)
    {
        sum += (sum * 26 + str[i] - 'a') % n1;
    }
    return sum % n1;
}
struct PhoneEntry
{
    string name;
    string phone_number;
    int internal_limit = 65407;
    PhoneEntry(string name, string phone_number) : name(name), phone_number(phone_number) {}
    int hash()
    {
        return string_hashing(name, internal_limit);
    }
    void print()
    {
        cout << "(" << name << ", " << phone_number << ")  ";
    }
};
class PhoneHashing
{
private:
    vector<PhoneEntry *> table;
    int table_size;
    PhoneEntry *deleted = new PhoneEntry("", "");

public:
    PhoneHashing(int table_size) : table_size(table_size)
    {
        table.resize(table_size);
    }
    bool put(PhoneEntry phone)
    {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < table_size; i++)
        {
            if (!table[idx] || table[idx] == deleted)
            {
                table[idx] = new PhoneEntry(phone);
                return true;
            }
            else if (table[idx]->name == phone.name)
            {
                table[idx]->phone_number = phone.phone_number; // update
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }
    bool remove(PhoneEntry phone)
    {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < table_size; i++)
        {
            if (!table[idx])
                break;
            else if (table[idx]->name == phone.name && table[idx] != deleted)
            {
                delete table[idx];
                table[idx] = deleted;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }
    bool get(PhoneEntry &phone)
    {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < table_size; i++)
        {
            if (!table[idx])
                break;
            else if (table[idx]->name == phone.name && table[idx] != deleted)
            {
                phone.phone_number = table[idx]->phone_number;
                return true;
            }
            idx = (idx + 1) % table_size;
        }
        return false;
    }
    void print_all()
    {
        for (int hash = 0; hash < table_size; hash++)
        {
            cout << hash << " ";
            if (!table[hash])
                cout << "E";
            else if (table[hash] == deleted)
                cout << "X";
            else
                table[hash]->print();
            cout << endl;
        }
    }
};

int count_unique_substring(const string &str)
{
    unordered_map<string, int> mp;
    for (int i = 0; i < (int)str.size(); i++)
    {
        string temp = "";
        for (int j = i; j < (int)str.size(); j++)
        {
            temp += str[j];
            if (mp[temp] == 0)
            {
                mp[temp]++;
            }
        }
    }
    return (int)mp.size();
}
int count_unique_substring2(const string &str, unordered_map<string, int> &mp)
{
    for (int i = 0; i < (int)str.size(); i++)
    {
        string temp = "";
        for (int j = i; j < (int)str.size(); j++)
        {
            temp += str[j];
            if (mp[temp] == 0)
            {
                mp[temp]++;
            }
        }
    }
    return mp.size();
}
int count_distincit_matching(string &str1, string &str2)
{
    unordered_map<string, int> mp, mp2;
    count_unique_substring2(str1, mp), count_unique_substring2(str2, mp2);
    int count = 0;
    for (auto v : mp) // first by me
    {
        for (auto it : mp2)
        {
            if (v.first == it.first)
            {
                count++;
            }
        }
    }
    /*int cnt = 0; //second mostafa
    for (string str : s1)
        cnt += s2.count(str);*/
    return count;
}
int count_angram_subdtring(const string &str)
{
    unordered_set<string> s;
    for (int i = 0; i < str.size(); i++)
    {
        for (int j = i; j < str.size(); j++)
        {
            string temp = str.substr(i, j - i + 1);
            sort(temp.begin(), temp.end());
            s.insert(temp);
        }
    }
    return str.size();
}
int main()
{
    cout << count_angram_subdtring("abba");
    return 0;
}