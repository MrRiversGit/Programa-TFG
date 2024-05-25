#include <vector>
#include<string>
#include"matrix.h"
using namespace std;

class labeled_data{
    vector<pair<matrix,matrix>> dataset;
public: 
    labeled_data(int batch_size, int input_size, int output_size);
    labeled_data(){};
    void setimput(int position, int coord, float value);
    float getimput(int position, int coord);
    void setoutput(int position, int coord, float value);
    float getoutput(int position, int coord);
    int size();
    void addnew(pair<matrix,matrix>);
    labeled_data sample(int start, int end);
};

class network{
    vector<pair<matrix,matrix>> layers;
public:
    network(vector<int> sizes);
    void setweight(int layer, int colmn, int row, float value);
    void setbias(int layer, int colmn, int row, float value);
    float getweight(int layer, int colmn, int row);
    float getbias(int layer, int colmn, int row);
    void feedforward(matrix& a);
    network backprop();
    void GD(labeled_data mini_batch);
    void SGD(labeled_data train_data, int epoch, int minisize);
};