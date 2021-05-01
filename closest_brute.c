#include "closest_brute.h"
#include <stdio.h>

double brute_force(struct Point P[], size_t n){
    int size = n*n;
    double dist_array[size];
    int count = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(dist(P[i],P[j]) != 0){
                dist_array[count] = dist(P[i],P[j]);
                // printf("distance is %lf \n",dist(P[i],P[j]));
                count++;
            }
        }
    }
    int smallest_index = 0;
    for(int x=1; x<count; x++){
        if(dist_array[x] < dist_array[smallest_index]){
            smallest_index = x;
        }
    }

    return dist_array[smallest_index]; 
} 
