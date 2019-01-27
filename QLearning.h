#ifndef NODE
#include "Node.h"
#define NODE
#endif
#ifndef LINE
#include "Line.h"
#define LINE
#endif
#ifndef QTABLE
#include "QTable.h"
#define QTABLE
#endif

#include <map>
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;


struct step {
    int from;
    int to;
};

typedef map<int, int> U2R; // User to Real
typedef map<int, Node> N2N; // No to Node
typedef map<int, Line> N2L; // No to Line
typedef list<int> LI; // list of int
typedef vector<step> VS;

const double EPSILON = 0.9;
const double ALPHA = 0.1;
const double GAMMA = 0.8;
const int UPMOST = 10000;

class QLearning {
public:
    int node_amount;
    int line_amount;
    U2R node_no_map; // User Node No to Real Node No
    U2R node_no_revmap; // reverse of node_no_map
    U2R line_no_map; // Line
    N2N nodes; // unno -> Node
    N2L lines; // ulno -> Node
    int** matrix; // 邻接矩阵，-1 无连接，否则记录 ulno
    QTable Q; // Q 表
    QTable R; // R 表
    LI exits;

    QLearning();
    ~QLearning();
    void init(string file_addr);
    void showNode();
    void showLine();
    void showMatrix();
    void showExit();
    LI getValidNext(int now);
    int getRandomNext(LI next);
    int findBestNext(int now);
    double findMostNextQV(int now);
    bool hasExited(int now);
    int getNext(int now);
    void updateQ(int now, int next);
    bool trainOneTime(int start);
    void showQTable();
    bool randomTrainOneTime();
    void readInQ(string dir);
    VS findWay(int usno);
    VS cvt(VS old);
    void calcAllWays();
};
