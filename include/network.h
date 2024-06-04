#include <vector>
#include<string>
#include<algorithm>
#include<random>
#include<fstream>
#include"matrix.h"
using namespace std;

const float ETA_0=1, ALPHA=1, ETA_MIN=0.000001;
const int SAMPLE=50;
const int INTERVAL_A=-4, INTERVAL_B=4;

class labeled_data{
    vector<pair<matrix,matrix>> dataset;
public: 
    labeled_data(int batch_size, int input_size, int output_size);
    labeled_data(){};
    void setinput(int position, int coord, float value);
    float getinput(int position, int coord);
    void setoutput(int position, int coord, float value);
    float getoutput(int position, int coord);
    matrix getinputmatrix(int position);
    matrix getoutputmatrix(int position);
    int size();
    void addnew(pair<matrix,matrix>);
    void shuffle_data();
    labeled_data sample(int start, int end);
    void show_data();
    void export_as_file(string file);
};

class network{
    vector<pair<matrix,matrix>> layers;
public:
    network(vector<int> sizes);
    network(){};
    vector<int> sizes();
    void setweight(int layer, int colmn, int row, float value);
    void setweights(int layer, matrix value);
    void setbias(int layer, int colmn, int row, float value);
    void setbiases(int layer, matrix value);
    float getweight(int layer, int colmn, int row);
    matrix getweights(int layer);
    float getbias(int layer, int colmn, int row);
    matrix getbiases(int layer);
    network sum(network B);
    network by(float scalar);
    float dot(network);
    matrix feedforward(matrix a);
    network backprop(matrix input, matrix output);
    void GD(labeled_data mini_batch);
    void SGD(labeled_data train_data, int epoch, int minisize);
    void show_network();
    labeled_data generate_results(int sample);
};