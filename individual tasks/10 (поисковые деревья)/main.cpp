#include <fstream>
using namespace std;

struct Node
{
    int key;
    Node* leftChild;
    Node* rightChild;
    int height;
    int MSL;
    int leaves;
    int cover;
    Node(int x): key(x), leftChild(nullptr), rightChild(nullptr), height(0), MSL(0), leaves(0), cover(0) {}
};

class Tree
{
private:
    Node* root;
    int maxMSL;
    int bestCover;
    Node* bestRoot;

public:
    Tree(): root(nullptr), maxMSL(0), bestCover(-1), bestRoot(nullptr) {}

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
            else return;
        }
        Node* newNode = new Node(key);
        if (parent == nullptr)
            root = newNode;
        else if (key < parent->key)
            parent->leftChild = newNode;
        else parent->rightChild = newNode;
    }

    void Delete(Node* v, Node* parent, bool twoChildren = false)
    {
        if (v != nullptr)
        {
            Node* newChild = nullptr;
            if (v->leftChild == nullptr && v->rightChild == nullptr)
                newChild = nullptr;
            else if (v->leftChild == nullptr)
                newChild = v->rightChild;
            else if (v->rightChild == nullptr)
                newChild = v->leftChild;
            else
            {
                if (twoChildren == false)
                    return;
                Node* currentParent = v;
                Node* current = v->rightChild;
                while (current->leftChild != nullptr)
                {
                    currentParent = current;
                    current = current->leftChild;
                }
                v->key = current->key;
                if (currentParent->leftChild == current)
                    currentParent->leftChild = current->rightChild;
                else
                    currentParent->rightChild = current->rightChild;
                delete current;
                return;
            }
            if (v == root)
                root = newChild;
            else if (parent != nullptr && parent->leftChild == v)
                parent->leftChild = newChild;
            else if (parent != nullptr)
                parent->rightChild = newChild;
            delete v;
        }
    }

    Node* findParent(Node* v, Node* node, Node* parent = nullptr)
    {
        if (v == nullptr)
            return nullptr;
        if (v == node)
            return parent;
        Node* current = findParent(v->leftChild, node, v);
        if (current != nullptr)
            return current;
        return findParent(v->rightChild, node, v);
    }

    void countHeight(Node* v)
    {
        if (v->leftChild == nullptr && v->rightChild == nullptr)
            v->height = 0;
        else if (v->leftChild == nullptr)
            v->height = v->rightChild->height + 1;
        else if (v->rightChild == nullptr)
            v->height = v->leftChild->height + 1;
        else
            v->height = (v->leftChild->height < v->rightChild->height) ? v->rightChild->height + 1 : v->leftChild->height + 1;
    }

    void countMSL(Node* v)
    {
        if (v->leftChild == nullptr && v->rightChild == nullptr)
            v->MSL = 0;
        else if (v->leftChild == nullptr)
            v->MSL = v->rightChild->height + 1;
        else if (v->rightChild == nullptr)
            v->MSL = v->leftChild->height + 1;
        else v->MSL = v->leftChild->height + v->rightChild->height + 2;
        if (v->MSL > maxMSL)
            maxMSL = v->MSL;
    }

    void countLeaves(Node* v)
    {
        if (v->leftChild == nullptr && v->rightChild == nullptr)
            v->leaves = 1;
        else if (v->leftChild == nullptr)
            v->leaves = v->rightChild->leaves;
        else if (v->rightChild == nullptr)
            v->leaves = v->leftChild->leaves;
        else if (v->leftChild->height == v->rightChild->height)
            v->leaves = v->leftChild->leaves + v->rightChild->leaves;
        else
            v->leaves = (v->leftChild->height < v->rightChild->height) ? v->rightChild->leaves : v->leftChild->leaves;
    }

    void PostOrderTraversal1(Node* v)
    {
        if (v != nullptr)
        {
            PostOrderTraversal1(v->leftChild);
            PostOrderTraversal1(v->rightChild);
            countHeight(v);
            countMSL(v);
            countLeaves(v);
        }
    }

    void markLeft(Node* v, int need, int right)
    {
        if (v != nullptr)
        {
            v->cover += right * v->leaves;
            if (need == 0)
                return;
            if (v->leftChild!=nullptr && v->leftChild->height == need - 1)
                markLeft(v->leftChild, need - 1, right);
            if (v->rightChild!=nullptr && v->rightChild->height == need - 1)
                markLeft(v->rightChild, need - 1, right);
        }
    }

    void markRight(Node* v, int need, int left)
    {
        if (v != nullptr)
        {
            v->cover += left * v->leaves;
            if (need == 0)
                return;
            if (v->leftChild != nullptr && v->leftChild->height == need - 1)
                markRight(v->leftChild, need - 1, left);
            if (v->rightChild != nullptr && v->rightChild->height == need - 1)
                markRight(v->rightChild, need - 1, left);
        }
    }

    void processRoot(Node* r)
    {
        if (r->leftChild == nullptr && r->rightChild == nullptr)
            return;
        if (r->rightChild == nullptr)
        {
            r->cover += r->leftChild->leaves;
            markLeft(r->leftChild, r->leftChild->height, 1);
            return;
        }
        if (r->leftChild == nullptr)
        {
            int R = r->rightChild->leaves;
            r->cover += R; 
            markRight(r->rightChild, r->rightChild->height, 1);
            return;
        }
        int L = r->leftChild->leaves;
        int R = r->rightChild->leaves;
        r->cover += L * R;
        markLeft(r->leftChild, r->leftChild->height, R);
        markRight(r->rightChild, r->rightChild->height, L);
    }


    void PostOrderTraversal2(Node* v)
    {
        if (v != nullptr)
        {
            PostOrderTraversal2(v->leftChild);
            PostOrderTraversal2(v->rightChild);
            if (v->MSL == maxMSL)
                processRoot(v);
        }
    }

    void chooseBestRoot(Node* v)
    {
        if (v != nullptr)
        {
            if (v->MSL == maxMSL && v->cover > bestCover)
            {
                bestCover = v->cover;
                bestRoot = v;
            }
            chooseBestRoot(v->leftChild);
            chooseBestRoot(v->rightChild);
        }
    }

    void deleteOnBranches(Node* v, Node* parent, int need)
    {
        if (v != nullptr)
        {
            if (v->leftChild != nullptr && v->leftChild->height == need - 1)
                deleteOnBranches(v->leftChild, v, need - 1);

            if (v->rightChild != nullptr && v->rightChild->height == need - 1)
                deleteOnBranches(v->rightChild, v, need - 1);
            if (v->cover == bestCover)
                Delete(v, parent, (v->leftChild != nullptr && v->rightChild != nullptr));
        }
    }

    void Deletion()
    {
        if (bestRoot->leftChild != nullptr)
            deleteOnBranches(bestRoot->leftChild, bestRoot, bestRoot->leftChild->height);
        if (bestRoot->rightChild != nullptr)
            deleteOnBranches(bestRoot->rightChild, bestRoot, bestRoot->rightChild->height);
        if (bestRoot == root && bestRoot->leftChild == nullptr && bestRoot->rightChild == nullptr)
        return;
        Node* parent = findParent(root, bestRoot);
        Delete(bestRoot, parent, true);
    }

    void PreOrderTraversal(Node* v, ofstream& out)
    {
        if (v != nullptr)
        {
            out << v->key << "\n";
            PreOrderTraversal(v->leftChild, out);
            PreOrderTraversal(v->rightChild, out);
        }
    }

};

int main()
{
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    Tree tree;
    int x;
    while (fin >> x)
        tree.insert(x);
    tree.PostOrderTraversal1(tree.getRoot());
    tree.PostOrderTraversal2(tree.getRoot());
    tree.chooseBestRoot(tree.getRoot());
    tree.Deletion();
    tree.PreOrderTraversal(tree.getRoot(), fout);
    return 0;
}
