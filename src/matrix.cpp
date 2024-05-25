#include"matrix.h"

matrix::matrix(int colmn, int rows){
    data=vector<vector<float>>(colmn,vector<float>(rows, 0));
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
