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
    bool _ConflictVertically(int r, int c) const {
        for (int i = 0; i < r; i++) {
            if (placements[i * num + c]) {
                return true;
            }
        }

        return false;
    }

    bool _ConflictDiagonally(int r, int c) const {
        for (int i = r - 1, j = c - 1; i >= 0 && j >= 0; i--, j--) {
            if (placements[i * num + j]) {
                return true;
            }
        }

        for (int i = r - 1, j = c + 1; i >= 0 && j < num; i--, j++) {
            if (placements[i * num + j]) {
                return true;
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
        cout << "Solution " << ++_count << ": " << endl;
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
