#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <math.h>

#include <unsupported/Eigen/MatrixFunctions>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;
//using Eigen::MatrixXd;

MatrixXd readMatrix(const char *filename)
{
    std::ifstream indata;

    indata.open(filename);

    std::string line;
    getline(indata, line);
    std::stringstream lineStream(line);
    std::string cell;
    int count = 0, raw, coll;
    while (std::getline(lineStream, cell, ','))
    {
        if(count == 0) raw = stoi(cell);
        else coll = stoi( cell );
        count++;
    }
    MatrixXd res(raw,coll);
    cout<<"Matrix has been created"<<endl;
    raw = 0; coll = 0;
    while (getline(indata, line))
    {
    
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ','))
        {
            
            //cout<<"Raw: "<<raw<<" Coll: "<<coll<<endl;   
            res(raw,coll) = stof(cell);
            coll++;
        }
        coll = 0;
        raw++;
    }
    indata.close();
    return res;
};

//TODO:
//Saving type of matrix
void writeMatrix(const char *filename, MatrixXd mat)
{
    ofstream outdata(filename,ios_base::out);
    int raws = mat.rows();
    int cols = mat.cols();
    outdata<<raws<<","<<cols<<endl;
    for(int i = 0; i< raws; i++)
    {
        for(int j = 0; j < cols-1; j++)
        {
            outdata<<mat(i,j)<<",";
        }
        outdata<<mat(i,cols-1)<<endl;
    }
    outdata.close();
    
}

/* void test_read_write_matrix_into_csv()
{
  MatrixXd m = MatrixXd::Random(3,3);
  writeMatrix("test_w.csv", m);
  MatrixXd n = readMatrix("test_w.csv");
  if(m == n) cout<<"True"<<endl;
  cout<<m<<endl;
  cout<<"===="<<endl;
  cout<<n<<endl;
} */

double Exp(double x) // the functor we want to apply
{
    return std::exp(x);
}

int main()
{
    MatrixXd X = readMatrix("X.csv");
    MatrixXd y = readMatrix("y.csv");
    MatrixXd z, z1, p, p1, u, w ;
    float b0 = log(y.mean() / (1 - y.mean()) ) ;
    cout<< b0<<endl;
    VectorXd b = ArrayXd::Zero(20);
    VectorXd b_old = ArrayXd::Zero(20);
    b(0) = b0;
    cout<<"Transposing"<<endl;
    b = b.transpose();
    for(int i = 0; i < 20; i++)
    {
        z = X * b;
        z = -z;     
        z = z.unaryExpr([](double d) {return std::exp(d);});
        z1 = z.unaryExpr([](double d) {return d + 1.0;});
        p = z1.unaryExpr([](double d) {return 1.0 / d;});
        p1 = p.unaryExpr([](double d) {return 1 - d;});
        w = p * p1;
        w = w.unaryExpr([](double d) {return 1.0 / d;});
        u = z + (y -  p) * w;
        b_old = b;
        
    }
    // cout<<m;
    return 0;

    
}
