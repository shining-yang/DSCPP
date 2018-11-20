//
// File: 09_HuffmanTree.cpp
// Using Huffman algorithm to build a Huffman-tree.
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
ostream& operator<<(ostream& os, const HuffmanTreeNode<T>& node) {
  os << node.data << ":" << node.weight;
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
    if (this != &obj) {
      obj.tree.Clone(tree);
    }

    return *this;
  }

  bool operator<(const HuffmanTree<T>& obj) const {
    return GetWeight() < obj.GetWeight();
  }

  bool operator>(const HuffmanTree<T>& obj) const {
    return GetWeight() > obj.GetWeight();
  }

  bool IsEmpty() {
    return tree.IsEmpty();
  }

  int GetWeight() const { // Retrieve the weight of Huffman Tree
    HuffmanTreeNode<T> x;
    if (!tree.GetRoot(x)) {
      throw new ItemNotExisted();
    }

    return static_cast<int>(x);
  }

  void PrintTree(int width) const {
    tree.PrintVertically(width);
  }

  HuffmanTree<T>& MakeTree(HuffmanTree<T>& x, HuffmanTree<T>& y) {
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


void TestHuffmanTree() {
  typedef HuffmanTreeNode<char> HTNODE;
  typedef HuffmanTree<char> HT;

  HTNODE inputs[] = {
    { 'A', 1 }, { 'B', 2 }, { 'C', 3 }, { 'D', 4 }, { 'E', 5 },
    { 'F', 6 }, { 'G', 7 }, { 'H', 8 }, { 'I', 9 }
  };

  int sz = sizeof(inputs) / sizeof(inputs[0]);

  MinHBLT<HT>  minHBLT;
  for (int i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++) {
    minHBLT.Insert(HT(inputs[i].data, inputs[i].weight));
  }

  HT x, y, z;
  while (true) {
    minHBLT.DeleteMin(x);
    if (minHBLT.IsEmpty()) {
      break;
    }

    minHBLT.DeleteMin(y);

    z.MakeTree(x, y);
    minHBLT.Insert(z);
  }

  x.PrintTree(64);
}

int main(int argc, char* argv[]) {
//     for (int i = 0; i < 4096; i++)
  {
    TestHuffmanTree();
  }

  return 0;
}