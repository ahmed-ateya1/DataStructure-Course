#include<bits/stdc++.h>
using namespace std;
class AVL_TREE
{
private:
	struct BinaryNode
	{
		int data{ };
		int height{ };
		BinaryNode* left{ };
		BinaryNode* right{ };
		BinaryNode(int data) :data(data) { }
		int ch_child(BinaryNode* node)
		{
			if (!node)
				return -1;
			return node->height;
		}
		int update_height()
		{
			return height= 1 + max(ch_child(left), ch_child(right));
		}
		int balanced_factor()
		{
			return ch_child(left) - ch_child(right);
		}
	};
	BinaryNode* root{ };
	BinaryNode*  right_rotation(BinaryNode* Q)
	{
		BinaryNode* P = Q->left;
		Q->left = P->right;
		P->right = Q;
		P->update_height();
		Q->update_height();
		return P;
	}
	BinaryNode* left_rotation(BinaryNode* P)
	{
		BinaryNode* Q = P->right;
		P->right = Q->left;
		Q->left = P;
		P->update_height();
		Q->update_height();
		return Q;
	}
	BinaryNode* belanced(BinaryNode* node)
	{
		if (node->balanced_factor() == 2)
		{
			if (node->left->balanced_factor() == -1)
				node->left = left_rotation(node->left);
			node = right_rotation(node);
		}
		else if (node->balanced_factor() == -2)
		{
			if (node->right->balanced_factor() == 1)
				node->right = right_rotation(node->right);
			node = left_rotation(node);
		}
		return node;
	}
	BinaryNode* insert(int target , BinaryNode* node)
	{
		if (target < node->data)
		{
			if (!node->left)
				node->left = new BinaryNode(target);
			else
			{
				node->left = insert(target, node->left);
			}
		}
		else if(target > node->data)
		{
			if (!node->right)
				node->right = new BinaryNode(target);
			else
			{
				node->right = insert(target, node->right);
			}
		}
		node->update_height();
		return belanced(node);
	}
	BinaryNode* min_node(BinaryNode* node)
	{
		while (node && node->left)
		{
			node = node->left;
		}
		return node;
	}
	BinaryNode* delete_node(int target,BinaryNode* node)
	{
		if (!node)
			return nullptr;
		if (target < node->data)
			node->left = delete_node(target, node->left);
		else if (target > node->data)
			node->right = delete_node(target, node->right);
		else
		{
			BinaryNode* temp = node;
			if (!node->left && !node->right)
				node = nullptr;
			else if (!node->left)
				node = node->right;
			else if (!node->right)
				node = node->left;
			else
			{
				BinaryNode* mn = min_node(node->right);
				node->data = mn->data;
				node->right = delete_node(node->data, node->right);
				temp = nullptr;
			}
			if (temp)
			{
				delete temp;
			}
		}
		if (node) {
			node->update_height();
			node = belanced(node);
		}
		return node;
	}
	BinaryNode* upper_bound(BinaryNode* node, int target)
	{
		if (!node)
			return nullptr;
		if (target < node->data)
		{
			BinaryNode* ans = upper_bound(node->left, target);
			if (ans)
				return ans;
			return node;
		}
		return upper_bound(node->right, target);
	}
	BinaryNode* lower_bound(BinaryNode* node, int target)
	{
		if (!node)
			return nullptr;
		else if (target <= node->data)
		{
			BinaryNode* ans = lower_bound(node->left, target);
			if (ans)
				return ans;
			return node;
		}
		return  lower_bound(node->right, target);
	}
	bool search(int target, BinaryNode* node)
	{
		if (!node)
			return false;
		if (node->data == target)
			return true;
		if (target < node->data)
			return search(target, node->left);
		return search(target, node->right);
	}
	void print_inorder(BinaryNode* node)
	{
		if (!node)
			return;
		print_inorder(node->left);
		cout << node->data << " ";
		print_inorder(node->right);
	}
public:
	void insert(int target)
	{
		if (!root)
			root = new BinaryNode(target);
		else
		{
			root = insert(target, root);
		}
	}
	void delete_node(int target)
	{
		if (root)
		{
			root = delete_node(target, root);
		}
	}
	bool search(int target)
	{
		return search(target, root);
	}
	
	pair<bool, int>upper_bound(int target)
	{
		if (root)
		{
			BinaryNode* res = upper_bound(root, target);
			if (!res)
				return make_pair(false, -1);
			return make_pair(true, res->data);
		}
		return make_pair(false, -1);
	}
	pair<bool, int>lower_bound(int target)
	{
		if (root)
		{
			BinaryNode* res = lower_bound(root, target);
			if (!res)
				return make_pair(false, -1);
			return make_pair(true, res->data);
		}
		return make_pair(false, -1);
	}
	void print_inorder()
	{
		print_inorder(root);
	}
	void level_order_treversal()
	{
		queue<BinaryNode*>child;
		child.push(root);
		int level = 0;
		while (!child.empty())
		{
			int sz = child.size();
			cout << "Level " << level << ": ";
			while (sz--)
			{
				BinaryNode* cur = child.front(); child.pop();
				cout << cur->data << " ";
				if (cur->left)
					child.push(cur->left);
				if (cur->right)
					child.push(cur->right);
			}
			level++;
			cout << endl;
		}
	}
};
void test_lower() {
	AVL_TREE tree;

	vector<int> v{ 10, 5, 20, 15, 50, 70, 2, 13, 40 };
	// 2, 5, 10, 13, 15, 20, 40, 50, 70

	for (int i = 0; i < v.size(); ++i)
		tree.insert(v[i]);

	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); ++i)
		cout << v[i] + 1 << " " << tree.lower_bound(v[i] + 1).second << "\n";
}

void test_upper() {
	AVL_TREE tree;

	vector<int> v{ 10, 5, 20, 15, 50, 70, 2, 13, 40 };

	for (int i = 0; i < v.size(); ++i)
		tree.insert(v[i]);

	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << " " << tree.upper_bound(v[i]).second << "\n";
}
int main()
{
	test_upper();
	//AVL_TREE v;
	//v.insert(3), v.insert(5), v.insert(9), v.insert(1), v.insert(0), v.insert(2), v.insert(6), v.insert(10), v.insert(7), v.insert(8);
	//v.delete_node(3);
	//v.level_order_treversal();
	////v.print_inorder();
	return 0;
}
/*
           3
		/      \
	  1          7
	 /  \       /  \
   0     2    6      9
             /  \
            5    8
*/