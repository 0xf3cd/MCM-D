#ifndef QLEARNING
#include "QLearning.h"
#define QLEARNING
#endif

const int EPISODE = 100000;

int main() {
    QLearning QL;
    QL.init("./info.txt");
    // QL.showNode();
    // QL.showLine();
    // QL.showMatrix();
    // QL.showExit();
    // auto x = QL.getValidNext(30);
    // for(auto y = x.begin(); y != x.end(); y++) {
    //     cout << *y << endl;
    // }
    // cout << endl;
    // cout << QL.trainOneTime(110) << endl;
    // int i;
    // for(i = 0; i < EPISODE; i++) {
    //     QL.randomTrainOneTime();
    //     // if(i % 100 == 0) {
    //     //     cout << i << endl;
    //     // }
    // }
    QL.readInQ("./TrainedQ.txt");
    // QL.showQTable();
    // QL.findWay(204);
    // cout << endl;
    // QL.findWay(510);
    // cout << endl;
    // auto x = QL.cvt(QL.findWay(510));//404);
    // for(auto y = x.begin(); y != x.end(); y++) {
    //     cout << y -> from << " -> " << y -> to << endl;
    // }
    QL.calcAllWays();
    return 0;
}