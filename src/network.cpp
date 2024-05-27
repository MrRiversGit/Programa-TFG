#include"network.h"
#include"utils.h"

labeled_data::labeled_data(int batch_size, int input_size, int output_size){
    matrix input(1,input_size);
    matrix output(1,output_size);
    dataset = vector<pair<matrix,matrix>>(batch_size,pair (input,output));
}

void labeled_data::setimput(int position, int coord, float value){
    dataset[position].first.setvalue(1,coord,value);
}

float labeled_data::getimput(int position, int coord){
    return dataset[position].first.getvalue(1,coord);
}

void labeled_data::setoutput(int position, int coord, float value){
    dataset[position].second.setvalue(1,coord,value);
}

float labeled_data::getoutput(int position, int coord){
    return dataset[position].second.getvalue(1,coord);
}

matrix labeled_data::getimputmatrix(int position){
    return dataset[position].first;
}

matrix labeled_data::getoutputmatrix(int position){
    return dataset[position].first;
}

int labeled_data::size(){
    return dataset.size();
}

void labeled_data::addnew(pair<matrix,matrix> newdata){
    dataset.push_back(newdata);
}

void labeled_data::shuffle_data(){
    random_device rd;
    mt19937 g(rd());
    shuffle(dataset.begin(), dataset.end(), g);
}

labeled_data labeled_data::sample(int start, int end){
    vector<pair<matrix,matrix>> sub_vector(dataset.begin() + start, dataset.begin() + end);
    labeled_data result;
    result.dataset=sub_vector;
    return result;
}

network::network(vector<int> sizes){
    for (int i = 1; i < sizes.size(); i++){
        matrix biases(1,sizes[i]);
        matrix weights(sizes[i-1],sizes[i]);
        layers.push_back(pair (biases,weights));
    }
}

vector<int> network::sizes(){
    vector<int> size_vector;
    for (int i = 0; i < layers.size(); i++){
        size_vector.push_back(layers[i].second.numrows());
    }
    return size_vector;
}

void network::setweight(int layer, int colmn, int row, float value){
        layers[layer].first.setvalue(colmn,row,value);
}

void network::setweights(int layer, matrix value){
        layers[layer].first=value;
}

void network::setbias(int layer, int colmn, int row, float value){
        layers[layer].second.setvalue(colmn,row,value);
}

void network::setbiases(int layer, matrix value){
        layers[layer].second=value;
}

float network::getweight(int layer, int colmn, int row){
        return layers[layer].first.getvalue(colmn,row);
}

matrix network::getweights(int layer){
    return layers[layer].first;
}

float network::getbias(int layer, int colmn, int row){
        return layers[layer].second.getvalue(colmn,row);
}

matrix network::getbiases(int layer){
    return layers[layer].second;
}

network network::sum(network B){
    for (int i = 0; i < layers.size(); i++){
        B.setbiases(i,getbiases(i).sum(B.getbiases(i)));
        B.setweights(i,getweights(i).sum(B.getweights(i)));
    }
    return B;
}

network network::by(float eta){
    network result=*this;
    for (int i = 0; i < layers.size(); i++){
        result.setbiases(i,getbiases(i).times(eta));
        result.setweights(i,getweights(i).times(eta));
    }
    return result;
}

float network::dot(network B){
    float result=0;
    for (int i = 0; i < layers.size(); i++){
        result+=getbiases(i).T().multiply(B.getbiases(i)).getvalue(0,0);
        matrix weights1=getweights(i), weights2=B.getweights(i);
        for (int j = 0; j < sizes()[i]; j++){
            result+=weights1.getcol(j).T().multiply(weights2.getcol(j)).getvalue(0,0);
        }
    }
    return result;
}

matrix network::feedforward(matrix a){
    for (int i = 0; i < layers.size()-1; i++){
        a=sigmoid(layers[i].first.T().multiply(a).sum(layers[i].second));
    }
    return a;
}

network network::backprop(matrix imput, matrix output){
    network gradient(sizes());
    vector<matrix> z;
    vector<matrix> activations;
    int n=layers.size();
    //FEEDFORWARD pero guardando los resultados intermedios
    activations.push_back(imput);
    z.push_back(layers[0].first.T().multiply(imput).sum(layers[0].second));
    activations.push_back(sigmoid(z[0]));
    for (int i = 1; i < n; i++){
        z.push_back(layers[i].first.T().multiply(activations[i]).sum(layers[i].second));
        activations.push_back(sigmoid(z[i]));
    }
    //BACKPROPAGATION
    matrix delta=activations[n].sum(output.times(-1)).hadamard(sigmoid_deriv(z[n-1]));
    gradient.setbiases(n-1,delta);
    gradient.setweights(n-1,delta.multiply(activations[n-1]));
    for (int i = n-1; i>0; i--){
        delta=activations[i].sum(output.times(-1)).hadamard(sigmoid_deriv(z[i-1]));
        gradient.setbiases(i-1,delta);
        gradient.setweights(i-1,delta.multiply(activations[i-1]));
    }
    return gradient;
}

void network::GD(labeled_data mini_batch){
    float eta=1, ALPHA=1, ETA_min=0.0000001;
    int n=mini_batch.size();
    network gradient_1, gradient_2, temp_network;
    for (int i = 0; i < n; i++){
        gradient_1=backprop(mini_batch.getimputmatrix(i),mini_batch.getoutputmatrix(i));
        temp_network=sum(gradient_1.by(-eta));
        gradient_2=temp_network.backprop(mini_batch.getimputmatrix(i),mini_batch.getoutputmatrix(i));
        eta+=ALPHA*gradient_1.dot(gradient_2);
        if (eta<0){
            eta=ETA_min;
        }
        sum(gradient_1.by(-eta));
    }
}

void network::SGD(labeled_data train_data, int epochs, int minisize){
    int n=train_data.size();
    vector<labeled_data> mini_batches;
    int start=0, end=minisize;
    for (int i = 0; i < epochs; i++){
        start=0;
        for (int end = minisize; end < n; end+=minisize){
            //mini_batches.push_back(train_data.sample(start,end));
            GD(train_data.sample(start,end));
            start=end;
        }
    }
}