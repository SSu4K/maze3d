#include "lighting.h"

static double* squares_map;
static int squares_count = 0;
static int max_distance = 0;
static double step = 1;
static double intensity = 0;

int light_init(int max_d, double step, double light_intensity){
    max_distance = max_d;
    intensity = light_intensity;
    squares_count = max_distance / step;
    squares_map = (double*)calloc(squares_count, sizeof(double));
    if(squares_map==NULL)
        return 0;
    for(int i=0;i<squares_count;i++){
        squares_map[i] = pow(i*step, 2);
    }
    return 1;
}

int light_free(){
    free(squares_map);
    return 1;
}

double get_square(double x){
    if(x<0){
        x*=(-1);
    }
    if(x>=max_distance){
        return 0;
    }
    long n = x/step;
    if(n>=squares_count){
        return squares_map[squares_count-1];
    }
    return squares_map[n];
}

double get_intensity(double distance, double height){
    double square_sum = (get_square(distance) + get_square(height));
    if(square_sum==0)
        return 0; 
    return intensity/square_sum;
}