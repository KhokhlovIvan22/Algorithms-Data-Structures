#include <fstream>
#include <stack>
using namespace std;

struct Node
{
	int key;
	Node* leftChild;
	Node* rightChild;
	Node(int key) : key(key), leftChild(nullptr), rightChild(nullptr) {};
};

class Tree
{
private:
	Node* root;

public:
	Tree() { root = nullptr; }
	Node* getRoot() { return root; }
	void insert(int key)
	{
		Node* parent = nullptr;
		Node* current = root;
		while (current != nullptr)
		{
			parent = current;
			if (key < current->key)
				current = current->leftChild;
			else if (key > current->key)
				current = current->rightChild;
			else
				return;
		}
		Node* newNode = new Node(key);
		if (parent == nullptr)
			root = newNode;
		else if (parent->key < key)
			parent->rightChild = newNode;
		else if (parent->key > key)
			parent->leftChild = newNode;
	}

	void Delete(int key)
	{
		Node* current = root;
		Node* parent = nullptr;
		stack <bool> leftOrRight;
		while (current != nullptr)
		{
			if (key == current->key)
				break;
			if (key < current->key)
			{
				parent = current;
				current = current->leftChild;
				leftOrRight.push(true);
			}
			else
			{
				parent = current;
				current = current->rightChild;
				leftOrRight.push(false);
			}
		}
		if (current == nullptr)
			return;
		if (current->leftChild == nullptr || current->rightChild == nullptr)
		{
			Node* newChild = (current->leftChild != nullptr) ? current->leftChild: current->rightChild;
			if (current == root)
			{
				root = newChild;
				delete current;
			}
			else 
			{
				bool pos = leftOrRight.top();
				if (pos)
					parent->leftChild = newChild;
				else
					parent->rightChild = newChild;
				delete current;
			}
		}
		else 
		{
			Node* newNode = current->rightChild;
			Node* newNodeParent = current;
			while (newNode->leftChild != nullptr)
			{
				newNodeParent = newNode;
				newNode = newNode->leftChild;
			}
			current->key = newNode->key;
			if (newNodeParent->leftChild==newNode)
				newNodeParent->leftChild = newNode->rightChild;
			else 
				newNodeParent->rightChild = newNode->rightChild;
			delete newNode;
		}
	}

	void PreOrderTravesal(Node* v, ofstream& out)
	{
		if (v != nullptr)
		{
			out << v->key << "\n";
			PreOrderTravesal(v->leftChild, out);
			PreOrderTravesal(v->rightChild, out);
		}
	}
};

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	Tree tree;
	int searchKey, insertKey;
	in >> searchKey;
	while (!in.eof())
	{
		in >> insertKey;
		tree.insert(insertKey);
	}
	tree.Delete(searchKey);
	tree.PreOrderTravesal(tree.getRoot(), out);
	return 0;
}
