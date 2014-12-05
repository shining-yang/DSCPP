//
// File: 07_SortedChain.cpp
//
// Shining Yang <y.s.n@live.com>, 2014-11-17
//
#include <string>
#include <iostream>

#include "SortedChain.h"
using namespace DSCPP::SortedLinearList;

template<class KT>
class Employee {
public:
    enum SEX { MALE, FEMALE };

    // no need on these
    //Employee(const Employee<KT>& o);
    //Employee& operator=(const Employee<KT>& o);

    Employee() {}
    Employee(KT NO, const std::string& name, SEX sex, int age,
        const std::string& phone, double salary) {
        this->NO = NO;
        this->name = name;
        this->sex = sex;
        this->age = age;
        this->phone = phone;
        this->salary = salary;
    }

    operator KT() const {
        return NO;
    }

    bool operator<(KT k) {
        return NO < k;
    }

    bool operator==(KT k) {
        return NO == k;
    }
    
    template<class T>
    friend std::ostream& operator<<(std::ostream& os, const Employee<T>& obj);

private:
    KT NO;
    std::string name;
    SEX sex;
    int age;
    std::string phone;
    double salary;
};


template<class KT>
std::ostream& operator<<(std::ostream& os, const Employee<KT>& obj)
{
    os << "NO: " << obj.NO
        << " Name: " << obj.name
        << " Gender: " << (obj.sex == Employee<KT>::MALE ? "M" : "F")
        << " Age: " << obj.age
        << " Phone: " << obj.phone
        << " Salary: " << obj.salary
        << std::endl;
    
    return os;
}

void test1()
{
    typedef int EmpKT;
    typedef Employee<EmpKT> Emp;

    Emp e1(1, "Larry", Emp::MALE, 44, "Lumia 1520", 1000);
    Emp e2(2, "Euler", Emp::MALE, 48, "Lumia 1020", 9000);
    Emp e3(3, "Dijkstra", Emp::MALE, 47, "Lumia 830", 2500);
    Emp e4(4, "Huffman", Emp::MALE, 46, "Lumia 630", 3000);
    Emp e5(5, "Stroustrup", Emp::MALE, 49, "Lumia 920", 8000);
    Emp e6(6, "Julie", Emp::FEMALE, 32, "iPhone 6 plus", 4000);

    SortedChain<Emp, EmpKT> s;
    Emp dummy;

    s.Insert(e1).Insert(e2).Insert(e3).Insert(e4).Insert(e5).Insert(e6);
    std::cout << s << std::endl;

    s.Delete(3, dummy);
    std::cout << dummy << endl;
}

int main(int argc, char* argv[])
{
#if 0
    int dummy;
    SortedChain<int, int> s;
    s.Insert(5).Insert(10).Insert(20).Insert(12).Insert(25).Delete(12, dummy).Insert(30);
    s.Insert(15).Delete(5, dummy).Delete(15, dummy).Delete(25, dummy).Insert(10).Insert(20).Insert(60);
    std::cout << "Sorted Chain:" << std::endl;
    std::cout << s << std::endl;

    s.Delete(-1, dummy);
    s.InsertDistinct(20);
#else
    test1();
#endif

    return 0;
}
