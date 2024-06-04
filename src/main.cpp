#include <iostream>
#include <cmath>
#include <vector>
#include<string>
#include <utility>
#include"network.h"
#include"utils.h"

using namespace std;

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
        learning_data.setinput(i,0, INTERVAL_A +(INTERVAL_B-INTERVAL_A)*i/(float)SAMPLE);
        //cout<<learning_data.getinputmatrix(i).tostring();
        //learning_data.setoutput(i,0,sigmoid_deriv(learning_data.getinputmatrix(i)).getvalue(0,0));
        learning_data.setoutput(i,0,exp(learning_data.getinput(i,0)));
        //cout<<learning_data.getoutputmatrix(i).tostring();
    }

    //learning_data.show_data();

    network neural(vector<int> {1,10,10,1});
    //neural.setweight(0,0,0,1);
    //neural.setbias(0,0,0,0);
    neural.SGD(learning_data,200,10);
    //cout<<neural.getweight(0,0,0)<<"\t"<<neural.getbias(0,0,0)<<"\n";
    learning_data.export_as_file("learning_data.csv");
    neural.generate_results(SAMPLE).export_as_file("results.csv");
    return 0;
}