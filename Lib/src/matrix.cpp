#ifndef Matrix_H_
#define Matrix_H_

#include "matrix.h"

template<typename T>
Matrix<T>::Matrix(int dim)
{
  data_.reserve(dim);
}

template<typename T>
Matrix<T>& operator<<(Matrix<T>& Mat, T value){
  Mat.data().push_back(value);
  return Mat;
}

template<typename T>
Matrix<T>& operator,(Matrix<T>& Mat, T value){
  Mat << value;
  return Mat;
}

template class Matrix<int>;

template
Matrix<int>& operator<<(Matrix<int>&, int);

template
Matrix<int>& operator,(Matrix<int>&, int);
#endif /* Matrix_H_ */
