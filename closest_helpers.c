#include "closest_helpers.h"
#include <math.h>

int verbose = 0;

int compare_x(const void* a, const void* b) 
{   
    int x_distance = (*(struct Point*)a).x - (*(struct Point*)b).x;
    return x_distance;
} 

int compare_y(const void* a, const void* b) 
{
    int y_distance = (*(struct Point*)a).y - (*(struct Point*)b).y;
    return y_distance; 
} 

double dist(struct Point p1, struct Point p2) 
{
    double distance = 0.0;
    double power = 2;
    distance = sqrt(pow((double)p1.x - (double)p2.x,power) + pow((double)p1.y - (double)p2.y,power));
    // distance = sqrt(pow(p1.x - p2.x,2) + pow(p1.y - p2.y,2));
    return distance;
} 
