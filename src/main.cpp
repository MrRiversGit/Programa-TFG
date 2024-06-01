#include <iostream>
#include <cmath>
#include <vector>
#include<string>
#include <utility>
#include"network.h"
#include"utils.h"

using namespace std;

const int SAMPLE=80;
const int INTERVAL_A=0, INTERVAL_B=1;

int main(){
    /*
    vector<vector<float>> A;
    A=vector<vector<float>>(5,vector<float>(3,0));
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
        {
            cout<<A[i][j]<<"\t";
        }
        cout<< endl;
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

    vector<int> v1={0,1,2,3,4,5,6,7,8,9};
    vector<float> v1(5, 0);
    vector<int> v2(v1.begin() + 1, v1.begin() + 5);
    for (int j = 0; j < v1.size(); j++){
            cout<<v1[j]<<endl;
    }
    matrix vector(1,4);
    vector.setvalue(1,4,6);
    cout<<vector.tostring();
    */
    labeled_data learning_data(SAMPLE,1,1);
    for (int i = 0; i < SAMPLE; i++){
        learning_data.setinput(i,0,i/(float)SAMPLE);
        learning_data.setoutput(i,0,sigmoid(learning_data.getinputmatrix(i)).getvalue(0,0));
    }
    //learning_data.show_data();

    network neural(vector<int> {1,1,1});
    neural.SGD(learning_data, 1, 10);

    return 0;

}