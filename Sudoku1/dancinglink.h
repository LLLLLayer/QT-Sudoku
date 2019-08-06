#ifndef DANCINGLINK_H
#define DANCINGLINK_H
#include <vector>
#include <functional>
using namespace std;

typedef vector<int> IntList;
typedef vector<IntList> IntMatrix;

class DancingLink
{
public:
    DancingLink(int row ,int col);
    int appendRow(const IntList& cols);
    void remove(int col);
    void restore(int col);
    int dfs(int level, const std::function<bool()>& callback);
    IntList solve();
    bool solveUnique(IntList&);
private:
    int colNum, rowNum;
    int nodeNow, rowNow;
    IntList columnNode;
    IntList L, R, U, D;
    IntList belongRow, belongCol;
    IntList answer;
    int answerNum;
};

#endif // DANCINGLINK_H
