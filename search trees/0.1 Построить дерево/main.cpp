#include <fstream>
using namespace std;

struct Node
{
	int key;
	Node* leftChild;
	Node* rightChild;
	Node(int key): key(key), leftChild(nullptr), rightChild(nullptr) {};
};

class Tree 
{
private:
	Node* root;

public:
	Tree() {root = nullptr;}
	Node* getRoot(){return root;}
	void insert(int key)
	{
		Node* parent = nullptr;
		Node* current = root;
		while (current!=nullptr)
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

	void PreOrderTravesal(Node *v, ofstream& out) 
	{
		if (v != nullptr)
		{
			out << v->key<<"\n";
			PreOrderTravesal(v->leftChild,out);
			PreOrderTravesal(v->rightChild,out);
		}
	}
};


int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	int x;
	Tree tree;
	while (!in.eof())
	{
		in >> x;
		tree.insert(x);
	}
	tree.PreOrderTravesal(tree.getRoot(), out);
	return 0;
}
