// contains all the matrix library definition

#include <vector>
#include <initializer_list>
#include <array>
#include <iostream>
#include <numeric>
#include <algorithm>

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
  int size() const;
};

template<int N>
template<typename ...Dims>
int MatrixSlice<N>::operator()(Dims... dims){
  // TODO: check to enforce Dims in bound
  int argc[N] {int (dims)...};
  return start_ + inner_product(argc, argc+N,
      strides.begin(),int{0});
}

template<int N>
inline int MatrixSlice<N>::size() const {
  return accumulate(extents.begin(),extents.end(),1,multiplies<int>());
}

namespace matrixImpl{ 
  template<int N>
  void compute_strides(MatrixSlice<N> &ms);

  template<int K, int N>
  void slice_dim(int i, const MatrixSlice<N+1>& in_s,
      MatrixSlice<N>& out_s);
}


template<int N>
template<typename ...Dims>
inline MatrixSlice<N>::MatrixSlice(Dims... dims) : 
  extents {int (dims)...}
{
  matrixImpl::compute_strides(*this);
}

template<typename T, int N>
class MatrixRef; // forward declaration

template<typename T, int N>
class MatrixBase{
  
  public:

    virtual int size() const = 0;
    virtual T* data() = 0;
};

template <typename T, int N>
class Matrix : public MatrixBase<T,N>{ 

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

    virtual int size() const override {return data_.size();};
    virtual T* data() override {return data_.data();};
    vector<T>& GetVector() {return data_;};

    void info();

    template<typename ...Dims>
    T& operator()(Dims... dims){
      return *(data_.begin() + desc_(dims...));
    }

    MatrixRef<T,N-1> row(int i);
    MatrixRef<T,N-1> column(int i);

  private:

    MatrixSlice<N> desc_;
    vector<T> data_;
};

template<typename T, int N>
MatrixRef<T,N-1> Matrix<T,N>::row(int i) {
  MatrixSlice<N-1> row;
  matrixImpl::slice_dim<0>(i,desc_, row);
  return {row, data()};
}

template<typename T, int N>
MatrixRef<T,N-1> Matrix<T,N>::column(int i) {
  MatrixSlice<N-1> col;
  matrixImpl::slice_dim<1>(i,desc_, col);
  return {col, data()};
}

template<typename T, int N>
class MatrixRef : public MatrixBase<T,N>{ 

  public:

    MatrixRef() = default;
    MatrixRef(MatrixSlice<N> MatRef, T* ptr) :
      desc_{MatRef},
      ptr_(ptr) 
      {};

    virtual int size() const override {return desc_.size();};
    virtual T* data() override {return ptr_;};

    void info();

    template<typename ...Dims>
    T& operator()(Dims... dims){
      return *(data() + desc_(dims...));
    }

    MatrixRef<T,N-1> row(int i);
    MatrixRef<T,N-1> column(int i);

  private:

    MatrixSlice<N> desc_;
    T* ptr_;
};

template<typename T, int N>
MatrixRef<T,N-1> MatrixRef<T,N>::row(int i){
  MatrixSlice<N-1> row;
  matrixImpl::slice_dim<0>(i, desc_, row);
  return {row, data()};
}

template<typename T, int N>
MatrixRef<T,N-1> MatrixRef<T,N>::column(int i) {
  MatrixSlice<N-1> col;
  matrixImpl::slice_dim<1>(i,desc_, col);
  return {col, data()};
}

template<typename T, int N>
Matrix<T,N>& operator<<(Matrix<T,N>& Mat, T value){
  Mat.GetVector().push_back(value);
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
  for (auto &i : this->desc_.extents){
    cout << i << ", ";
  }
  cout << endl;
  cout << "strides: ";
  for (auto &i : this->desc_.strides){
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

template<int K, int N>
void slice_dim(int i, const MatrixSlice<N+1>& in_s,
    MatrixSlice<N>& out_s){
  out_s.start_ = in_s.start_ + i * in_s.strides[K];
  std::copy(in_s.extents.begin()+1,in_s.extents.end(),
      out_s.extents.begin());
  std::copy(in_s.strides.begin()+1,in_s.strides.end(),
      out_s.strides.begin());
  if (K==1){
    out_s.extents[0]=in_s.extents[0];
    out_s.strides[0]=in_s.strides[0];
  }
}
}
