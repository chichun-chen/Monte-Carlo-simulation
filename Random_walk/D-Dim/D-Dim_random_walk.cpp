/*
    Compile with:
    Mac M1 : clang++ -o D-Dim_random_walk D-Dim_random_walk.cpp 
*/

#include<iostream>
#include<cmath>
#include<vector>
#include<random>
#include<chrono>
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

int main(int argc, char* argv[]){
    
    int Dim = atoi(argv[1]);      // Dimension                
    vector<int> p(Dim,0);         // position coordinates
    int N_max=1000/Dim;           // Random steps
    double d;                     // mean distance 
    double walk;                  // random walk
    int  partition;               // for determine direction of walks
    FILE *f; 
    
    f=fopen("mean_distance.txt","w");
    
    mt19937_64 rng;
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(2023);
    std::uniform_real_distribution<double> unif(0, 1);    

    for (int N=0; N<=N_max; N++){
        // simulate N^D times for each N
        d=0;
        for (int t=0; t<pow(N,2); t++){
            p = initialize(p);
            // walk N steps
            for (int s=0; s<N; s++){
                walk = unif(rng);
               
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
