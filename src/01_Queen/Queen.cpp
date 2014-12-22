//
// File: Queen.cpp
// Place queen properly so that they won't threaten each other.
// Shining Yang <y.s.n@live.com>, 2014-12-22
//
#include <iostream>
using namespace std;

class Queens {
public:
    Queens(int n = 8) : num(n) {
        placements = new bool[num * num];
        for (int i = 0; i < num * num; i++) {
            placements[i] = false;
        }
    }

    ~Queens() {
        delete[] placements;
    }

    void Place() {
        TryPlace(0);
    }

protected:
    bool _ConflictVertically(int i, int j) const {
        for (int n = 0; n < i; n++) {
            if (placements[n * num + j]) { // [n, j]
                return true;
            }
        }
        return false;
    }

    bool _ConflictDiagonally(int i, int j) const {
        for (int n = 1; n < j; n++) {
            if ((i - n >= 0) && (j - n >= 0)) {
                if (placements[(i - n) * num + j - n]) { // [i-n, j-n]
                    return true;
                }
            }
        }

        for (int m = 1; m < num - j; m++) {
            if ((i - m >= 0) && (j + m < num)) {
                if (placements[(i - m) * num + j + m]) { // [i-m, j+m]
                    return true;
                }
            }
        }

        return false;
    }

    void TryPlace(int row) {
        if (row >= num) {
            Output();
        } else {
            for (int j = 0; j < num; j++) {
                if (!_ConflictVertically(row, j) && !_ConflictDiagonally(row, j)) {
                    placements[row * num + j] = true;
                    TryPlace(row + 1);
                    placements[row * num + j] = false;
                }
            }
        }
    }

    void Output() const {
        static int _count = 0;
        cout << ++_count << ": " << endl;
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < num; j++) {
                cout << (placements[i * num + j] ? "Q" : ".");
            }
            cout << endl;
        }
        cout << endl;
    }

private:
    int num;
    bool* placements;
};



void main()
{
    Queens q(8);
    q.Place();
}
