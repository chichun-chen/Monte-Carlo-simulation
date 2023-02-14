/*
    We interal I = ∫dx1...∫dx10 1/(1+x1^2+x2^2+...x10^2) for all x form 0 to 1.
*/
#include<iostream>
#include<cmath>
#include<vector>
#include <random>
#include <chrono>
#include<cassert>
#include<cstdlib>
#define assertm(exp, msg) assert(((void)msg, exp))
#define PI 3.14159265358979323846
using namespace std;


double Func(vector<double> x){
    double S=1.0;
    for (int i=0;i<x.size();i++)
        S += x[i]*x[i];
    return 1/S;
}

double weight_func(vector<double> x){
    double w=1.0;
    for (int i=0;i<x.size();i++)
        w = w*(6-2*x[i])/5;
        //w = w*1/sqrt(2*PI)*exp(-x[i]*x[i]/2);
    return w;
}

vector<double> copy_vector(vector<double> a, vector<double> b){
    assertm(a.size() == b.size(), "Size of vector has to be the same.");
    for (int i=0;i<a.size();i++)
        a[i] = b[i]; 
    return a;
}

int main(int argc, char* argv[])
{
    int D = 10;                   // Dim of variables
    int N = atoi(argv[1]);        // # of simulation points
    vector<double> x(D);          // variable
    vector<double> F(N);          // value of the function for every point
    double I = 0;                 // The final estimated value of the Integration
    double Var = 0;               // varianve of the sample set

    mt19937_64 rng;
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    std::uniform_real_distribution<double> unif(0, 1);
    
    ////////////////////
    // Simple sampling//
    ////////////////////
    for (int p=0;p<N;p++){
        for (int k=0;k<D;k++)
            x[k] = unif(rng);
            //x[k] = gsl_rng_uniform(rng);
        F[p] = Func(x);
        //cout << F[p] << endl;
        I += F[p];
        Var += F[p]*F[p]; 
    }
    
    I = I/N;
    Var = Var/N - I*I;
    cout << "Monte Carlo with Simple sampling " << N << " points" << endl;
    cout << "I = " << I << endl;
    cout << "Var = " << Var << endl;

    ////////////////////////////////////////
    // Metropolis sampling with distrution//
    ////////////////////////////////////////
    // reset
    I = 0.0; Var = 0.0;

 
    double w_old, w_new;                    // weight functions
    vector<double> x_old(D), x_new(D);      // variables

    // generate first random x
    for (int k=0;k<D;k++)
        x_old[k] = unif(rng);
    w_old = weight_func(x_old);

    for (int p=0;p<N;p++){
        for (int k=0;k<D;k++)
            x_new[k] = unif(rng);
        w_new = weight_func(x_new);
        if (w_new >= w_old ){
            w_old = w_new;
            x_old = copy_vector(x_old, x_new);
        }
        else{
            if (unif(rng) < w_new/w_old ){
                w_old = w_new;
                x_old = copy_vector(x_old, x_new);
            }
        }
        
        F[p] = Func(x_old)/w_old;
        I += F[p];
        Var += F[p]*F[p];
    }

    I = I/N;
    Var = Var/N - I*I;
    cout << "Monte Carlo with Metropolis sampling " << N << " points" << endl;
    cout << "I = " << I << endl;
    cout << "Var = " << Var << endl;

    return 0;
}
