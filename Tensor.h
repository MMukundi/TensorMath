#pragma once
#include <cmath>
#include <initializer_list>
#include <stdio.h>

template <typename Number>
struct TensorData
{
private:
    unsigned int m;
    unsigned int n;
    Number *tensor;

public:
    TensorData(Number *tensor, unsigned int m, unsigned int n) : tensor(tensor), m(m), n(n){};
    TensorData(std::initializer_list<Number> tensorData, unsigned int m, unsigned int n) : m(m), n(n){
        const auto size = (int)pow(m, n);
        if (tensorData.size() != size)
        {
            //TODO: Implelment Error Function
        }
        tensor = new Number[size];
        auto iterator = tensorData.begin();
        for (int i = 0; i < size; i++)
        {
            tensor[i] = *iterator;
            iterator++;
        }
    };
    // operator Number() {return tensor[0];}
    operator Number &() { return tensor[0]; }
    TensorData operator[](unsigned int i)
    {
        const unsigned int index = i * (int)pow(m, n - 1);
        return TensorData(tensor + index, m, n - 1);
    }
    Number& operator=(Number n)
    {
        if(n!=0){
            //TODO: Implelment Error Function
        }
        tensor[0] = n;
        return tensor[0];
    }
};
template <typename Number, unsigned int m, unsigned int n>
class Tensor
{
    TensorData<Number> tensorData;
public:
    Tensor(std::initializer_list<Number> tensor):tensorData(TensorData<Number>(tensor, m, n)){}
    Tensor():tensorData(TensorData<Number>(new Number[(int)pow(m, n)], m, n)){}
    TensorData<Number> operator[](unsigned int i)
    {
        return tensorData[i];
    }
};
