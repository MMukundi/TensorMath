#include "Tensor.h"
#include <stdio.h>

int main(){
    auto test = Tensor<double,3,1>({2,3,4});
    double& val = test[0];
    printf("Tensor val: %f %f %f\n",(double)test[0],(double)test[1],(double)test[2]);
    test[3] = 1;
    printf("Tensor val: %f %f %f\n",(double)test[0],(double)test[1],(double)test[2]);
    // printf("Tensor val: %f",(double)test[0]);
}