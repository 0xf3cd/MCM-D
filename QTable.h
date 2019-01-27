#include <list>
using namespace std;
typedef list<int> L;

class QTable {
public:
    double **t;
    int node_amount;
    QTable();
    ~QTable();
    void init(int node_amount);
    double getV(int row, int col);
    void setV(int row, int col, double newV);
    void show();
};