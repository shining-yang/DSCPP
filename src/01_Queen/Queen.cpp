//
// File: Queen.cpp
// Place queen properly so that they won't threaten each other.
// Shining Yang <y.s.n@live.com>, 2014-12-22
//
#include <iostream>
using namespace std;


class Queens {
public:
    Queens(int n = 8) : N(n) {
        placement = new bool[N * N];
        for (int i = 0; i < N * N; i++) {
            placement = false;
        }
    }

    ~Queens() {
        delete[] placement;
    }

    void TryPlace() const;

protected:
    bool _ConflictVertically(int i, int j) const {
        for (int n = 0; n < i; n++) {
            if (placement[n * N + j]) { // [n, j]
                return true;
            }
        }
        return false;
    }

private:
    int N;
    bool* placement;
};

void Queens::TryPlace() const
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
        }
    }
}

void main()
{
    Queens q(8);
    q.TryPlace();
}
