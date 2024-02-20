#include<bits/stdc++.h>
using namespace std;

class Binary_search
{
private:
	int data{ };
	Binary_search* left{ };
	Binary_search* right{ };
	
	void search_inorder(vector<int>&v)
	{
		if (left)
			left->search_inorder(v);
		v.push_back(data);
		if (right)
			right->search_inorder(v);
	}
	Binary_search* min_node()
	{
		Binary_search* cur = this;
		while (cur && cur->left)
		{
			cur = cur->left;
		}
		return cur;
	}
	void special_delete(Binary_search* child)
	{
		data = child->data;
		left = child->left;
		right = child->right;
		delete child;
	}
 public:
	Binary_search(int data) :data(data) { }
	void insert(int target)
	{
		if (target < data)
		{
			if (!left)
				left = new Binary_search(target);
			else
			{
				left->insert(target);
			}
		}
		else if(target > data)
		{
			if (!right)
				right = new Binary_search(target);
			else
			{
				right->insert(target);
			}
		}
	}
	bool search(int key)//o(logn)
	{
		if (key == data)
			return true;
		if (key < data)
			return left && left->search(key);
		return right && right->search(key);
	}
	bool search_iterative(int key)//o(n)
	{
		vector<int>v;
		search_inorder(v);
		for (int i = 0; i < (int)v.size(); i++)
		{
			if (v[i] == key)
				return true;
		}
		return false;
	}
	bool IS_BST()
	{
		vector<int>v;
		search_inorder(v);
		for (int i = 1; i < (int)v.size(); i++)
		{
			if (v[i-1] > v[i])
				return false;
		}
		return true;
	}
	bool is_bst2(int mn = INT_MIN, int mx = INT_MAX)
	{
		bool status = data > mn && data < mx;
		if (!status)
			return false;
		bool left_bst = !left || left->is_bst2(mn, data);
		if (!left_bst)
			return false;
		bool right_bst = !right || right->is_bst2(data, mx);
		return right_bst;
	}
	int kth_smallest(int k)
	{
		vector<int>v;
		search_inorder(v);
		int count = 0;
		for (int i = 0; i < (int)v.size(); i++)
		{
			if (++count == k)
				return v[i];
		}
		return -1234;
	}
	int kth_smallest_v2(int& k) {
		if (k == 0)
			return -1234;

		if (left) {
			int res = left->kth_smallest_v2(k);
			if (k == 0)
				return res;
		}

		--k;
		if (k == 0)
			return data;

		if (right)
			return right->kth_smallest_v2(k);

		return -1234;
	}
	int LCA(int x, int y)
	{
		if (x < data && y < data)
			return left->LCA(x, y);
		else if (x > data && y > data)
			return right->LCA(x, y);
		return data;
	}
	int min_value()
	{
		if(!left)
			return data;
		return left->min_value();
	}
	int min_value_v2()
	{
		Binary_search* cur = this;
		while (cur && cur->left)
		{
			cur = cur->left;
		}
		return cur->data;
	}
	bool find_chain(int target, vector<Binary_search*>&ancestor)
	{
		ancestor.push_back(this);
		if (data == target)
			return true;
		if (target < data)
			return left && left->find_chain(target, ancestor);
		return right&& right->find_chain(target, ancestor);
	}
	Binary_search* getnext(vector<Binary_search*>&ancestor)
	{
		if (ancestor.size() == 0)
			return nullptr;
		Binary_search* node = ancestor.back();
		ancestor.pop_back();
		return node;
	}
	pair<bool, int>successor(int target)
	{
		vector<Binary_search*>ancestor;
		if (!find_chain(target, ancestor))
		{
			return make_pair(false, -1);
		}
		Binary_search* child = getnext(ancestor);
		if (child->right)
			return make_pair(true, child->right->min_value_v2());
		Binary_search* parent = getnext(ancestor);
		while (parent && parent->right==child)
		{
			child = parent, parent = getnext(ancestor);
		}
		if (parent)
			return make_pair(true, parent->data);
		return make_pair(false, -1);
	}
	bool is_degenerate(vector<int>& preorder) { 
		if (preorder.size() <= 2)
			return true;

		int mn = 1, mx = 1000;

		for (int i = 1; i < (int)preorder.size(); ++i) {
			if (preorder[i] < mn || preorder[i] > mx)
				return false;

			if (preorder[i] > preorder[i - 1])	
				mn = preorder[i - 1] + 1;	
			else
				mx = preorder[i - 1] - 1;
		}
		return true;
	}
	Binary_search* delete_node(int target, Binary_search* node)
	{
		if (!node)
			return nullptr;
		if (target < node->data)
			node->left = delete_node(target, node->left);
		else if (target > node->data)
			node->right = delete_node(target, node->right);
		else
		{
			Binary_search* temp = node;
			if (!node->right && !node->left)
				node = nullptr;
			else if (!node->right)
				node = node->left;
			else if (!node->left)
				node = node->right;
			else
			{
				Binary_search* mn = node->right->min_node();
				node->data = mn->data;
				node->right = delete_node(node->data, node->right);
				temp = nullptr;
			}
			if (temp)
				delete temp;
		}
		return node;
	}
	void delete_value(int target)
	{
		if (target == data && !left && !right)
			return;
		delete_node(target, this);
	}
	void print_inorder()
	{
		if (left)
			left->print_inorder();
		cout << data << " ";
		if (right)
			right->print_inorder();
	}
};
int main()
{
	Binary_search tree(5);
	tree.insert(6), tree.insert(4), tree.insert(8), tree.insert(12), tree.insert(7),tree.insert(2);
	tree.delete_value(5);
	tree.print_inorder();
	/*Binary_search tree(15);
	tree.insert(6), tree.insert(8), tree.insert(1), tree.insert(20), tree.insert(10), tree.insert(9), tree.insert(14);
	pair<bool, int>p = tree.successor(10);
	if (p.first)
		cout << p.second << endl;
	else
	{
		cout << "NA" << endl;
	}
	tree.print_inorder();*/
	return 0;
}