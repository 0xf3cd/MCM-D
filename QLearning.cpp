#ifndef QLEARNING
#include "QLearning.h"
#define QLEARNING
#endif

QLearning::QLearning() {
    node_amount = 0;
    line_amount = 0;
    matrix = nullptr;
}

QLearning::~QLearning() {
    int i;
    for(i = 0; i < node_amount; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void QLearning::init(string file_addr) {
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
        
        node_no_map[unno] = i;
        nodes[i] = new_node;
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
        snno = node_no_map[sunno]; // 得到内存中的结点编号
        enno = node_no_map[eunno];
        new_line.snno = snno;
        new_line.enno = enno;

        fin >> llength;
        fin >> lwidth;
        fin >> ldis;
        new_line.length = llength;
        new_line.width = lwidth;
        new_line.dis_to_danger = ldis;

        line_no_map[ulno] = i;
        lines[i] = new_line;

        matrix[snno][enno] = i;
        matrix[enno][snno] = i;
    }

    fin.close();

    t.init(node_amount);
}

void QLearning::showNode() {
    N2N::iterator it;
    for(it = nodes.begin(); it != nodes.end(); it++) {
        cout << it -> first << ": ";
        cout << (it -> second).no << ", ";
        cout << (it -> second).ini_people << ", ";
        cout << (it -> second).is_exit << endl;
    }
}

void QLearning::showLine() {
    N2L::iterator it;
    for(it = lines.begin(); it != lines.end(); it++) {
        cout << it -> first << ": ";
        cout << (it -> second).no << ", ";
        cout << (it -> second).enno << ", ";
        cout << (it -> second).snno << ", ";
        cout << (it -> second).length << ", ";
        cout << (it -> second).width << ", ";
        cout << (it -> second).dis_to_danger << endl;
    }
}

void QLearning::showMatrix() {
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