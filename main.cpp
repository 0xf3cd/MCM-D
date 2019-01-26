#ifndef NODE
#include "Node.h"
#define NODE
#endif
#ifndef LINE
#include "Line.h"
#define LINE
#endif

#include <map>
#include <fstream>
#include <iostream>
using namespace std;

typedef map<int, Node> NM;
typedef map<int, Line> LM;

int node_amount;
int line_amount;
NM node_map; // unno ->  Node
LM line_map; // ulno ->  Node
int** matrix = nullptr; // 邻接矩阵，-1 无连接，否则记录 ulno

void init(string file_addr);
void freeSpace();
void showNode();
void showLine();
void showMatrix();

int main() {
    init("./example.txt");
    // showNode();
    // showLine();
    showMatrix();
    freeSpace();
    return 0;
}

void init(string file_addr) {
    int i, j;
    ifstream fin;

    int unno; // user node no
    int ini_people;

    int ulno;
    int sunno, snno; // start user node no & start node no
    int eunno, enno;
    double llength;
    double lwidth;
    double ldis;

    fin.open(file_addr, ios::in);

    fin >> node_amount;
    for(i = 0; i < node_amount; i++) {
        Node new_node;
        fin >> unno;
        fin >> ini_people;

        new_node.no = i; // Node 编号从 0 开始

        if(ini_people > 0) {
            new_node.ini_people = ini_people;
            new_node.is_exit = false;
        } else if(ini_people == 0) {
            new_node.ini_people = 0;
            new_node.is_exit = true;
        } else { // < 0
            new_node.ini_people = 0;
            new_node.is_exit = false;
        }
        
        node_map[unno] = new_node;
    }

    matrix = new int*[node_amount];
    for(i = 0; i < node_amount; i++) {
        matrix[i] = new int[node_amount];
    }
    for(i = 0; i < node_amount; i++) {
        for(j = 0; j < node_amount; j++) {
            matrix[i][j] = -1;
        }
    }

    fin >> line_amount;
    for(i = 0; i < line_amount; i++) {
        Line new_line;
        fin >> ulno;
        new_line.no = i;

        fin >> sunno; // 从文件中读取用户指定的结点编号
        fin >> eunno;
        snno = node_map[sunno].no; // 得到内存中的结点编号
        enno = node_map[eunno].no;
        new_line.snno = snno;
        new_line.enno = enno;

        fin >> llength;
        fin >> lwidth;
        fin >> ldis;
        new_line.length = llength;
        new_line.width = lwidth;
        new_line.dis_to_danger = ldis;

        line_map[ulno] = new_line;

        matrix[snno][enno] = ulno;
        matrix[enno][snno] = ulno;
    }

    fin.close();
}

void freeSpace() {
    int i;
    for(i = 0; i < node_amount; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void showNode() {
    NM::iterator it;
    for(it = node_map.begin(); it != node_map.end(); it++) {
        cout << it -> first << ": ";
        cout << (it -> second).no << ", ";
        cout << (it -> second).ini_people << ", ";
        cout << (it -> second).is_exit << endl;
    }
}

void showLine() {
    LM::iterator it;
    for(it = line_map.begin(); it != line_map.end(); it++) {
        cout << it -> first << ": ";
        cout << (it -> second).no << ", ";
        cout << (it -> second).enno << ", ";
        cout << (it -> second).snno << ", ";
        cout << (it -> second).length << ", ";
        cout << (it -> second).width << ", ";
        cout << (it -> second).dis_to_danger << endl;
    }
}

void showMatrix() {
    int i, j;
    cout << '\t';
    for(i = 0; i < node_amount; i++) {
        cout << i << '\t';
    }
    cout << endl;

    for(i = 0; i < node_amount; i++) {
        cout << i << '\t';
        for(j = 0; j < node_amount; j++) {
            if(matrix[i][j] == -1) {
                cout << '\t';
            } else {
                cout << matrix[i][j] << '\t';
            }
        }
        cout << endl;
    }
}