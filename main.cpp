#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class matrix{
    vector<vector<float>> data;
public:
    matrix(int colmn, int rows);
    void setvalue(int,int,float);
    float getvalue(int,int);
    void push_cback(vector<float>);
    int csize();
    int rsize();
    matrix multiply(matrix,matrix);
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


int matrix::rsize(){
    return data.size();
}

int matrix::csize(){
    return data[0].size();
}

matrix matrix::multiply(matrix A, matrix B){
    float result=0;
    vector<float> results;
    matrix C(0,0);
    for (int i = 0; i < B.rsize(); i++){
        for (int j = 0; j < A.csize(); j++){
            for (int k = 0; k < A.rsize(); k++){
                result+=A.getvalue(k,j)*B.getvalue(i,k);
            }
            results.push_back(result);
            result=0;
        }
        C.push_cback(results);
        results.clear();
    }
    return C;
}


/*
float sigmoid(float x){
    return 1.0/(1.0+exp(x));
}

float sigmoid_deriv(float x){
    float sigma=sigmoid(x);
    return sigma*(1-sigma);
}

class Network{
    int layers;
    vector<matrix> biases;
    vector<matrix> weights;
public:
    Network(int num_layers, vector<int> sizes);
    void set_wvalue(int layer, matrix new_w);
    matrix get_wvalue(int layer);
    void set_bvalue(int layer, matrix new_b);
    matrix get_bvalue(int layer);
    float feedforward(float& a);
    void SGD(matrix train_data, int epoch, int minisize);
};
*/
/*
Network::Network(int num_layers, vector<int> sizes){
    layers=num_layers;
    for (int i = 0; i < layers; i++){
        matrix zero(1,sizes[i]);
        biases.push_back(zero);
        weights.push_back(zero);
    }
    
}

void Network::set_wvalue(int layer, matrix new_w){
    for (int i = 0; i < new_w.csize(); i++){
        for (int j = 0; j < new_w.rsize(); j++){
            weights[layer].setvalue(i,j,new_w.getvalue(i,j));
        }
    }
    
}

void Network::set_bvalue(int layer, matrix new_b){
    for (int j = 0; j < new_b.rsize(); j++){
        biases[layer].setvalue(1,j,new_b.getvalue(1,j));
    }
}

matrix Network::get_wvalue(int layer){
    return weights[layer];
}

matrix Network::get_bvalue(int layer){
    return biases[layer];
}

float Network::feedforward(float& a){
    for (int i = 0; i < layers; i++){
        
    }
    
}
*/
int main(){
    /*
    matrix A(2,3);
    vector<float> v= {1,1,1};
    A.push_cback(v);
    for (int i = 0; i < A.rsize(); i++)
    {
        for (int j = 0; j < A.csize(); j++)
        {
            cout<<A.getvalue(j,i)<<endl;
        }
    }
    */
    matrix A(0,0);
    matrix B(0,0);
    vector<float> v1={1,0};
    vector<float> v2={1,1};
    A.push_cback(v1);
    A.push_cback(v2);
    B.push_cback(v2);
    B.push_cback(v2);
    
    return 0;

}