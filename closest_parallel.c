#include "closest_parallel.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <math.h>

//Used to get total number of procceses depending on depth of tree
int sumof(int start, int end){
    int total = 0;
    for(int i=start; i<= end; i++){
        total += pow(2,i);
    }
    return total;
}

//Used to calculate curr_depth depending on how many processes have been forked
int depth_calculator(int forks){
    int level;
    int curr_level;
    for(level = 1; level<forks; level++){
        if( (((pow(2,level)-1) <= forks)) && ((forks<= (2*(pow(2,level)-1)))) ){
            curr_level = level;
        }
    }
    return curr_level;
}
int curr_depth = 0;
int total;
double _closest_parallel(struct Point P[], size_t n, int pdmax, int *pcount)
{
    // static int num_forks = 0;
    if(n<=3 || pdmax == 0){
        return _closest_serial(P,n);
    }

    int mid = n/2;
    int fdl[2];
    int fdr[2];

    pid_t l_child;
    pid_t r_child;

    if (pipe(fdl)==-1) 
    { 
        fprintf(stderr, "Pipe 1 Failed" ); 
        exit(1); 
    }

    if (pipe(fdr)==-1) 
    { 
        fprintf(stderr, "Pipe 2 Failed" ); 
        exit(1); 
    }

    l_child = fork();
    r_child = fork();

    if ((l_child < 0) || (r_child < 0))
    { 
        fprintf(stderr, "fork Failed" ); 
        exit(1); 
    }

    if(l_child == 0){
        close(fdl[0]); // Close reading end for left child pipe
        // curr_depth = depth_calculator(num_forks);
        double left_result = _closest_parallel(P, mid, pdmax-1, pcount);
        write(fdl[1], &left_result, sizeof(double));
        close(fdl[1]);
        exit(*pcount);
        if(n<=3 || pdmax == 0){
            exit(0);
        }
        int descendentsL = sumof(1,pdmax-1);
        exit(descendentsL);
    }

    if(r_child == 0){
        close(fdr[0]); // Close reading end for right child pipe
        // curr_depth = depth_calculator(num_forks);
        double right_result = _closest_parallel(P+mid,n-mid, pdmax-1, pcount);
        write(fdr[1], &right_result, sizeof(double));
        close(fdr[1]);
        exit(*pcount);
        if(n<=3 || pdmax == 0){
            exit(0);
        }
        int descendentsR = sumof(1,pdmax-1);
        exit(descendentsR);
    }
    close(fdl[1]);
    close(fdr[1]);
    double left_smallest;
    double right_smallest;

    //wait for children to finish
    int status_l = 0;
    int status_r = 0;
    int combined = 0;

    waitpid(l_child,&status_l,0);
    waitpid(r_child,&status_r,0);

    // Check if child exited with 1, if so parent should too
    if(WIFEXITED(status_l)){
        int exit_value = WEXITSTATUS(status_l);
        if(exit_value == 1){
            exit(1);
        }else{
            combined += exit_value;
        }
    }

    if(WIFEXITED(status_r)){
        int exit_value = WEXITSTATUS(status_r);
        if(exit_value == 1){
            exit(1);
        }else{
            combined += exit_value;
        }
    }
    combined +=2;
    *pcount = combined;

    read(fdl[0], &left_smallest, sizeof(double));
    read(fdr[0], &right_smallest, sizeof(double));

    double d = (left_smallest < right_smallest)? left_smallest : right_smallest;
    double smallest_either_side = combine_lr(P,n,P[mid],d);
    close(fdl[0]);
    close(fdr[0]);
    return smallest_either_side;
}


double closest_parallel(struct Point P[], size_t n, int pdmax, int *pcount)
{ 
    qsort(P, n, sizeof(P[0]),compare_x);
    return _closest_parallel(P, n, pdmax, pcount);
}

