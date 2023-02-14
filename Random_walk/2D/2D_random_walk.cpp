/*
    Compile with:
    Mac M1 : clang++ -o 2D_random_walk 2D_random_walk.cpp
*/

#include<iostream>
#include<cmath>
#include<random>
#include<chrono>

using namespace std;


double distance(int x, int y)
{
    return sqrt(x*x + y*y);
}

int main()
{
    int x, y;          // position coordinates
    int N_max=500;     // Random steps
    double d;          // mean distance 
    double walk;       // random walk
    FILE *f; 
    
    f=fopen("mean_distance.txt","w");    

    mt19937_64 rng;
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    rng.seed(2023);
    std::uniform_real_distribution<double> unif(0, 1);

    for (int N=0; N<=N_max; N++){
        // simulate N^2 times for each N
        d=0;
        for (int t=0; t<N*N; t++){
            x=0; y=0;
            // walk N steps
            for (int s=0; s<N; s++){
                walk = unif(rng);
                if (walk <= 0.25)
                    y++;
                else if (walk <= 0.5)
                    y--;
                else if (walk <= 0.75)
                    x++;
                else
                    x--;
            }
            // calculate the distance of the ended point
            d += distance(x,y)/(N*N);
        }
        //cout << "N=" << N << ", <d>=" << d << endl;
        fprintf(f,"%-d  %-f\n",N, d);
    }
    fclose(f);

    return 0;
}
