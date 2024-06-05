#include <iostream>
#include <cmath>
#include <vector>
#include<string>
#include <utility>
#include <sstream>
#include"network.h"
#include"utils.h"

using namespace std;

void help(){
    cout<<"Invalid parameters.\n";
}

bool isDouble( string myString ) {
    istringstream iss(myString);
    double f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail(); 
}

bool is_number(const string &s) {
  return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
}

int main(int args, char** argv){
    if(args<6)
    {
        help();
        return 1;
    }
    if(!(isDouble(argv[1])&&is_number(argv[2])&&is_number(argv[3])&&is_number(argv[4])))
    {
        help();
        return 1;
    }
    double eta=stod(argv[1]);
    int epochs=stoi(argv[2]);
    int mini_size=stoi(argv[3]);
    int layer_count=stoi(argv[4]);
    if(args!= layer_count+4)
    {
        help();
        return 1;
    }
    vector<int> sizes;
    for(int i=5; i<layer_count; i++)
    {
        if(!is_number(argv[i]))
        {
            help();
            return 1;
        }
        sizes.push_back(stoi(argv[i]));
    }


    /*
    vector<vector<double>> A;
    A=vector<vector<double>>(5,vector<double>(3,0));
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
    vector<double> v1={1,0};
    vector<double> v2={1,1};
    A.push_cback(v1);
    A.push_cback(v2);
    B.push_cback(v2);
    B.push_cback(v2);
    matrix C=A.multiply(B);
    cout<<C.tostring();

    vector<int> v1={0,1,2,3,4,5,6,7,8,9};
    vector<double> v1(5, 0);
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
        learning_data.setinput(i,0, INTERVAL_A +(INTERVAL_B-INTERVAL_A)*i/(double)SAMPLE);
        //cout<<learning_data.getinputmatrix(i).tostring();
        learning_data.setoutput(i,0,sigmoid(learning_data.getinputmatrix(i)).getvalue(0,0));
        //learning_data.setoutput(i,0,exp(learning_data.getinput(i,0)));
        //double x=learning_data.getinputmatrix(i).getvalue(0,0);
        //learning_data.setoutput(i,0,-x*(1+x));
        //cout<<learning_data.getinputmatrix(i).tostring();
    }

    //learning_data.show_data();

    network neural(sizes);
    neural.randomize();
    //neural.setweight(0,0,0,1);
    //neural.setbias(0,0,0,0);
    //neural.setweight(1,0,0,1);
    //neural.setbias(1,0,0,0);
    neural.SGD(learning_data,epochs,mini_size,eta);
    //cout<<neural.getweight(0,0,0)<<"\t"<<neural.getbias(0,0,0)<<"\n";
    learning_data.export_as_file("learning_data.csv");
    neural.generate_results(SAMPLE).export_as_file("results.csv");
    return 0;
}