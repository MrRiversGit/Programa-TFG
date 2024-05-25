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

int labeled_data::size(){
    return dataset.size();
}

void labeled_data::addnew(pair<matrix,matrix> newdata){
    dataset.push_back(newdata);
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

void network::setweight(int layer, int colmn, int row, float value){
        layers[layer].first.setvalue(colmn,row,value);
}

void network::setbias(int layer, int colmn, int row, float value){
        layers[layer].second.setvalue(colmn,row,value);
}

float network::getweight(int layer, int colmn, int row){
        return layers[layer].first.getvalue(colmn,row);
}

float network::getbias(int layer, int colmn, int row){
        return layers[layer].second.getvalue(colmn,row);
}

void network::feedforward(matrix& a){
    for (int i = 0; i < layers.size()-1; i++){
        a=sigmoid(layers[i].first.multiply(a).sum(layers[i].second));
    }
}



void network::GD(labeled_data mini_batch){
    
}

void network::SGD(labeled_data train_data, int epochs, int minisize){
    int n=train_data.size();
    vector<labeled_data> mini_batches;
    int start=0, end=minisize;
    for (int i = 0; i < epochs; i++){
        //falta un shuffle
        start=0;
        for (int end = minisize; end < n; end+=minisize){
            mini_batches.push_back(train_data.sample(start,end));
            start=end;
        }
        
    }

}