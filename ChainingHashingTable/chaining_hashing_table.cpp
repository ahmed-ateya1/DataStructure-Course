#include <bits/stdc++.h>
using namespace std;

int hash_string(string str, int n = 65407)
{
    long long sum = 0, n1 = n;
    for (int i = 0; i < (int)str.size(); i++)
    {
        if (isupper(str[i]))
            sum = (sum * 26 + str[i] - 'A') % n1;
        else if (islower(str[i]))
            sum = (sum * 26 + str[i] - 'a') % n1;
        else
            sum = (sum * 9 + str[i] - '0') % n1;
    }
    return sum % n1;
}
int hash_num(int value, int n = 65407)
{
    long long n1 = n;
    return (value % n1 + n1) % n1;
}
int hash_string_folding(string str, int n = 65407)
{
    long long n1 = n, sum = 0;
    for (int i = 0; i < str.size(); i++)
    {
        string block = str.substr(i, 4);
        sum += hash_string(block);
        sum %= n1;
    }
    return sum;
}

struct somObject
{
    string str1, str2;
    int number;
    int internal_limit = 2147483647;

    int hash()
    {
        long long res = hash_string_folding(str1, internal_limit);
        res += hash_string_folding(str2, internal_limit);
        res += hash_num(number, internal_limit);
        return res % internal_limit;
    }
};
struct PhoneEntry
{
    const static int INTERNAL_LIMIT = 65407;
    string name;
    string phone_number;

    int hash()
    {
        return hash_string_folding(name, INTERNAL_LIMIT);
    }

    PhoneEntry(string name, string phone_number) : name(name), phone_number(phone_number)
    {
    }

    void print()
    {
        cout << "(" << name << ", " << phone_number << ")  ";
    }
};

class PhoneHashTable
{
private:
    int table_size;
    vector<vector<PhoneEntry>> table;

public:
    PhoneHashTable(int table_size) : table_size(table_size)
    {
        table.resize(table_size);
    }

    bool get(PhoneEntry &phone)
    {
        int idx = phone.hash() % table_size;

        for (int i = 0; i < (int)table[idx].size(); ++i)
        {
            if (table[idx][i].name == phone.name)
            {
                phone = table[idx][i];
                return true;
            }
        }
        return false;
    }

    void put(PhoneEntry phone)
    {
        int idx = phone.hash() % table_size;

        for (int i = 0; i < (int)table[idx].size(); ++i)
        {
            if (table[idx][i].name == phone.name)
            {
                table[idx][i] = phone;
                return;
            }
        }
        table[idx].push_back(phone);
    }

    bool remove(PhoneEntry phone)
    {
        int idx = phone.hash() % table_size;
        for (int i = 0; i < (int)table[idx].size(); ++i)
        {
            if (table[idx][i].name == phone.name)
            {
                swap(table[idx][i], table[idx].back());
                table[idx].pop_back();
                return true;
            }
        }
        return false;
    }

    void print_all()
    {
        for (int hash = 0; hash < table_size; ++hash)
        {
            if (table[hash].size() == 0)
                continue;

            cout << "Hash " << hash << ": ";
            for (int i = 0; i < (int)table[hash].size(); ++i)
                table[hash][i].print();
            cout << "\n";
        }
    }
};

int main()
{

    PhoneHashTable table(3);
    table.put(PhoneEntry("mostafa1111A", "604-401-120"));
    table.put(PhoneEntry("mostafa", "604-401-777"));
    table.put(PhoneEntry("ali", "604-401-343"));
    table.put(PhoneEntry("ziad", "604-401-17"));
    table.put(PhoneEntry("hany", "604-401-758"));
    table.put(PhoneEntry("belal", "604-401-550"));
    table.put(PhoneEntry("john", "604-401-223"));

    PhoneEntry e("mostafa", "");
    if (table.get(e))
        cout << e.phone_number << "\n";
    table.print_all();
    cout << table.remove(PhoneEntry("smith", "")) << "\n"; // 0
    cout << table.remove(PhoneEntry("hany", "")) << "\n";  // 1
    cout << table.remove(PhoneEntry("belal", "")) << "\n"; // 1
    table.print_all();
    return 0;
}
