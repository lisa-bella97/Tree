#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TreeNode
{
private:
	TreeNode* _parent;
	vector<TreeNode*> _children;
	int _value;
public:
	TreeNode(int value) : _value(value) { }
	int getValue() const { return _value; }
	vector<TreeNode*> getChildren() const { return _children; }
	void AddChild(TreeNode* child);
};

class Tree
{
private:
	TreeNode* _root;
public:
	Tree(TreeNode* root) : _root(root) { }
	static void Direct(TreeNode* root);
	static void Reverse(TreeNode* root);
	static void Symmetric(TreeNode* root);
	TreeNode* getRoot() const { return _root; }
	static TreeNode* Create(int* cursors, int n, TreeNode* root, int k = 0);
	static void CountElements(TreeNode* root, int& n);
};

int main(int argc, char* argv[])
{
	cout << "N = ";
	int n;
	cin >> n;
	int* cursors = new int[n];

	for (int i = 0; i < n; i++)
		cin >> cursors[i];

	TreeNode* root = nullptr;
	int pos = 0;

	for (int i = 0; i < n; i++)
		if (cursors[i] == -1)
		{
			if (!root)
			{
				root = new TreeNode(i);
				pos = i;
			}
			else
			{
				cout << "Bad tree\n";
				return 0;
			}
		}

	if (!root)
	{
		cout << "Root is not found\n";
		return 0;
	}

	Tree tree(Tree::Create(cursors, n, root, pos));
	pos = 1;
	Tree::CountElements(tree.getRoot(), pos);
	
	if (pos != n)
	{
		cout << "Bad tree\n";
		return 0;
	}

	cout << "Direct: "<< endl;
	Tree::Direct(tree.getRoot());
	cout << "\nReverse: " << endl;
	Tree::Reverse(tree.getRoot());
	cout << "\nSymmetric: " << endl;
	Tree::Symmetric(tree.getRoot());
	cout << endl;

	system("pause");
	return 0;
}

void Tree::Direct(TreeNode* root)
{
	if (!root)
		return;
	cout << root->getValue() << "  ";
	vector<TreeNode*> _children = root->getChildren();
	for (int i = 0; i < _children.size(); i++)
		Direct(_children[i]);
}

void Tree::Reverse(TreeNode* root)
{
	if (!root)
		return;
	vector<TreeNode*> _children = root->getChildren();
	for (int i = 0; i < _children.size(); i++)
		Reverse(_children[i]);
	cout << root->getValue() << "  ";
}

void Tree::Symmetric(TreeNode* root)
{
	if (!root)
		return;
	vector<TreeNode*> _children = root->getChildren();
	if (_children.size() > 0)
		Symmetric(_children[0]);
	cout << root->getValue() << "  ";
	for (int i = 1; i < _children.size(); i++)
		Symmetric(_children[i]);
}

TreeNode* Tree::Create(int * cursors, int n, TreeNode* root, int k)
{
	if (!root)
		return nullptr;

	for (int i = 0; i < n; i++)
	{
		if (cursors[i] == k)
		{
			TreeNode* child = new TreeNode(i);
			root->AddChild(child);
			Create(cursors, n, child, i);
		}
	}
	return root;
}

void Tree::CountElements(TreeNode * root, int& n)
{
	if (!root)
		return;
	vector<TreeNode*> _children = root->getChildren();
	for (int i = 0; i < _children.size(); i++)
		CountElements(_children[i], ++n);
}

void TreeNode::AddChild(TreeNode * child)
{
	child->_parent = this;
	_children.push_back(child);
}