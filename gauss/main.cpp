#include <string>
#include "method.h"

int main()
{
    std::vector<std::vector<double>> rcsv;
    {
        lazycsv::parser parser{"AB.csv"};
        for (const auto row : parser)
        {
            std::vector<double> r;
            for (const auto cell : row)
            {
                r.push_back(std::stod(std::string(cell.raw())));
            }
            rcsv.push_back(r);
        }
    }

    int rows = rcsv.size();
    int cols = rcsv[0].size();
    Eigen::MatrixXd A(rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            A(i, j) = rcsv[i][j];
        }
    }

    Eigen::VectorXd solution = gaussianMethod(A);
    std::cout << "Solution:\n" << solution << "\n";

    return 0;
}
