#include "dancinglink.h"
DancingLink::DancingLink(int row, int col)
{
    rowNum=row;
    colNum=col;
    int nodeNum=(rowNum+1)*(colNum+1)+colNum+2;
    columnNode.assign(colNum+1,0);
    belongRow.assign(nodeNum,0);
    belongCol.assign(nodeNum,0);
    L.assign(nodeNum, 0);
    R.assign(nodeNum, 0);
    U.assign(nodeNum, 0);
    D.assign(nodeNum, 0);
    rowNow=1;
    nodeNow=colNum+1;
    for(int i = 0; i <= colNum; ++i)
    {
        L[i] = i - 1;
        R[i] = i + 1;
        U[i] = D[i] = i;
    }

    L[0] = colNum;
    R[colNum] = 0;
}

int DancingLink::appendRow(const IntList &cols)
{
    int firstNodeNow=nodeNow;
    for(int col:cols)
    {
        belongRow[nodeNow]=rowNow;
        belongCol[nodeNow]=col;
        L[nodeNow] = nodeNow - 1;
        R[nodeNow] = nodeNow + 1;
        D[nodeNow] = col;
        U[nodeNow] = U[col];
        ++columnNode[col];
        ++nodeNow;
    }
    L[firstNodeNow] = nodeNow - 1;
    R[nodeNow - 1] = firstNodeNow;
    return rowNow++;
}

void DancingLink::remove(int col)
{
    L[R[col]] = L[col];
    R[L[col]] = R[col];
    for(int i = D[col]; i != col; i = D[i])
    {
        for(int j = R[i]; j != i; j = R[j])
        {
            U[D[j]] = U[j];
            D[U[j]] = D[j];
            --columnNode[belongCol[j]];
        }
    }
}

void DancingLink::restore(int col)
{
    for(int i = U[col]; i != col; i = U[i])
    {
        for(int j = L[i]; j != i; j = L[j])
        {
            U[D[j]] = j;
            D[U[j]] = j;
            ++columnNode[belongCol[j]];
        }
    }
    L[R[col]] = col;
    R[L[col]] = col;
}

int DancingLink::dfs(int level, const std::function<bool ()> &callback)
{
    if(R[0] == 0)
    {
        answerNum = level;
        return callback();
    }
    int minNodeInCol = R[0];
    for(int i = R[0]; i != 0; i = R[i])
    {
        if(columnNode[i] < columnNode[minNodeInCol])
            minNodeInCol = i;
    }
    remove(minNodeInCol);
    int m = minNodeInCol;
    for(int i = D[m]; i != m; i = D[i])
    {
        answer[level] = belongRow[i];
        for(int k = R[i]; k != i; k = R[k])
            remove(belongCol[k]);
        if(dfs(level + 1, callback)) return 1;
        for(int k = L[i]; k != i; k = L[k])
            restore(belongCol[k]);
    }
    restore(minNodeInCol);
    return 0;
}

IntList DancingLink::solve()
{
    answerNum = 0;
    answer.assign(rowNum + 1, 0);
    if(!dfs(0, []() { return true; })) return {};
    return IntList(answer.begin(), answer.begin() + answerNum);
}

bool DancingLink::solveUnique(IntList& ans)
{
    int count = 0;
    answerNum = 0;
    answer.assign(rowNum + 1, 0);
    dfs(0, [&]() { return ++count > 1; });
    if(count == 0)
    {
        ans = {};
        return false;
    } else {
        ans = IntList(answer.begin(), answer.begin() + answerNum);
        return count == 1;
    }
}
