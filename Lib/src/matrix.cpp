#ifndef Matrix_H_
#define Matrix_H_

#include "matrix.h"

template<typename T>
Matrix<T>::Matrix(int dim) :
  data_(dim)
{
}


template class Matrix<int>;

#endif /* Matrix_H_ */
