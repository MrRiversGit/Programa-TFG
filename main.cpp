#include <iostream>
#include <cmath>
#include <vector>
#include<string>
#include <utility>
using namespace std;

class matrix{
    vector<vector<float>> data;
public:
    matrix(int colmn, int rows);
    matrix(){};
    void setvalue(int,int,float);
    float getvalue(int,int);
    void push_cback(vector<float>);
    int numrows();
    int numcols();
    matrix multiply(matrix);
    matrix sum(matrix);
    string tostring();
};

matrix::matrix(int colmn, int rows){
    for(int i = 0; i < colmn ; i++){
        data.push_back(vector<float>(rows, 0));
    }
}

void matrix::setvalue(int c, int r, float value){
    data[c][r]=value;
}

float matrix::getvalue(int c, int r){
    return data[c][r];
}

void matrix:: push_cback(vector<float> newcolmn){
    data.push_back(newcolmn);
}


int matrix::numcols(){
    return data.size();
}

int matrix::numrows(){
    return data[0].size();
}

matrix matrix::multiply(matrix B){
    float result=0;
    vector<float> results;
    matrix C(0,0);
    for (int i = 0; i < B.numcols(); i++){
        for (int j = 0; j < numrows(); j++){
            for (int k = 0; k < numcols(); k++){
                result+=getvalue(k,j)*B.getvalue(i,k);
            }
            results.push_back(result);
            result=0;
        }
        C.push_cback(results);
        results.clear();
    }
    return C;
}

matrix matrix::sum(matrix B){
    matrix C;
    for (int i = 0; i < numcols(); i++){
        for (int j = 0; j < numrows(); j++){
           C.setvalue(i,j,getvalue(i,j)+B.getvalue(i,j));
        }
    }
    return C;
}

string matrix:: tostring(){
    string output;
    for (int i = 0; i < numcols(); i++){
        for (int j = 0; j < numrows(); j++){
            output+=to_string(getvalue(j,i))+"\t";
        }
        output+="\n";
    }
    return output;
}

matrix sigmoid(matrix x){
    matrix A(x.numcols(),x.numrows());
    for(int i=0; i < x.numrows(); i++){
        for(int j=0; j < x.numrows(); j++)
            A.setvalue(i,j,1.0/(1.0+exp(x.getvalue(i,j))));
    }
    return A;
}

matrix sigmoid_deriv(matrix x){
    matrix sigma=sigmoid(x);
    matrix A(x.numcols(),x.numrows());
    for(int i=0; i < x.numrows(); i++){
        for(int j=0; j < x.numrows(); j++)
            A.setvalue(i,j,1.0/sigma.getvalue(i,j)*(1-sigma.getvalue(i,j)));
    }
    return A;
}

class Network{
    vector<pair<matrix,matrix>> layers;
public:
    Network(vector<int> sizes);
    void setvalue(int layer, bool weights, int colmn, int row, float value);
    float getvalue(int layer, bool weights, int colmn, int row);
    float feedforward(matrix& a);
    void SGD(matrix train_data, int epoch, int minisize);
};

Network::Network(vector<int> sizes){
    for (int i = 1; i < sizes.size(); i++){
        matrix biases(1,sizes[i]);
        matrix weights(sizes[i-1],sizes[i]);
        layers.push_back(pair (biases,weights));
    }
}

void Network::setvalue(int layer, bool weights, int colmn, int row, float value){
    if (weights)
        layers[layer].first.setvalue(colmn,row,value);
    else
        layers[layer].second.setvalue(colmn,row,value);
    
}

float Network::getvalue(int layer, bool weights, int colmn, int row){
    if (weights)
        return layers[layer].first.getvalue(colmn,row);
    else
        return layers[layer].second.getvalue(colmn,row);
}

float Network::feedforward(matrix& a){
    for (int i = 0; i < layers.size()-1; i++){
        a=sigmoid(layers[i].first.multiply(a))
    }
    
}

void Network::SGD(matrix train_data, int epochs, int minisize){
    vector
    for (int i = 0; i < epochs; i++){
        
    }

}


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
    */
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
    return 0;

}