#pragma once
#include <vector>
#include <stdio.h>
typedef unsigned int CountingNumber;
template <typename T>
void vecToPointer(std::vector<T> v, T *t)
{
    const auto s = v.size();
    auto iterator = v.begin();
    for (int i = 0; i < s; i++)
    {
        t[i] = *iterator;
        iterator++;
    }
}
template <typename T>
void reverseVecToPointer(std::vector<T> v, T *t)
{
    const auto s = v.size();
    auto iterator = v.rbegin();
    for (int i = 0; i < s; i++)
    {
        t[i] = *iterator;
        iterator++;
    }
}

template <typename Number>
struct TensorData
{
private:
    const CountingNumber rank;
    CountingNumber *shape;
    Number *tensor;

public:
    // TensorData(std::vector<CountingNumber> shapeVector)
    // {
    // }
    TensorData(const CountingNumber rank, CountingNumber *shape, Number *tensor) : rank(rank), shape(shape), tensor(tensor) {}
    TensorData(std::vector<CountingNumber> shapeVector) : rank(shapeVector.size())
    {
        CountingNumber size = 1;
        for (CountingNumber n : shapeVector)
        {
            size *= n;
        }
        tensor = new Number[size];
        shape = new CountingNumber[shapeVector.size()];
        vecToPointer(shapeVector, shape);
    };
    TensorData(std::vector<CountingNumber> shapeVector, std::vector<Number> tensorVector) : rank(shapeVector.size())
    {
        CountingNumber size = 1;
        for (CountingNumber n : shapeVector)
        {
            size *= n;
        }
        assert(tensorVector.size() == size);

        tensor = new Number[size];
        vecToPointer(tensorVector, tensor);
        shape = new CountingNumber[shapeVector.size()];
        reverseVecToPointer(shapeVector, shape);
    };
    inline constexpr bool isScalar()
    {
        return rank == 0;
    }
    operator Number &() { return getScalar(); }
    TensorData operator[](CountingNumber i)
    {
        const int currentShapeIndex = rank-1;
        assert((currentShapeIndex<1||(0 <= i && i < shape[currentShapeIndex])));
        CountingNumber componentSize = 1;
        for (int i = 0; i < currentShapeIndex; i++)
        {
            componentSize *= shape[i];
        }
        return TensorData(rank - 1, shape, tensor + i * componentSize);
    }
    constexpr Number& getScalar()
    {
        assert(isScalar());
        return tensor[0];
    }    
    constexpr Number& operator=(Number n)
    {
        assert(isScalar());
        tensor[0] = n;
        return tensor[0];
    }
};

template <typename Number = double>
class Tensor
{
    TensorData<Number> tensorData;
    // Number* tensorStart;
public:
    Tensor(std::vector<CountingNumber> shape) : tensorData(TensorData<Number>(shape)) {}
    Tensor(std::vector<CountingNumber> shape, std::vector<Number> data) : tensorData(TensorData<Number>(shape, data)) {}
    Tensor() : Tensor({3, 1}, {0, 0, 0}) {}
    TensorData<Number> operator[](CountingNumber i)
    {
        return tensorData[i];
    }
};
