#include <vector>
#include<string>
#include<iostream>
using namespace std;

class matrix{
    vector<vector<double>> data;
public:
    matrix(int colmn, int rows);
    matrix(){};
    void setvalue(int,int,double);
    double getvalue(int,int);
    matrix getcol(int);
    void push_cback(vector<double>);
    int numrows();
    int numcols();
    void set_random();
    matrix multiply(matrix);
    matrix sum(matrix);
    matrix times(double);
    matrix T();
    matrix hadamard(matrix);
    string tostring();
};