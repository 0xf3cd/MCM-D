#include <string>
using namespace std;

class Line {
public:
    int no;
    int snno; // start node no
    int enno; // end node no
    double length;
    double width;
    int dis_to_danger;
    Line(); // 构造函数
};