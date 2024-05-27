#include <vector>
#include<string>
using namespace std;

class matrix{
    vector<vector<float>> data;
public:
    matrix(int colmn, int rows);
    matrix(){};
    void setvalue(int,int,float);
    float getvalue(int,int);
    matrix getcol(int);
    void push_cback(vector<float>);
    int numrows();
    int numcols();
    matrix multiply(matrix);
    matrix sum(matrix);
    matrix times(float);
    matrix T();
    matrix hadamard(matrix);
    string tostring();
};