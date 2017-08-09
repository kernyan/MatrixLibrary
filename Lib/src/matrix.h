// contains all the matrix library definition

#include <vector>
#include <initializer_list>
#include <array>
#include <iostream>
#include <numeric>

using namespace std;


template<int N>  
struct MatrixSlice{
// functor to map dimensions to vector index

  int size_;
  int start_;

  // TODO: default constructor?
  template<typename ...Dims>
  MatrixSlice(Dims... dims);

  array<int, N> extents;
  array<int, N> strides;

  template<typename ...Dims>
  int operator()(Dims... dims);
};

template<int N>
template<typename ...Dims>
int MatrixSlice<N>::operator()(Dims... dims){
  // TODO: check to enforce Dims in bound
  int argc[N] {int (dims)...};
  return start_ + inner_product(argc, argc+N,
      strides.begin(),int{0});
}

namespace matrixImpl{ 
  template<int N>
  void compute_strides(MatrixSlice<N> &ms);
}


template<int N>
template<typename ...Dims>
inline MatrixSlice<N>::MatrixSlice(Dims... dims) : 
  extents {int (dims)...}
{
  matrixImpl::compute_strides(*this);
}

template<typename T, int N>
class MatrixBase{
  
  public:
    vector<T>* Data() = 0;

  protected:
    MatrixSlice<N> desc_;
};

template <typename T, int N>
class Matrix{ 

  public:

    Matrix() = default;

    template<typename ...Dims>
    Matrix(Dims... dims) :
      desc_(dims...){
      data_.reserve(desc_.size_);
    }

    // explicit Matrix(int dim);
    // Matrix (double dim) = delete;
    // Matrix& operator=(const Matrix&) = delete;

    int size() const {return data_.size();};
    vector<T>& data() {return data_;};

    void info();

    template<typename ...Dims>
    T& operator()(Dims... dims){
      return *(data_.begin() + desc_(dims...));
    }

  private:

    MatrixSlice<N> desc_;
    vector<T> data_;
};


template<typename T, int N>
Matrix<T,N>& operator<<(Matrix<T,N>& Mat, T value){
  Mat.data().push_back(value);
  return Mat;
}

template<typename T, int N>
Matrix<T,N>& operator,(Matrix<T,N>& Mat, T value){
  Mat << value;
  return Mat;
}


template<typename T, int N>
void Matrix<T,N>::info(){
  cout << "extents: ";
  for (auto &i : desc_.extents){
    cout << i << ", ";
  }
  cout << endl;
  cout << "strides: ";
  for (auto &i : desc_.strides){
    cout << i << ", ";
  }
  cout << endl;
  cout << "elements: ";
  for (auto &i : data_){
    cout << i << ", ";
  }
  cout << endl;
}

/* matrix implementation namespace for functions 
 * used to prepare Matrix and supply operations.
 * Should not be exposed to main()
 */
namespace matrixImpl{

template<int N>
void compute_strides(MatrixSlice<N> &ms){
  ms.start_ = 0;
  int sizeTotal = 1;
  for (int i = N-1;i>=0;--i){
    ms.strides[i] = sizeTotal; 
    sizeTotal *= ms.extents[i];
  }
  ms.size_ = sizeTotal;
}  

}
