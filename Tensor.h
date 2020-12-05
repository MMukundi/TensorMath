template <typename Number>
struct TensorData{
    unsigned int m;
    unsigned int n;
    Number* tensor;
public:
    TensorData operator[](unsigned int);
};
template <typename Number, unsigned int m, unsigned int n>
class Tensor{
Number* data;
public:
    Tensor();
    TensorData<Number> operator[](unsigned int);
};