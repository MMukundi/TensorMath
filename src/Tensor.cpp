#include "TensorWrapper.h"
#include <stdio.h>

int main(){
    auto test = Tensor<double>({3,2},{2,3,4,5,6,7});
    // printf("Tensor val: %f",(double)test[0][0]);
    printf("All 6 scalars at start of test: {[%f, %f], [%f, %f], [%f, %f]}\n",(double)test[0][0],(double)test[0][1],(double)test[1][0],(double)test[1][1],(double)test[2][0],(double)test[2][1]);
    printf("Before altering [0][1]: %f %f\n",(double)test[0][0],(double)test[0][1]);
    test[0][1] = 1;
    printf("After altering [0][1]: %f %f\n",(double)test[0][0],(double)test[0][1]);
    printf("All 6 scalars at end of test: {[%f, %f], [%f, %f], [%f, %f]}\n",(double)test[0][0],(double)test[0][1],(double)test[1][0],(double)test[1][1],(double)test[2][0],(double)test[2][1]);
    // printf("Tensor val: %f",(double)test[0]);
}