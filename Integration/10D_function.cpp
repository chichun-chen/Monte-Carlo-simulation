/*
    Compile with
    Mac M1 : clang++ -o 10D_function 10D_function.cpp
             ./10D_function {N}
*/
//Interal I = ∫dx1...∫dx10 1/(1+x1^2+x2^2+...x10^2) for all x form 0 to 1.

#include<iostream>
#include<cmath>
#include<vector>
#include<random>
#include<chrono>
#include<cassert>
#include<cstdlib>
#define _USE_MATH_DEFINES 
#define assertm(exp, msg) assert(((void)msg, exp))
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
        w = w*(8-2*x[i])/7;
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
    int N = atoi(argv[1]);       // # of simulation points for each integraation
    int D = 10;                  // Dim of variables
    int NI = 10000;              // # of total integrations
    vector<double> x(D);         // variable
    vector<double> F(N);         // value of the function for every point
    double I_t;                  // I value of each intagration
    double I = 0.0;              // The final estimated value of the Integration (mean of I_t)
    double Std_I = 0.0;          // variance of I

    mt19937_64 rng;
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(2023);
    std::uniform_real_distribution<double> unif(0, 1);
    
    ///////////////////
    //Simple sampling//
    ///////////////////
    for (int t=0;t<NI;t++){
        I_t = 0.0;
        for (int p=0;p<N;p++){
            for (int k=0;k<D;k++)
                x[k] = unif(rng);
            I_t += Func(x);
        }
        I_t = I_t/N;
        I += I_t;
        Std_I += I_t*I_t;
    }
    
    I = I/NI;
    Std_I = sqrt(Std_I/NI - I*I);
    cout << "Monte Carlo with Simple sampling " << N << " points" << endl;
    cout << "I = " << I << endl;
    cout << "Std = " << Std_I << endl;

    ///////////////////////////////////////
    //Metropolis sampling with distrution//
    ///////////////////////////////////////
    // reset
    rng.seed(2023);
    I = 0.0; Std_I = 0.0;

    double w_old, w_new;                    // weight functions
    vector<double> x_old(D), x_new(D);      // variables

    for (int t=0;t<NI;t++){
        I_t = 0.0;
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
            I_t += Func(x_old)/w_old;
        }
        I_t = I_t/N;
        I += I_t;
        Std_I += I_t*I_t;
    }

    I = I/NI;
    Std_I = sqrt(Std_I/NI - I*I);
    cout << "Monte Carlo with Metropolis sampling " << N << " points" << endl;
    cout << "I = " << I << endl;
    cout << "Std = " << Std_I << endl;

    return 0;
}
