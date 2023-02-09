/*
    Compile with:
    gcc -Wall -I/opt/homebrew/include -c 2D_random_walk.cpp
    gcc -L/opt/homebrew/lib -o 2D_random_walk.out 2D_random_walk.o -lgsl -lgslcblas -lm
*/

#include<iostream>
#include <cmath>
#include<gsl/gsl_rng.h>

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
    gsl_rng *rng;
    
    f=fopen("mean_distance.txt","w");
    rng = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(rng, 2023);    

    for (int N=0; N<=N_max; N++){
        // simulate N^2 times for each N
        d=0;
        for (int t=0; t<N*N; t++){
            x=0; y=0;
            // walk N steps
            for (int s=0; s<N; s++){
                walk = gsl_rng_uniform(rng);
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
