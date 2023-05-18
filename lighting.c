#include "lighting.h"

double* squares_map;
int squares_count;
int max_distance;
double step;
double intensity;

int light_init(int max_distance, double step, double intensity){
    squares_count = max_distance / step;
    squares_map = (double*)calloc(squares_count, sizeof(double));
    for(int i=0;i<squares_count;i++){
        squares_map[i] = pow(i*step, 2);
    }
}

int light_free(){
    free(squares_map);
}

double get_square(double x){
    if(x<0){
        x*=(-1);
    }
    int n = x/step;
    if(n>=squares_count){
        return squares_map[squares_count-1];
    }
    return squares_map[n];
}

double get_intensity(double distance, double height){
    return intensity/(get_square(distance) + get_square(height));
}