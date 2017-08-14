#include "matrix.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]){
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Matrix, Dimension_Constructor){

  Matrix<int, 1> A(5);
  EXPECT_EQ(A.size(), 5);
  A << 1,2,3,4,5;
  EXPECT_EQ(A.size(), 5);
}

TEST(Matrix, Stream_Operator){
  
  Matrix<int,1> A(9);
  A << 1,2,3,4,5,6,7,8,9;
  vector<int> Ans{1,2,3,4,5,6,7,8,9};

  EXPECT_TRUE(equal(A.data(),
    A.data()+9, Ans.begin()));
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

TEST(Matrix, Matrix_MultiDimensionAccess){
  Matrix<int,3> A(2,3,5);
  A << 1,2,3,4,5,
       2,3,4,5,6,
       7,8,1,2,3,

       2,4,6,8,0,
       4,6,8,0,2,
       6,8,0,9,4;
  EXPECT_EQ(A(1,2,3), 9);
}

TEST(Matrix, Matrix_OneDimensionedOneElem){
  Matrix<int,1> A(2);
  A << 99,100;
  auto A2 = A.row(0);
  EXPECT_EQ(A2.size(),1);
}

class MatrixTest : public ::testing::Test{
  protected:
    virtual void SetUp(){
      Mat = Matrix<int, 3>(2,3,5);
      Mat << 1,2,3,4,5,
             2,3,4,5,6,
             7,8,1,2,3,

             2,4,6,8,0,
             4,6,8,0,2,
             6,8,0,9,4;
    };

    Matrix<int,3> Mat;
};

TEST_F(MatrixTest, Matrix_ReplaceValue){
  Mat(1,2,3) = 99;
  EXPECT_EQ(Mat(1,2,3), 99); 
}

TEST_F(MatrixTest, Matrix_RowAccess){
  auto MatRef = Mat.row(1);
  EXPECT_EQ(MatRef(2,3), 9);
}

TEST_F(MatrixTest, MatrixRef_RowAccess){
  auto MatRef = Mat.row(1);
  auto MatRef2 = MatRef.row(2);
  EXPECT_EQ(MatRef2(3), 9);
}

TEST_F(MatrixTest, Matrix_ColumnAccess){
  auto MatRef = Mat.column(1);
  EXPECT_EQ(MatRef(1,2), 8);
}

TEST_F(MatrixTest, MatrixRef_FromMatrix){
  string strMatrix = Mat.GetString();
  
  MatrixRef<int,3> MatRef(Mat);
  string strMatRef;
  MatRef.GetString(strMatRef);

  EXPECT_EQ(strMatrix, strMatRef);
}

TEST_F(MatrixTest, Matrix_Print){
  string Str = Mat.GetString();
  string Ans =
    "{\n"
    "  {\n"
    "    {1,2,3,4,5}\n"
    "    {2,3,4,5,6}\n"
    "    {7,8,1,2,3}\n"
    "  }\n"
    "  {\n"
    "    {2,4,6,8,0}\n"
    "    {4,6,8,0,2}\n"
    "    {6,8,0,9,4}\n"
    "  }\n"
    "}\n";
  EXPECT_EQ(Str,Ans);
}

TEST_F(MatrixTest, MatrixBase_Start){
  EXPECT_EQ(Mat.start(),0);
  EXPECT_EQ(*(Mat.data() + Mat.start()),1);
  auto MatRef = Mat.row(1);
  EXPECT_EQ(*(MatRef.data() + MatRef.start()),2);
  EXPECT_EQ(MatRef.start(),15);
  auto MatRef2 = MatRef.row(2);
  EXPECT_EQ(*(MatRef2.data() + MatRef2.start()),6);
  EXPECT_EQ(MatRef2.start(),25);
}

TEST_F(MatrixTest, Matrix_MultipleDimPrint){
  string AnsDim3 =
    "{\n"
    "  {\n"
    "    {1,2,3,4,5}\n"
    "    {2,3,4,5,6}\n"
    "    {7,8,1,2,3}\n"
    "  }\n"
    "  {\n"
    "    {2,4,6,8,0}\n"
    "    {4,6,8,0,2}\n"
    "    {6,8,0,9,4}\n"
    "  }\n"
    "}\n";
  string AnsDim2 = 
    "{\n"
    "  {2,4,6,8,0}\n"
    "  {4,6,8,0,2}\n"
    "  {6,8,0,9,4}\n"
    "}\n";

  auto MatRef = Mat.row(1);
  string strDim3 = Mat.GetString();
  string strDim2 = MatRef.GetString();

  EXPECT_EQ(AnsDim3, strDim3);
  EXPECT_EQ(AnsDim2, strDim2);
}

class MatrixAlgebra : public ::testing::Test{
  protected:
    virtual void SetUp(){
      Mat = Matrix<int, 2>(3,3);
      Mat << 1,2,3,
             4,5,6,
             7,8,9;
    };

    Matrix<int,2> Mat;
};

TEST_F(MatrixAlgebra, Matrix_PlusEqual){
  Mat += 1;
  Matrix<int, 2> Mat2(3,3);
  Mat2 << 2,3,4,5,6,7,8,9,10;
  EXPECT_EQ(Mat2.GetString(), Mat.GetString());
}

TEST_F(MatrixAlgebra, Matrix_PlusMatrix)
{
  auto Mat2 = Mat + Mat;
  Mat += Mat;
  EXPECT_EQ(Mat.GetString(), Mat2.GetString()); 
}
