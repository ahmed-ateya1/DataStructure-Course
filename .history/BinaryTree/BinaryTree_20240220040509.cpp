#include <iostream>
#include<
#include<vector>
#include<queue>
#include<deque>
#include<assert.h>
using namespace std;
class BinaryTree
{
private:
	BinaryTree* left{ };
	BinaryTree* right{ };
	int data{ };
public:
	BinaryTree(int data) :data(data) { }
	void add(vector<int>value, vector<char>direction)
	{
		assert(value.size() == direction.size());
		BinaryTree* current = this;
		for (int i = 0; i < direction.size(); i++)
		{
			if (direction[i] == 'L')
			{
				if (!current->left)
				{
					current->left = new BinaryTree(value[i]);
				}
				else
				{
					assert(current->left->data == value[i]);
				}
				current = current->left;
			}
			else
			{
				if (!current->right)
				{
					current->right = new BinaryTree(value[i]);
				}
				else
				{
					assert(current->right->data == value[i]);
				}
				current = current->right;
			}
		}
	}
	void inorder()
	{
		if (left)
			left->inorder();
		cout << data << " ";
		if (right)
			right->inorder();
	}
	int tree_max()
	{
		int res = data;
		if (left)
			res = max(res, left->tree_max());
		if (right)
			res = max(res, right->tree_max());
		return res;
	}
	int tree_height()
	{
		int res = 0, res2 = 0;
		if (left)
			res += 1 + left->tree_height();
		if (right)
			res2 += 1 + right->tree_height();
		return max(res, res2);
	}
	int count_all_nodes()
	{
		int res = 1;
		if (left)
			res += left->count_all_nodes();
		if (right)
			res += right->count_all_nodes();
		return res;
	}
	bool search_tree(int goal)
	{
		bool res = goal == data;
		if (left && !res)
			res = left->search_tree(goal);
		if (right && !res)
			res = right->search_tree(goal);
		return res;
	}
	bool is_prefect()
	{
		return count_all_nodes() == pow(2, tree_height() + 1) - 1;
	}
	int summution_node()
	{
		int sum = data;
		if (left)
			sum += left->summution_node();
		if (right)
			sum += right->summution_node();
		return sum;
	}
	int count_leaf()
	{
		if (!right || !left)
			return 1;
		int res = 0;
		if (left)
			res += left->count_leaf();
		if (right)
			res += right->count_leaf();
		return res;
	}
	void traverse_left()
	{
		cout << data << " ";
		if (left)
			left->traverse_left();
		else if (right)
			right->traverse_left();
	}
	void traversa_order()
	{
		queue<BinaryTree*>q;
		q.push(this);
		int level = 0;
		while (!q.empty())
		{
			int sz = q.size();
			cout << "Level " << level << " : ";
			while (sz--)
			{
				BinaryTree* cur = q.front();
				q.pop();
				cout << cur->data << " ";
				if (cur->left)
					q.push(cur->left);
				if (cur->right)
					q.push(cur->right);
			}
			level++;
			cout << endl;
		}

	}
	void print_order(int level)
	{
		if (level == 0)
			cout << data << " ";
		else if (level)
		{
			left->print_order(level - 1);
			right->print_order(level - 1);
		}
	}
	void traverse_order_rec()
	{
		int h = tree_height();
		for (int level = 0; level < h; level++)
			print_order(level);
	}
	void traverse_spiral()
	{
		deque<BinaryTree*>q;
		q.push_back(this);
		bool forward = true;
		int level = 0;
		while (!q.empty())
		{
			int sz = q.size();
			cout << "Level " << level << " : ";
			while (sz--)
			{
				BinaryTree* cur;
				if (forward)
				{
					cur = q.front();
					q.pop_front();
					if (cur->left)
						q.push_back(cur->left);
					if (cur->right)
						q.push_back(cur->right);
				}
				else
				{
					cur = q.back();
					q.pop_back();
					if (cur->right)
						q.push_front(cur->right);
					if (cur->left)
						q.push_front(cur->left);
				}
				cout << cur->data << " ";
			}
			level++;
			forward = !forward;
			cout << endl;
		}
	}
	~BinaryTree()
	{
		clear();
	}
	void clear()
	{
		if (left)
		{
			delete left;
			left = nullptr;
		}
		if (right)
		{
			delete right;
			left = nullptr;
		}
	}
};
int main()
{
	//BinaryTree tree(2);
	//tree.add({3,5}, {'L','L'});
	//tree.add({ 3,6 }, { 'L','R' });
	//tree.add({ 13,8 }, { 'R','R' });
	//tree.add({ 13,7 }, { 'R','L' });
	//tree.add({ 13,8,9 }, { 'R','R','R' });
	//tree.add({ 13,8,20 }, { 'R','R','L' });
	////tree.add({ 13,7,20 }, { 'R','R','R' });
	///*cout<<tree.tree_max() << endl;
	//cout << tree.tree_height() << endl;
	//cout << tree.count_all_nodes() << endl;
	//cout << tree.search_tree(99) << endl;
	//cout << tree.is_prefect() << endl;
	//cout << tree.summution_node() << endl;*/
	//tree.traversa_order();
	//cout << endl;
	//tree.traverse_spiral();
	return 0;
}