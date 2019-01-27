#ifndef QLEARNING
#include "QLearning.h"
#define QLEARNING
#endif

int main() {
    QLearning QL;
    QL.init("./example.txt");
    QL.showNode();
    QL.showLine();
    QL.showMatrix();
    return 0;
}