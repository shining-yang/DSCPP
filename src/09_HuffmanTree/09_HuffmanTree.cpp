//
// File: 09_HuffmanTree.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-10
//
#include <iostream>
#include "../08_BinaryTree/BinaryTree.h"
#include "../09_HeightBiasedLeftistTree/HeightBiasedLeftistTree.h"
using namespace std;
using namespace DSCPP::BinaryTree;
using namespace DSCPP::PriorityQueue;

template<typename T>
struct HuffmanTreeNode {
    HuffmanTreeNode() {}
    HuffmanTreeNode(const T&e, int w) : data(e), weight(w) {}

    operator int() const { // for comparison usage
        return weight;
    }

    T data;
    int weight;
};

template<typename T>
ostream& operator<<(ostream& os, const HuffmanTreeNode<T>& node)
{
    if (node.data) {
        os << node.data;
    } else {
        os << "*";
    }

    //os << node.data << ":" << node.weight;
    return os;
}

template<typename T>
class HuffmanTree {
public:
    HuffmanTree() {
    }

    HuffmanTree(const T& e, int w) {
        BinaryTree<HuffmanTreeNode<T> > x; // empty tree
        tree.MakeTree(HuffmanTreeNode<T>(e, w), x, x);
    }

    HuffmanTree(const HuffmanTree<T>& obj) {
        obj.tree.Clone(tree);
    }

    HuffmanTree<T>& operator=(const HuffmanTree<T>& obj) {
        if (this == &obj) {
            return *this;
        }

        obj.tree.Clone(tree);
        return *this;
    }

    bool operator<(const HuffmanTree<T>& obj) const {
        HuffmanTreeNode<T> x;
        if (!tree.GetRoot(x)) {
            throw new ItemNotExisted();
        }

        HuffmanTreeNode<T> y;
        if (!obj.tree.GetRoot(y)) {
            throw new ItemNotExisted();
        }

        return static_cast<int>(x) < static_cast<int>(y);
    }

    bool operator>(const HuffmanTree<T>& obj) const {
        HuffmanTreeNode<T> x;
        if (!tree.GetRoot(x)) {
            throw new ItemNotExisted();
        }

        HuffmanTreeNode<T> y;
        if (!obj.tree.GetRoot(y)) {
            throw new ItemNotExisted();
        }

        return static_cast<int>(x) > static_cast<int>(y);
    }

    bool IsEmpty() {
        return tree.IsEmpty();
    }

    int GetWeight() {
        HuffmanTreeNode<T> x;
        if (!tree.GetRoot(x)) {
            throw new ItemNotExisted();
        }

        return x.weight;
    }

    void PrintTree(int width) const {
        tree.PrintVertically(width);
    }

    HuffmanTree<T>& Merge(HuffmanTree<T>& x, HuffmanTree<T>& y) {
        if (x.IsEmpty() || y.IsEmpty()) {
            throw new InvalideArgument();
        }

        tree.MakeTree(HuffmanTreeNode<T>(0, x.GetWeight() + y.GetWeight()),
            x.tree, y.tree);
        
        return *this;
    }

private:
    BinaryTree<HuffmanTreeNode<T> > tree;
};


void TestHuffmanTree()
{
    typedef HuffmanTreeNode<char> HTNODE;
    typedef HuffmanTree<char> HT;

    HTNODE inputs[] = {
        { 'A', 1 }, { 'B', 2 }, { 'C', 3 }, { 'D', 4 }, { 'E', 5 },
        { 'F', 6 }, { 'G', 7 }, { 'H', 8 }, { 'I', 9 }
    };

    int sz = sizeof(inputs) / sizeof(inputs[0]);

    MinHBLT<HT>  mh;
    for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++) {
        mh.Insert(HT(inputs[i].data, inputs[i].weight));
    }

    HT x, y, z;
    while (true) {
        mh.DeleteMin(x);
        if (mh.IsEmpty()) {
            break;
        }

        mh.DeleteMin(y);

        z.Merge(x, y);
        mh.Insert(z);
    }

    x.PrintTree(96);
}

int main(int argc, char* argv[])
{
//     for (int i = 0; i < 4096; i++)
    {
        TestHuffmanTree();
    }

    return 0;
}