#ifndef QLEARNING
#include "QLearning.h"
#define QLEARNING
#endif

#include <vector>
#include <algorithm>
#include <fstream>

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

    int r_amount;
    double r_value;

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
            exits.push_back(i);
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

    Q.init(node_amount);
    R.init(node_amount);

    // TODO: 接下来读入部分点的初始奖励值于 R 中

    fin >> r_amount;
    // cout << r_amount << endl;
    for(i = 0; i < r_amount; i++) {
        fin >> sunno; // 从文件中读取用户指定的结点编号
        fin >> eunno;
        fin >> r_value;
        snno = node_no_map[sunno]; // 得到内存中的结点编号
        enno = node_no_map[eunno];
        R.setV(snno, enno, r_value);
        // cout << snno << " -> " << enno << ": " << r_value << endl;
    }

    srand(time(NULL));
    fin.close();

    U2R::iterator it;
    for(it = node_no_map.begin(); it != node_no_map.end(); it++) {
        node_no_revmap[it -> second] = it -> first;
    }
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

void QLearning::showExit() {
    LI::iterator it;
    for(it = exits.begin(); it != exits.end(); it++) {
        cout << *it << endl;
    }
}

LI QLearning::getValidNext(int now) {
    LI next;
    int i;
    
    for(i = 0; i < node_amount; i++) {
        if(matrix[now][i] != -1) {
            next.push_back(i);
        }
    }

    return next;
}

int QLearning::getRandomNext(LI next) {
    int i;
    int length = next.size();
    int temp = rand()%length;
    LI::iterator it;
    it = next.begin();
    for(i = 1; i <= temp; i++) {
        it++;
    }
    return *it;
}

int QLearning::findBestNext(int now) {
    LI next = getValidNext(now);
    LI::iterator it;
    double r;
    int n;
    
    n = getRandomNext(next);
    r = Q.getV(now, n);

    for(it = next.begin(); it != next.end(); it++) {
        if(Q.getV(now, *it) > r) {
            n = *it;
            r = Q.getV(now, *it);
        }
    }

    return n;
}

double QLearning::findMostNextQV(int now) {
    LI next = getValidNext(now);
    LI::iterator it;
    double r = -100000000;
    for(it = next.begin(); it != next.end(); it++) {
        if(Q.getV(now, *it) > r) {
            r = Q.getV(now, *it);
        }
    }
    return r;
}

bool QLearning::hasExited(int now) {
    if(find(exits.begin(), exits.end(), now) != exits.end()) {
        return true;
    } else {
        return false;
    }
}

int QLearning::getNext(int now) {
    double ep = double(rand() % 10000) / 10000.0;
    if(ep > EPSILON) {
        // 随机选一步
        return getRandomNext(getValidNext(now));
    } else {
        // 选取最大 Q Value 的一步
        return findBestNext(now);
    }
}

void QLearning::updateQ(int now, int next) {
    double newV = 0;
    newV += (1 - ALPHA) * Q.getV(now, next);
    newV += ALPHA * (R.getV(now, next) + GAMMA * findMostNextQV(next));
    Q.setV(now, next, newV);
}

bool QLearning::trainOneTime(int start) {
    int now, next;
    int count = 0;
    now = start;

    while(count <= UPMOST) {
        if(hasExited(now)) {
            return true;
        }
        next = getNext(now);
        updateQ(now, next);
        // cout << now << " -> " << next << endl;
        now = next;
        count++;
    }
    return false;
}

bool QLearning::randomTrainOneTime() {
    int start = rand() % node_amount;
    return trainOneTime(start);
}

void QLearning::showQTable() {
    Q.show();
}

void QLearning::readInQ(string dir) {
    int i, j;
    double t;
    ifstream fin;
    fin.open(dir, ios::in);

    // cout << fin.is_open() << endl;

    for(i = 0; i < node_amount; i++) {
        for(j = 0; j < node_amount; j++) {
            fin >> t;
            Q.setV(i, j, t);
        }
    }

    fin.close();
}

VS QLearning::findWay(int usno) {
    int i;
    int now, next;
    int old_from; 
    int count = 0;
    now = node_no_map[usno];
    bool enter = false;

    VS v;
    VS::iterator it;

    while(count <= UPMOST) {
        enter = false;
        if(hasExited(now)) {
            return v;
        }
        next = getNext(now); //findBestNext(now);

        for(it = v.begin(); it != v.end(); it++) {
            if(matrix[it->from][next] != -1) {
                old_from = it -> from;
                v.erase(it, v.end());
                now = next;
                step ns;
                ns.from = old_from;
                ns.to = next;
                v.push_back(ns);
                enter = true;
                break;
            }

            if(next == it -> from) {
                v.erase(it, v.end());
                now = next;
                enter = true;
                break;
            }
        }

        if(!enter) {
            step ns;
            ns.from = now;
            ns.to = next;

            v.push_back(ns);
            now = next;
        }
        
        // cout << now << endl;
        count++;
    }
    return v;
}

VS QLearning::cvt(VS old) {
    VS n;
    VS::iterator it;
    
    for(it = old.begin(); it != old.end(); it++) {
        step s;
        s.from = node_no_revmap[it -> from];
        s.to = node_no_revmap[it -> to];
        n.push_back(s);
    }

    return n;
}

void QLearning::calcAllWays() {
    N2N::iterator it;
    Node temp;
    // ofstream fout;
    // fout.open(dir, ios::out);

    for(it = nodes.begin(); it != nodes.end(); it++) {
        temp = it -> second;
        if(!temp.is_exit) {
            cout << node_no_revmap[temp.no] << endl;
            auto x = cvt(findWay(node_no_revmap[temp.no]));
            for(auto y = x.begin(); y != x.end(); y++) {
                cout << y -> from << " -> " << y -> to << endl;
            }
            cout << endl;
        }
    }


    // fout.close();
}