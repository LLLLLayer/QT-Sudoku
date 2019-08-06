#ifndef LOGIC_H
#define LOGIC_H

#include <QObject>
#include <vector>
#include <QTimer>
#include "const.h"
#include "debug.h"
#include "dancinglink.h"
using namespace std;

class MainWindow;
struct Operation{
    int x, y, num, flag;
    Operation(){}
    Operation(int x, int y, int num, int flag): x(x), y(y), num(num), flag(flag){
    	
    }
};


class Logic : public QObject{
    Q_OBJECT
    friend class MainWindow;
    friend class Solver;
public:
    Logic(MainWindow *window, QObject *parent = 0): window(window), QObject(parent){
        memset(used, 0, sizeof(used));
        memset(ans, 0, sizeof(ans));
        memset(grid, 0, sizeof(grid));
        pre_x = pre_y = -1;
        m_note = 0;
        timer = new QTimer();
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeChange()));
    }
    ~Logic();
    void processFile(FILE *file, int time);
public slots:
    void generateEasyGame();
    void generateNormalGame();
    void generateHardGame();
    void noteMode();
    void revoke();
    int check();
    int simpleCheck();
    void clear();
    void pause();
    void recover();
    void newSolver();
    void hint();
    void timeChange();
    void restart();
    void showAnswer();
    void setBoardAvailable(int flag);
private:
    void clearNotes(int x, int y);
    void process(const Operation &x, int toShow = 1);
    int pushNumber(int);
    void updateFrame();
    int pushPos(int x, int y);
    std::vector<int> notes[10][10];
    int grid[10][10];
    int used[10][10];
    int ans[10][10];
    int generate(int step = 0);
    int selfCheck();
    int m_note;
    MainWindow *window;
    int pre_x, pre_y;
    vector<Operation> operations;
    vector<Operation> revoked;
    int paused;
    int timeUsed;
    QTimer* timer;
};

#endif // LOGIC_H
