#include "matrix.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>


int main(int argc, char *argv[]){
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

//TEST(Matrix, Dimension_Constructor){
//
//  Matrix<int> A(5);
//  EXPECT_EQ(A.size(), 5);
//}

TEST(Matrix, Stream_Operator){
  
  Matrix<int,1> A(9);
  A << 1,2,3,4,5,6,7,8,9;
  vector<int> Ans{1,2,3,4,5,6,7,8,9};

  EXPECT_TRUE(equal(A.data().begin(),
    A.data().begin()+9, Ans.begin()));
}

TEST(Matrix, MatrixSlice_ExtentInit){
  MatrixSlice<3> MatSlice(3,4,5);
  vector<int> Ans{3,4,5};
  EXPECT_TRUE(equal(MatSlice.extents.begin(),
      MatSlice.extents.begin()+3, Ans.begin()));

  vector<int> Ans2{20,5,1};
  EXPECT_TRUE(equal(MatSlice.strides.begin(),
      MatSlice.strides.begin()+3, Ans2.begin()));
}

//TEST(Matrix, Matrix_MultiDimensionInit){
//  Matrix<int,3> A(2,3,5);
//  A << 1,2,3,4,5,
//       2,3,4,5,6,
//       7,8,1,2,3,
//
//       2,4,6,8,0,
//       4,6,8,0,2,
//       6,8,0,2,4;
//  A.info();
//}
