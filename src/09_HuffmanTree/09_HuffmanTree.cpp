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
    T data;
    int weight;

    operator int() const { // for comparison usage
        return weight;
    }
};

template<typename T>
class HuffmanTree {
public:
    HuffmanTree() {}
    HuffmanTree(const T& e, int w) {
        BinaryTree<HuffmanTreeNode<T> > x; // empty tree
        tree.MakeTree(HuffmanTreeNode<T>(e, w), x, x);
    }

    bool IsEmpty() {
        return tree.IsEmpty();
    }

    HuffmanTree<T>& Merge(HuffmanTree<T>& x, HuffmanTree<T>& y) {
        if (x.IsEmpty() || y.IsEmpty()) {
            throw new InvalideArgument();
        }

        tree.MakeTree(HuffmanTreeNode<T>(
    }

private:
    BinaryTree<HuffmanTreeNode<T> > tree;
};

int main(int argc, char* argv[])
{
    return 0;
}