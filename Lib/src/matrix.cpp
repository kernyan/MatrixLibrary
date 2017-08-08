#ifndef Matrix_H_
#define Matrix_H_

#include "matrix.h"

/*
template<typename T, int N>
template<typename ...Dims>
Matrix<T,N>::Matrix(Dims ...dims) :
  extents(dims...)
{
  data_.reserve(extents.size_);
}

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

template class Matrix<int,1>;
template class Matrix<int,2>;
template class Matrix<int,3>;

template
Matrix<int,1>& operator<<(Matrix<int,i>&, int);
template
Matrix<int,2>& operator<<(Matrix<int>&, int);
template
Matrix<int>& operator<<(Matrix<int>&, int);

template
Matrix<int>& operator,(Matrix<int>&, int);
*/
#endif /* Matrix_H_ */
