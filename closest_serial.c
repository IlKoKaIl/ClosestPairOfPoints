#include "closest_serial.h"
#include <stdlib.h>
#include <stdio.h>

double combine_lr(struct Point P[], size_t n, struct Point mid_point, double d)
{
    struct Point close_mid[n];
    int current_index = 0;
    for(int i = 0; i<n;i++){
        if (abs(P[i].x - mid_point.x)<d){
            close_mid[current_index] = P[i];
            current_index++;
        }
    }
    double new_min = d;
    qsort(close_mid, current_index, sizeof(P[0]), compare_y);
    for(int i = 0; i< current_index; ++i){
        for(int j = i+1; j<current_index; ++j){
            if((close_mid[j].y - close_mid[i].y)<d){
                if(dist(close_mid[i],close_mid[j]) < new_min){
                    new_min = dist(close_mid[i],close_mid[j]);
                }
            }
        }
    }
    // Can just return new_min as new_min value is only updated if its < d, otherwise 
    // new_min = d, don't need to compare which is smaller as loop alr does so.
    return new_min;
}

double _closest_serial(struct Point P[], size_t n)
{
    if(n<=3){
        return brute_force(P,n);
    }
    // finds mid point, will round down to int
    int mid = n/2;
    
    double dl = _closest_serial(P,mid);
    double dr = _closest_serial(P + mid, n - mid);
    double d = (dl < dr)? dl : dr;
    double smallest_either_side = combine_lr(P,n,P[mid],d);
    return smallest_either_side;
}   

double closest_serial(struct Point P[], size_t n)
{
    qsort(P, n, sizeof(P[0]),compare_x);
    return _closest_serial(P,n);
}
