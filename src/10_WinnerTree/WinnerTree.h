//
// File: WinnerTree.h
// Winner tree.
// Shining Yang <y.s.n@live.com>, 2014-12-15
//
// http://www.geeksforgeeks.org/tournament-tree-and-binary-heap/
// Tournament tree is a form of min(max) heap which is a complete binary tree.
// Every external node represents a player and internal node represents winner.
// In a tournament tree every internal node contains winner and every leaf node
// contains one player.
//
// Tournament tree is also called Winner tree.
//
#pragma once

namespace DSCPP { namespace WinnerTree {

template<typename T>
class WinnerTree {
public:
    WinnerTree();
    virtual ~WinnerTree();

private:

};

}}