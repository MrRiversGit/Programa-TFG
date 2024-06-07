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
    cout<<"The order of the parameters must be:\n";
    cout<<"1. Learning rate.\n";
    cout<<"2. Number of epochs.\n";
    cout<<"3. Sample size (for SGD).\n";
    cout<<"4. Bottom and upper limit of the interval of approximation.\n";
    cout<<"5. Sample size (for the graph, not counting the last at the limit of the interval).\n";
    cout<<"6. Objetive of approximation (sigmoid, sigmoid_derivative or exponential)\n";
    cout<<"7. Number of layers and size of each one.\n";
    cout<<"Example: 0.25 1000 5 -1 1 50 exponential 3 1 4 1 \n";
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
    if(args<9)
    {
        cout<<"Not enough parameters.\n";
        help();
        return 1;
    }
    if(!(isDouble(argv[1])&&is_number(argv[2])&&is_number(argv[3])&&isDouble(argv[4])&&isDouble(argv[5])&&is_number(argv[6])&&is_number(argv[8])))
    {
        cout<<"Invalid parameter type.\n";
        help();
        return 1;
    }
    double eta=stod(argv[1]);
    int epochs=stoi(argv[2]);
    int mini_size=stoi(argv[3]);
    double interval_min=stod(argv[4]),interval_max=stod(argv[5]);
    int samples=stoi(argv[6]);
    string objective=argv[7];
    int layer_count=stoi(argv[8]);
    if(args!= layer_count+9)
    {
        cout<<"Number of layers and sizes not coherent.\n";
        help();
        return 1;
    }
    vector<int> sizes;
    for(int i=9; i<layer_count+9; i++)
    {
        if(!is_number(argv[i]))
        {
            cout<<"Layer sizes must be integers.\n";
            help();
            return 1;
        }
        sizes.push_back(stoi(argv[i]));
    }

    labeled_data learning_data(samples+1,1,1);
    if(objective=="sigmoid")
    {
        for (int i = 0; i < samples+1; i++)
        {
            learning_data.setinput(i,0, interval_min +(interval_max-interval_min)*i/(double)samples);
            learning_data.setoutput(i,0,sigmoid(learning_data.getinputmatrix(i)).getvalue(0,0));
        }
    }
    else if(objective=="sigmoid_derivative"){
        for (int i = 0; i < samples+1; i++)
        {
            learning_data.setinput(i,0, interval_min +(interval_max-interval_min)*i/(double)samples);
            learning_data.setoutput(i,0,sigmoid_deriv(learning_data.getinputmatrix(i)).getvalue(0,0));
        }
    }
    else if(objective=="exponential"){
        for (int i = 0; i < samples+1; i++)
        {
            learning_data.setinput(i,0, interval_min +(interval_max-interval_min)*i/(double)samples);
            learning_data.setoutput(i,0,exp(learning_data.getinput(i,0)));
        }
    }
    else
    {
        cout<<"Invalid objective of approximation.\n";
        help();
        return 1;
    }

    network neural(sizes);
    neural.randomize();
    neural.SGD(learning_data,epochs,mini_size,eta);
    neural.show_network();
    learning_data.export_as_file("learning_data.csv");
    neural.generate_results(samples,interval_min,interval_max).export_as_file("results.csv");
    return 0;
}