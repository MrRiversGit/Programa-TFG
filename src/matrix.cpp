#include "matrix.h"

matrix::matrix(int colmns, int rows)
{
    data = vector<vector<double>>(colmns, vector<double>(rows, 0));
}

void matrix::setvalue(int c, int r, double value)
{
    data[c][r] = value;
}

double matrix::getvalue(int c, int r)
{
    return data[c][r];
}

matrix matrix::getcol(int col)
{
    int n = data[0].size();
    matrix result(1, n);
    for (int i = 0; i < n; i++)
    {
        result.setvalue(0, i, getvalue(col, i));
    }
    return result;
}

void matrix::push_cback(vector<double> newcolmn)
{
    data.push_back(newcolmn);
}

int matrix::numcols()
{
    return data.size();
}

int matrix::numrows()
{
    return data[0].size();
}

void matrix::set_random()
{
    for (int i = 0; i < numcols(); i++)
    {
        for (int j = 0; j < numrows(); j++)
        {
            setvalue(i, j, rand() / (RAND_MAX / 4.0) - 2);
        }
    }
}

matrix matrix::multiply(matrix B)
{
    double result = 0;
    vector<double> results;
    matrix C(0, 0);
    for (int i = 0; i < B.numcols(); i++)
    {
        for (int j = 0; j < numrows(); j++)
        {
            for (int k = 0; k < numcols(); k++)
            {
                result += getvalue(k, j) * B.getvalue(i, k);
            }
            results.push_back(result);
            result = 0;
        }
        C.push_cback(results);
        results.clear();
    }
    return C;
}

matrix matrix::sum(matrix B)
{
    matrix C(numcols(), numrows());
    for (int i = 0; i < numcols(); i++)
    {
        for (int j = 0; j < numrows(); j++)
        {
            C.setvalue(i, j, getvalue(i, j) + B.getvalue(i, j));
        }
    }
    return C;
}

matrix matrix::times(double scalar)
{
    matrix result(numcols(), numrows());
    for (int i = 0; i < numcols(); i++)
    {
        for (int j = 0; j < numrows(); j++)
        {
            result.setvalue(i, j, scalar * getvalue(i, j));
        }
    }
    return result;
}

matrix matrix::T()
{
    matrix result(numrows(), numcols());
    for (int i = 0; i < numcols(); i++)
    {
        for (int j = 0; j < numrows(); j++)
        {
            result.setvalue(j, i, getvalue(i, j));
        }
    }
    return result;
}

matrix matrix::hadamard(matrix B)
{
    matrix result(numcols(), numrows());
    for (int i = 0; i < numcols(); i++)
    {
        for (int j = 0; j < numrows(); j++)
        {
            result.setvalue(i, j, getvalue(i, j) * B.getvalue(i, j));
        }
    }
    return result;
}

string matrix::tostring()
{
    string output;
    for (int i = 0; i < numrows(); i++)
    {
        for (int j = 0; j < numcols(); j++)
        {
            output += to_string(getvalue(j, i)) + "\t";
        }
        output += "\n";
    }
    return output;
}
