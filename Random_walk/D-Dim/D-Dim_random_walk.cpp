/*
    Compile with:
    gcc -Wall -I/opt/homebrew/include -c D-Dim_random_walk.cpp
    gcc -L/opt/homebrew/lib -o D-Dim_random_walk.out D-Dim_random_walk.o -lgsl -lgslcblas -lm -lstdc++
*/

#include<iostream>
#include <cmath>
#include<vector>
#include<gsl/gsl_rng.h>

using namespace std;


double distance(vector<int> v){   
    double d = 0;
    for (int i=0; i<v.size(); i++)
        d += v[i]*v[i];
    return sqrt(d);
}

vector<int> initialize(vector<int> v){
    for (int i=0; i<v.size(); i++)
        v[i] = 0;
    return v;
}

int main(){
    int Dim=5;                // Dimension
    vector<int> p(Dim,0);     // position coordinates
    int N_max=250;             // Random steps
    double d;                 // mean distance 
    double walk;              // random walk
    int  partition;           // for determine direction of walks
    FILE *f; 
    gsl_rng *rng;
    
    f=fopen("mean_distance.txt","w");
    rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(rng, 2023);    

    for (int N=0; N<=N_max; N++){
        // simulate N^D times for each N
        d=0;
        for (int t=0; t<pow(N,3); t++){
            p = initialize(p);
            // walk N steps
            for (int s=0; s<N; s++){
                walk = gsl_rng_uniform(rng);
               
                partition = 0;
                while (walk > (partition+1.0)/(2.0*Dim)){
                    partition += 1;
                }
                //cout << (partition+1.0)/(2.0*Dim) << endl;
                //dir = partition/2;
                //sign = partition%2;
                if (partition%2 == 0)
                    p[partition/2]++;
                else
                    p[partition/2]--;  
            }
            // calculate the distance of the ended point
            d += distance(p)/pow(N,3);
        }
        //cout << "N=" << N << ", <d>=" << d << endl;
        fprintf(f,"%-d  %-f\n",N, d);
    }
    fclose(f);

    return 0;
}
