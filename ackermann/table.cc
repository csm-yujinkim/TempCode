#include <iostream>
#include <vector>

typedef std::vector<int> vector1d;
typedef std::vector<std::vector<int>> vector2d;

// there is a major problem with this function.
// there are many more columns needed in the earlier rows.
int ackermann(int i, int j, vector2d &memo) {
    if (i < 1 || j < 1) {
        return -1;
    }

    int r, c;

    // preallocate space
    for (r = 0; r <= i; ++r) {
        memo.push_back(vector1d(j + 1));
    }

    // populate first row
    for (c = 1; c <= j; ++c) {
        memo[1][c] = 1 << c;
    }

    // fill up the table
    for (r = 2; r <= i; ++r) {
        // first column (base case)
        memo[r][1] = memo[r - 1][2];

        // other columns (inductive case)
        for (c = 2; c <= j; ++c) {
            memo[r][c] = memo[r - 1][memo[r][c - 1]];
        }
    }

    // return the value
    return memo[i][j];
}

void showv2d(vector2d const &v) {
    // show, ignore row/column 0
    std::cout << " \t";
    for (int c = 1; c < v[0].size(); ++c) {
        std::cout << c << '\t';
    }
    std::cout << "<<column numbers\n";
    for (int r = 1; r < v.size(); ++r) {
        std::cout << r << '\t';
        vector1d const &subv = v[r];
        for (int c = 1; c < subv.size(); ++c) {
            std::cout << subv[c] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main() {
    int i = 3, j = 4;

    vector2d v2d;

    int r = ackermann(i, j, v2d);

    showv2d(v2d);

    std::cout << "Result: " << r << std::endl;

    return 0;
}
