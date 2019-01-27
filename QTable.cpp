#ifndef QTABLE
#include "QTable.h"
#define QTABLE
#endif

QTable::QTable() {
    t = nullptr;
    node_amount = -1;
}

QTable::~QTable() {
    int i;
    if(t == nullptr) {
        return;
    }

    for(i = 0; i < node_amount; i++) {
        delete[] t[i];
    }
    delete[] t;
}

void QTable::init(int node_amount) {
    int i, j;
    this -> node_amount = node_amount;
    t = new double*[node_amount];
    for(i = 0; i < node_amount; i++) {
        t[i] = new double[node_amount];
    }

    for(i = 0; i < node_amount; i++) {
        for(j = 0; j < node_amount; j++) {
            t[i][j] = 0;
        }
    }
}

double QTable::getV(int row, int col) {
    return t[row][col];
}

void QTable::setV(int row, int col, double newV) {
    t[row][col] = newV;
}