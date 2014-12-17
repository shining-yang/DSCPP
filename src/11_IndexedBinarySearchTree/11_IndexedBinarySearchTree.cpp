//
// File: 11_IndexedBinarySearchTree.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-16
//
#include <iostream>
#include <string>
#include "IndexedBinarySearchTree.h"

using namespace std;
using namespace DSCPP::SearchTree;

class SmartPhone {
public:
    /*
     * Copy-constructor and assignment operator are not mandatory for this
     * simple class, since its members will implicitly do that.
     */
    SmartPhone() {}
    SmartPhone(const std::string& m, const std::string& v, int p)
        : model(m), vendor(v), price(p) {}

    operator int() const {
        return price;
    }

private:
    std::string model;
    std::string vendor;
    int price;
    friend ostream& operator<<(ostream& os, const SmartPhone& ph);
};

ostream& operator<<(ostream& os, const SmartPhone& ph)
{
    os << ph.model << " $" << ph.price;
    return os;
}

int main(int argc, char* argv[])
{
    int dummy;
    IndexedBSTree<int, int> x, a, b, c, d;
    a.MakeTree(IndexedBSTreeNodeInfo<int, int>(1, 1), x, x);
    b.MakeTree(IndexedBSTreeNodeInfo<int, int>(4, 2), a, x);
    c.MakeTree(IndexedBSTreeNodeInfo<int, int>(8, 1), x, x);
    d.MakeTree(IndexedBSTreeNodeInfo<int, int>(6, 3), b, c);
    d.PrintVerticallyWithLine(64);

    cout << "Found: " << (d.Search(1, dummy) ? "Yes" : "No") << endl;

    //--
    IndexedBSTree<int, int> ibst;
    ibst.Insert(5).Insert(9).Insert(4).Insert(2).Insert(1).Insert(7).Insert(6).Insert(8);
    ibst.PrintVerticallyWithLine(64);

    //-- compare two trees
    cout << "The two trees are equal? " << (ibst.Compare(d) ? "Yes" : "No") << endl;
    
    //--
    cout << endl;
    IndexedBSTree<SmartPhone, int> phones;
    phones.Insert(SmartPhone("Lumia 930", "Nokia", 4599));
    phones.Insert(SmartPhone("iPhone 6 Plus", "Apple", 7999));
    phones.Insert(SmartPhone("Galaxy Note III", "Samsung", 5199));
    phones.Insert(SmartPhone("Mate 7", "Huawei", 4299));
    phones.Insert(SmartPhone("Mi 4", "Xiaomi", 1999));
    phones.Insert(SmartPhone("MX III", "Meizu", 2599));
    phones.Insert(SmartPhone("HTC 8X", "HTC", 2199));
    phones.PrintVerticallyWithLine(76);

    //--
    cout << endl;
    phones.OutputAscending();
    cout << endl;

    SmartPhone dummyPhone;

    //--
    cout << endl << "Test IndexSearch():" << endl;
    for (int idx = 0; idx < 100; idx++) {
        if (phones.IndexSearch(idx, dummyPhone)) {
            cout << "Index " << idx << ": " << dummyPhone << endl;
        }
    }

    cout << endl;

    //--
    try {
        phones.Delete(4599, dummyPhone);
        cout << "Deleted by key: " << dummyPhone << endl;
    } catch (ItemNotExisted* e) {
        delete e;
        cout << "Item not exists." << endl;
    }

    phones.PrintVerticallyWithLine(76);

    //--
    try {
        phones.IndexDelete(2, dummyPhone);
        cout << "Deleted by index: " << dummyPhone << endl;
    } catch (ItemNotExisted* e) {
        delete e;
        cout << "Item with specified index cannot been found." << endl;
    }

    phones.OutputAscending();

    cout << endl;
    cout << "Number of phones left: " << phones.GetCount() << endl;
    return 0;
}