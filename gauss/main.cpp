#include "rwCSV.h"
#include "method.h"

int main()
{
    Eigen::MatrixXd A = readCSV("AB.csv");

    Eigen::VectorXd solution = gaussianMethod(A);
    writeCSV(solution);
    std::cout << "Solution:\n" << solution << "\n";

    return 0;
}
