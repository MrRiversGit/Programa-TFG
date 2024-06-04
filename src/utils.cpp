#include <cmath>
#include"utils.h"
#include"matrix.h"

matrix sigmoid(matrix x){
    matrix A(x.numcols(),x.numrows());
    for(int i=0; i < x.numcols(); i++){
        for(int j=0; j < x.numrows(); j++){
            A.setvalue(i,j,1.0/(1.0+exp(-x.getvalue(i,j))));
        }   
    }
    return A;
}

matrix sigmoid_deriv(matrix x){
    matrix sigma=sigmoid(x);
    matrix A(x.numcols(),x.numrows());
    for(int i=0; i < x.numcols(); i++){
        for(int j=0; j < x.numrows(); j++)
            A.setvalue(i,j,sigma.getvalue(i,j)*(1-sigma.getvalue(i,j)));
    }
    return A;
}
