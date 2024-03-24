//
// File: 09_PriorityQueue.cpp
// Shining Yang <y.s.n@live.com>, 2014-12-05
//
#include "PriorityQueue.h"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
using namespace DSCPP::PriorityQueue;

class Motor {
public:
  Motor() {}
  Motor(const std::string &v, const std::string &m, double p, int pri)
      : vendor(v), model(m), price(p), priority(pri) {}

  operator int() const { return priority; }

  operator double() const { return price; }

  friend ostream &operator<<(ostream &os, const Motor &m);

private:
  std::string vendor;
  std::string model;
  double price;
  int priority;
};

ostream &operator<<(ostream &os, const Motor &m) {
  os << setiosflags(std::ios::left) << setw(8) << m.vendor << ", "
     << resetiosflags(std::ios::left) << setw(4) << m.model << ", " << "$"
     << setprecision(2) << setiosflags(std::ios::fixed) << m.price << ", "
     << setw(10) << m.priority;
  return os;
}

int main(int argc, char *argv[]) {
  PriorityQueue<Motor, int> pq;

  Motor m1("BMW", "i8", 250000.99, 3);
  Motor m2("Mercedes", "C800", 275000.0, 2);

  pq.EnQueue(m1);
  pq.EnQueue(m2);
  pq.EnQueue(Motor("Audi", "A7", 230000.0, 4));
  pq.EnQueue(Motor("Porsche", "Macan", 180000.0, 5));
  pq.EnQueue(Motor("Chevy", "Camaro", 120000.0, 6));
  pq.EnQueue(Motor("Rolls Royce", "LV", 3000000.0, 1));
  pq.EnQueue(Motor("Cadillac", "CTS", 190000.0, 3));

  while (pq.Length()) {
    std::cout << "Max: " << pq.Max() << endl;
    pq.DeQueue(m1);
    std::cout << "Delete item: " << m1 << endl;
  }

  return 0;
}