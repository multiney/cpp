#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <unordered_map>
using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int columnSize = matrix.size(), rowSize = matrix[0].size();
    int num = columnSize * rowSize;
    vector<int> ret(num);
    int k = 0, i = 0, j = 0;
    while (k < num) {
        j = i;
        while (j < rowSize - i)
            ret[k++] = matrix[i][j++];
        j = i + 1;
        while (j < columnSize - i)
            ret[k++] = matrix[j++][rowSize - i - 1];
        j = rowSize - i - 2;
        while (j > i && k < num)
            ret[k++] = matrix[columnSize - i - 1][j--];
        j = columnSize - i - 1;
        while (j > i && k < num)
            ret[k++] = matrix[j--][i];
        ++i;
    }
    return ret;
}
