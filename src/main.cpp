#include <iostream>
#include <cmath>
#include <vector>
#include<string>
#include <utility>
#include"network.h"
using namespace std;

int main(){
    /*
    matrix A(2,3);
    vector<float> v= {1,1,1};
    A.push_cback(v);
    for (int i = 0; i < A.numcols(); i++)
    {
        for (int j = 0; j < A.numrows(); j++)
        {
            cout<<A.getvalue(j,i)<<endl;
        }
    }
    matrix A;
    matrix B;
    vector<float> v1={1,0};
    vector<float> v2={1,1};
    A.push_cback(v1);
    A.push_cback(v2);
    B.push_cback(v2);
    B.push_cback(v2);
    matrix C=A.multiply(B);
    cout<<C.tostring();
    */
    vector<int> v1={0,1,2,3,4,5,6,7,8,9};
    vector<int> v2(v1.begin() + 1, v1.begin() + 5);
    for (int j = 0; j < v2.size(); j++){
            cout<<v2[j]<<endl;
    }
    return 0;

}