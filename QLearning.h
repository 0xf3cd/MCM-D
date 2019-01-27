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
#include <fstream>
#include <iostream>
using namespace std;

typedef map<int, int> U2R; // User to Real
typedef map<int, Node> N2N; // No to Node
typedef map<int, Line> N2L; // No to Line

class QLearning {
public:
    int node_amount;
    int line_amount;
    U2R node_no_map; // User Node No to Real Node No
    U2R line_no_map; // Line
    N2N nodes; // unno -> Node
    N2L lines; // ulno -> Node
    int** matrix; // 邻接矩阵，-1 无连接，否则记录 ulno
    QTable t;

    QLearning();
    ~QLearning();
    void init(string file_addr);
    void showNode();
    void showLine();
    void showMatrix();
};