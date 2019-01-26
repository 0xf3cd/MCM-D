#ifndef NODE
#include "Node.h"
#define NODE
#endif

#include <map>
#include <fstream>
using namespace std;

int main() {
    int i;
    int node_amount;
    ifstream fin;
    map<string, Node> node_map;

    fin.open("./info.txt", ios::in);

    fin >> node_amount;
    for(i = 1; i <= node_amount; i++) {
        Node new_node;
        fin >> new_node.name;
    }

    return 0;
}