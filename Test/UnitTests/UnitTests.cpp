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
  
  Matrix<int> A(9);
  A << 1,2,3,4,5,6,7,8,9;
  vector<int> Ans{1,2,3,4,5,6,7,8,9};

  EXPECT_TRUE(equal(A.data().begin(),
    A.data().begin()+9, Ans.begin()));
}
