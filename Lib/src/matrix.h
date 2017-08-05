// contains all the matrix library definition

#include <vector>
#include <initializer_list>
using namespace std;

template <typename T>
class Matrix{

  public:

    Matrix() = default;

    Matrix(int dim);

    // explicit Matrix(int dim);
    // Matrix (double dim) = delete;
    // Matrix& operator=(const Matrix&) = delete;

    int size() const {return data_.size();};
    vector<T>& data() {return data_;};

  private:

    vector<T> data_;
};


template<typename T>
Matrix<T>& operator<<(Matrix<T>& Mat, T value);

template<typename T>
Matrix<T>& operator,(Matrix<T>& Mat, T value);
