#include<bits/stdc++.h>
using namespace std;

int hashing_string(string str, int n_ = 65407)
{
	int base = 2 * 26 + 10;	// lower, upper and 10 digits
	long long n = n_;
	long long sum = 0;

	for (int i = 0; i < (int)str.size(); ++i) {
		int value = 0;
		if (islower(str[i]))
			value = str[i] - 'a';
		else if (isupper(str[i]))
			value = 26 + str[i] - 'A';
		else if (isdigit(str[i]))
			value = 26 + 26 + str[i] - '0';
		else
			assert(false);
		sum = sum * base + value;
		sum %= n;	
	}
	return sum % n;
}
struct phoneEntery
{
	string name;
	string phone_number;
	const static int initial_item= 2147483647;
	phoneEntery(string name , string phone_number):name(name),phone_number(phone_number){ }
	int hash()
	{
		return hashing_string(name,initial_item);
	}
	void print() {
		cout << "(" << name << ", " << phone_number << ")  ";
	}

};
class phoneHash
{
private:
	struct linkedhash
	{
		phoneEntery item;
		linkedhash* next{ };

		linkedhash(phoneEntery item) : item(item) {
		}
	};
	int table_size;
	vector<linkedhash*>table{ };

public:
	phoneHash(int table_size) :table_size(table_size)
	{
		table.resize(table_size);
	}
	void put(phoneEntery phone)
	{
		int hash = phone.hash() % table_size;

		if (!table[hash])
			table[hash] = new linkedhash(phone);
		else {
			linkedhash* head = table[hash];
			while (head->next) {
				if (head->item.name == phone.name) {
					head->item = phone;	
					return;
				}
				head = head->next;
			}
			if (head->item.name == phone.name)
				head->item = phone;	
			else
				head->next = new linkedhash(phone);
		}
	}
	void print_all() {
		for (int hash = 0; hash < table_size; ++hash) {
			if (!table[hash])
				continue;

			cout << "Hash " << hash << ": ";
			for (linkedhash* head = table[hash]; head; head = head->next)
				head->item.print();
			cout << "\n";
		}
	}
};
int main()
{
	phoneHash table(3);
	table.put(phoneEntery("mostafa", "604-401-120"));
	table.put(phoneEntery("mostafa", "604-401-777"));
	table.put(phoneEntery("ali", "604-401-343"));
	table.put(phoneEntery("ziad", "604-401-17"));
	table.put(phoneEntery("hany", "604-401-758"));
	table.put(phoneEntery("belal", "604-401-550"));
	table.put(phoneEntery("john", "604-401-223"));

	table.print_all();
	return 0;
}