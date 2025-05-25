#include <gtest/gtest.h>
#include "method.h"
#include "rwCSV.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(rwCSVTest, ReadCSV) {
    std::ofstream file("test.csv", std::ios::binary);
    file << "A,B,C,D\n1,0,0,1\n0,1,0,1\n0,0,1,1";
    file.close();
    Eigen::MatrixXd result = readCSV("test.csv");
    ASSERT_EQ(result.rows(), 3);
    ASSERT_EQ(result.cols(), 4);
    EXPECT_DOUBLE_EQ(result(0, 0), 1);
    EXPECT_DOUBLE_EQ(result(1, 2), 0);
    std::remove("test.csv");
}
TEST(rwCSVTest, WriteCSVTest) {
    Eigen::VectorXd vec(3);
    vec << 1.5, 2.5, 3.5;
    writeCSV(vec);
    std::ifstream file("solution.csv");
    std::string content;
    std::getline(file, content);
    file.close();
    EXPECT_EQ(content, "1.5,2.5,3.5");
    std::remove("solution.csv");
}


TEST(GaussianMethodTest, CorrectSystem) {
    Eigen::MatrixXd A(3, 4);
    A << 1, 2, -1, 3,
         2, 5, -6, 1,
         3, 8, -10, 1;
    Eigen::VectorXd expected(3);
    expected << -1, 3, 2;
    Eigen::VectorXd result = gaussianMethod(A);
    for (int i = 0; i < expected.size(); i++) {
        EXPECT_NEAR(result(i), expected(i), 1e-9);
    }
}
TEST(GaussianMethodTest, ZeroMatrix) {
    Eigen::MatrixXd A(2, 3);
    A << 0, 0, 0,
         0, 0, 0;
    Eigen::VectorXd result = gaussianMethod(A);
    EXPECT_TRUE(result.isApprox(Eigen::VectorXd::Zero(2), 1e-9));
}
TEST(GaussianMethodTest, SingularMatrix) {
    Eigen::MatrixXd A(3, 4);
    A << 1, 2, 3, 4,
         1, 2, 3, 4,
         4, 5, 6, 7;
    Eigen::VectorXd result = gaussianMethod(A);
    EXPECT_EQ(result, Eigen::VectorXd::Zero(3));
}
TEST(GaussianMethodTest, InconsistentSystem) {
    Eigen::MatrixXd A(3, 4);
    A << 1, 0, 0, 1,
         0, 1, 0, 2,
         0, 0, 0, 5;
    Eigen::VectorXd result = gaussianMethod(A);
    EXPECT_EQ(result, Eigen::VectorXd::Zero(3));
}


TEST(GaussTest, Full) {
    std::ofstream test_file("test_AB.csv");
    test_file << "A,B,C,D\n2,1,-1,8\n-3,-1,2,-11\n-2,1,2,-3";
    test_file.close();
    Eigen::MatrixXd A = readCSV("test_AB.csv");
    Eigen::VectorXd solution = gaussianMethod(A);
    writeCSV(solution);
    Eigen::VectorXd expected(3);
    expected << 2, 3, -1;
    for (int i = 0; i < expected.size(); i++) {
        EXPECT_NEAR(solution(i), expected(i), 1e-9);
    }
    std::ifstream file("solution.csv");
    ASSERT_TRUE(file.is_open());
    std::string content;
    std::getline(file, content);
    file.close();
    EXPECT_TRUE(content.find("2") != std::string::npos);
    EXPECT_TRUE(content.find("3") != std::string::npos);
    EXPECT_TRUE(content.find("-1") != std::string::npos);
    std::remove("test_AB.csv");
    std::remove("solution.csv");
}
