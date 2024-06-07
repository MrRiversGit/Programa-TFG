#include "network.h"
#include "utils.h"

labeled_data::labeled_data(int batch_size, int input_size, int output_size)
{
    matrix input(1, input_size);
    matrix output(1, output_size);
    dataset = vector<pair<matrix, matrix>>(batch_size, pair(input, output));
}

void labeled_data::setinput(int position, int coord, double value)
{
    dataset[position].first.setvalue(0, coord, value);
}

double labeled_data::getinput(int position, int coord)
{
    return dataset[position].first.getvalue(0, coord);
}

void labeled_data::setoutput(int position, int coord, double value)
{
    dataset[position].second.setvalue(0, coord, value);
}

double labeled_data::getoutput(int position, int coord)
{
    return dataset[position].second.getvalue(0, coord);
}

matrix labeled_data::getinputmatrix(int position)
{
    return dataset[position].first;
}

matrix labeled_data::getoutputmatrix(int position)
{
    return dataset[position].second;
}

int labeled_data::size()
{
    return dataset.size();
}

void labeled_data::addnew(pair<matrix, matrix> newdata)
{
    dataset.push_back(newdata);
}

void labeled_data::shuffle_data()
{
    random_device rd;
    mt19937 g(rd());
    shuffle(dataset.begin(), dataset.end(), g);
}

labeled_data labeled_data::sample(int start, int end)
{
    vector<pair<matrix, matrix>> sub_vector(dataset.begin() + start, dataset.begin() + end);
    labeled_data result;
    result.dataset = sub_vector;
    return result;
}

void labeled_data::show_data()
{
    for (int i = 0; i < size(); i++)
    {
        cout << dataset[i].first.tostring();
        cout << dataset[i].second.tostring();
    }
}

void labeled_data::export_as_file(string file)
{
    ofstream fout(file);
    for (int i = 0; i < dataset.size(); i++)
    {
        fout << getinput(i, 0) << "\t";
        fout << getoutput(i, 0) << "\n";
    }
    fout.close();
}

network::network(vector<int> sizes)
{
    for (int i = 1; i < sizes.size(); i++)
    {
        matrix biases(1, sizes[i]);
        matrix weights(sizes[i - 1], sizes[i]);
        layers.push_back(pair(weights, biases));
    }
}

vector<int> network::sizes()
{
    vector<int> size_vector;
    size_vector.push_back(layers[0].first.numcols());
    for (int i = 0; i < layers.size(); i++)
    {
        size_vector.push_back(layers[i].second.numrows());
    }
    return size_vector;
}

void network::setweight(int layer, int colmn, int row, double value)
{
    layers[layer].first.setvalue(colmn, row, value);
}

void network::setweights(int layer, matrix value)
{
    layers[layer].first = value;
}

void network::setbias(int layer, int colmn, int row, double value)
{
    layers[layer].second.setvalue(colmn, row, value);
}

void network::setbiases(int layer, matrix value)
{
    layers[layer].second = value;
}

double network::getweight(int layer, int colmn, int row)
{
    return layers[layer].first.getvalue(colmn, row);
}

matrix network::getweights(int layer)
{
    return layers[layer].first;
}

double network::getbias(int layer, int colmn, int row)
{
    return layers[layer].second.getvalue(colmn, row);
}

matrix network::getbiases(int layer)
{
    return layers[layer].second;
}

void network::randomize()
{
    for (int i = 0; i < layers.size(); i++)
    {
        layers[i].second.set_random();
        layers[i].first.set_random();
    }
}

network network::sum(network B)
{
    for (int i = 0; i < layers.size(); i++)
    {
        B.setbiases(i, getbiases(i).sum(B.getbiases(i)));
        B.setweights(i, getweights(i).sum(B.getweights(i)));
    }
    return B;
}

network network::by(double eta)
{
    network result = *this;
    for (int i = 0; i < layers.size(); i++)
    {
        result.setbiases(i, getbiases(i).times(eta));
        result.setweights(i, getweights(i).times(eta));
    }
    return result;
}

matrix network::feedforward(matrix a)
{
    int n = layers.size();
    for (int i = 0; i < n - 1; i++)
    {
        a = sigmoid(layers[i].first.multiply(a).sum(layers[i].second));
    }
    a = layers[n - 1].first.multiply(a).sum(layers[n - 1].second);
    return a;
}

int temp1;
network network::backprop(matrix input, matrix output)
{
    network gradient(sizes());
    vector<matrix> z;
    vector<matrix> activations;
    int n = layers.size();
    // FEEDFORWARD pero guardando los resultados intermedios
    activations.push_back(input);
    z.push_back(layers[0].first.multiply(input).sum(layers[0].second));
    activations.push_back(sigmoid(z[0]));
    for (int i = 1; i < n - 1; i++)
    {
        z.push_back(layers[i].first.multiply(activations[i]).sum(layers[i].second));
        activations.push_back(sigmoid(z[i]));
    }
    z.push_back(layers[n - 1].first.multiply(activations[n - 1]).sum(layers[n - 1].second));
    activations.push_back(z[n - 1]);
    // BACKPROPAGATION
    matrix delta = activations[n].sum(output.times(-1));
    gradient.setbiases(n - 1, delta);
    gradient.setweights(n - 1, delta.multiply(activations[n - 1].T()));
    for (int i = n - 1; i > 0; i--)
    {
        delta = layers[i].first.T().multiply(delta).hadamard(sigmoid_deriv(z[i - 1]));
        gradient.setbiases(i - 1, delta);
        gradient.setweights(i - 1, delta.multiply(activations[i - 1].T()));
    }
    return gradient;
}

void network::GD(labeled_data mini_batch, double eta)
{
    int n = mini_batch.size();
    network gradient_1;
    for (int i = 0; i < n; i++)
    {
        temp1 = i;
        gradient_1 = backprop(mini_batch.getinputmatrix(i), mini_batch.getoutputmatrix(i));
        network result = sum(gradient_1.by(-eta));
        for (int j = 0; j < layers.size(); j++)
        {
            setweights(j, result.getweights(j));
            setbiases(j, result.getbiases(j));
        }
    }
}

void network::SGD(labeled_data train_data, int epochs, int minisize, double eta)
{
    int n = train_data.size();
    vector<labeled_data> mini_batches;
    int start = 0, end = minisize;
    for (int i = 0; i < epochs; i++)
    {
        start = 0;
        for (int end = minisize; end < n; end += minisize)
        {
            GD(train_data.sample(start, end), eta);
            start = end;
        }
    }
}

void network::show_network()
{
    for (int i = 0; i < layers.size(); i++)
    {
        cout << "Layer: " << i << "\n";
        cout << "Weights\n";
        cout << getweights(i).tostring();
        cout << "Biases\n";
        cout << getbiases(i).tostring();
    }
}

labeled_data network::generate_results(int sample, double interval_min, double interval_max)
{
    labeled_data results(sample + 1, 1, 1);
    matrix input(1, 1);
    for (int i = 0; i < sample + 1; i++)
    {
        input.setvalue(0, 0, interval_min + (interval_max - interval_min) * i / (double)sample);
        results.setinput(i, 0, input.getvalue(0, 0));
        results.setoutput(i, 0, feedforward(input).getvalue(0, 0));
    }
    return results;
}